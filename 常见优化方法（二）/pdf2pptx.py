#!/usr/bin/env python3
"""把 PDF 的每一页渲染成高清图片，再组装成一个 PPTX。

特点：
- 每页一张图，自动按 PDF 页面比例设置幻灯片尺寸
- 默认 200 DPI，适合投影和打印
- 支持只转换部分页、PNG/JPEG、覆盖输出
- 不修改 PDF 原文件

注意：输出的是“图片版 PPTX”，文字和图形不可在 PowerPoint 中编辑。
如果需要可编辑的 PPTX，需要走 PDF -> DOCX/PPTX 的结构化转换，不属于本脚本范围。

依赖：
    pip install pymupdf python-pptx pillow

用法：
    python pdf_to_pptx.py input.pdf
    python pdf_to_pptx.py input.pdf -o output.pptx --dpi 300
    python pdf_to_pptx.py input.pdf --pages 1-5,8 --format jpeg --quality 92

Windows 下如果 `python` 不是你想用的解释器，可以显式指定：
    py -3 pdf_to_pptx.py input.pdf
"""

from __future__ import annotations

import argparse
import io
import sys
from pathlib import Path


def parse_pages(spec: str, page_count: int) -> list[int]:
    """解析 1-based 页码，返回 0-based 索引。"""
    pages: set[int] = set()
    for chunk in spec.split(","):
        chunk = chunk.strip()
        if not chunk:
            continue
        if "-" in chunk:
            left, right = chunk.split("-", 1)
            start, end = int(left), int(right)
        else:
            start = end = int(chunk)
        if start < 1 or end > page_count or start > end:
            raise ValueError(
                f"页码范围 {chunk!r} 无效；PDF 共 {page_count} 页，页码从 1 开始"
            )
        pages.update(range(start - 1, end))
    if not pages:
        raise ValueError("没有选中任何页面")
    return sorted(pages)


def load_renderer():
    """延迟导入，保证 --help 在没有安装依赖时也能用。"""
    try:
        import pymupdf as fitz  # PyMuPDF >= 1.24 推荐写法
    except ImportError:
        try:
            import fitz  # 旧版 PyMuPDF
        except ImportError as exc:
            raise SystemExit(
                "缺少 PyMuPDF。请先安装：\n"
                "    python -m pip install pymupdf\n"
                "或：\n"
                "    py -3 -m pip install pymupdf"
            ) from exc
    return fitz


def load_pptx():
    try:
        from pptx import Presentation
        from pptx.util import Inches
    except ImportError as exc:
        raise SystemExit(
            "缺少 python-pptx。请先安装：\n"
            "    python -m pip install python-pptx\n"
            "或：\n"
            "    py -3 -m pip install python-pptx"
        ) from exc
    return Presentation, Inches


def page_image_bytes(
    page, dpi: int, fmt: str, quality: int, fitz
) -> tuple[bytes, int, int]:
    """把一页 PDF 渲染成 PNG/JPEG 字节，同时返回像素宽高。"""
    zoom = dpi / 72.0
    pix = page.get_pixmap(
        matrix=fitz.Matrix(zoom, zoom),
        alpha=False,
        colorspace=fitz.csRGB,
    )

    if fmt == "png":
        return pix.tobytes("png"), pix.width, pix.height

    from PIL import Image

    image = Image.frombytes("RGB", (pix.width, pix.height), pix.samples)
    buffer = io.BytesIO()
    image.save(buffer, format="JPEG", quality=quality, optimize=True)
    image.close()
    return buffer.getvalue(), pix.width, pix.height


def main() -> int:
    parser = argparse.ArgumentParser(
        description="把 PDF 每页转成图片并组装成 PPTX（图片版，不可编辑）",
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
    )
    parser.add_argument("pdf", type=Path, help="输入 PDF 文件")
    parser.add_argument(
        "-o",
        "--output",
        type=Path,
        default=None,
        help="输出 PPTX；默认与 PDF 同名、同目录",
    )
    parser.add_argument(
        "--dpi",
        type=int,
        default=200,
        help="渲染 DPI；文字多建议 200-300",
    )
    parser.add_argument(
        "--format",
        choices=("png", "jpeg"),
        default="png",
        help="幻灯片内嵌图片格式；JPEG 体积更小",
    )
    parser.add_argument(
        "--quality",
        type=int,
        default=92,
        help="JPEG 质量，仅 --format jpeg 时有效",
    )
    parser.add_argument(
        "--pages",
        default=None,
        help="只转换部分页，例如 1-5,8；默认全部",
    )
    parser.add_argument(
        "--size",
        choices=("auto", "16:9", "4:3"),
        default="auto",
        help="幻灯片尺寸；auto 按 PDF 第一页比例",
    )
    parser.add_argument(
        "--force",
        action="store_true",
        help="输出文件已存在时覆盖",
    )
    args = parser.parse_args()

    pdf_path: Path = args.pdf
    if not pdf_path.is_file():
        raise SystemExit(f"找不到 PDF：{pdf_path}")
    if pdf_path.suffix.lower() != ".pdf":
        raise SystemExit(f"输入文件不是 PDF：{pdf_path}")
    if not (72 <= args.dpi <= 600):
        raise SystemExit("--dpi 建议在 72 到 600 之间")

    output: Path = args.output or pdf_path.with_suffix(".pptx")
    if output.suffix.lower() != ".pptx":
        output = output.with_suffix(".pptx")
    if output.exists() and not args.force:
        raise SystemExit(f"输出已存在：{output}\n加 --force 覆盖，或换 -o 指定新文件")

    fitz = load_renderer()
    Presentation, Inches = load_pptx()

    try:
        doc = fitz.open(pdf_path)
    except Exception as exc:
        raise SystemExit(f"打开 PDF 失败：{exc}") from exc

    if doc.needs_pass:
        doc.close()
        raise SystemExit("PDF 有密码保护，请先解除密码再转换")

    page_count = doc.page_count
    if page_count == 0:
        doc.close()
        raise SystemExit("PDF 没有页面")

    try:
        page_indices = (
            parse_pages(args.pages, page_count)
            if args.pages
            else list(range(page_count))
        )
    except ValueError as exc:
        doc.close()
        raise SystemExit(str(exc)) from exc

    prs = Presentation()
    prs.core_properties.title = pdf_path.stem

    # 设置幻灯片尺寸
    first_page = doc.load_page(page_indices[0])
    first_rect = first_page.rect
    if args.size == "16:9":
        prs.slide_width = Inches(13.333)
        prs.slide_height = Inches(7.5)
    elif args.size == "4:3":
        prs.slide_width = Inches(10)
        prs.slide_height = Inches(7.5)
    else:
        ratio = first_rect.width / first_rect.height
        prs.slide_width = Inches(13.333)
        prs.slide_height = int(prs.slide_width / ratio)

    slide_w = int(prs.slide_width)
    slide_h = int(prs.slide_height)
    blank_layout = prs.slide_layouts[6]

    print(
        f"PDF: {pdf_path.name} | {page_count} 页 | 转换 {len(page_indices)} 页 | "
        f"{args.dpi} DPI | {args.format.upper()} | 幻灯片 {slide_w / 914400:.3f} x "
        f"{slide_h / 914400:.3f} in"
    )

    for order, page_index in enumerate(page_indices, start=1):
        page = doc.load_page(page_index)
        data, img_w, img_h = page_image_bytes(
            page, args.dpi, args.format, args.quality, fitz
        )

        slide = prs.slides.add_slide(blank_layout)
        image_stream = io.BytesIO(data)

        scale = min(slide_w / img_w, slide_h / img_h)
        width = int(img_w * scale)
        height = int(img_h * scale)
        left = (slide_w - width) // 2
        top = (slide_h - height) // 2
        slide.shapes.add_picture(image_stream, left, top, width=width, height=height)

        print(
            f"\r  第 {order}/{len(page_indices)} 页（PDF 第 {page_index + 1} 页）",
            end="",
        )
        sys.stdout.flush()

    doc.close()
    print()

    output.parent.mkdir(parents=True, exist_ok=True)
    prs.save(output)
    size_mb = output.stat().st_size / (1024 * 1024)
    print(f"完成：{output}（{size_mb:.1f} MB，{len(page_indices)} 页）")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
