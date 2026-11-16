const canvas = document.getElementById('myCanvas');
const ctx = canvas.getContext('2d');
$("#myCanvas").attr("width", $(window).width());
$("#myCanvas").attr("height",$(window).height());
let isOnOff = false;
let oldX = null;
let oldY = null;
let lineColor = "red";
let lineWidth = 3;
canvas.addEventListener('mousemove', draw, false);
canvas.addEventListener('mousedown', down, true);
canvas.addEventListener('mouseup', up, false);
function down(event) {
	isOnOff = true;oldX = event.clientX;oldY = event.clientY;
}
function up() {
	isOnOff = false;
}
function draw(event) {
	if (isOnOff === true) {
		let newX = event.clientX;
		let newY = event.clientY;
		ctx.beginPath();
		ctx.moveTo(oldX, oldY);
		ctx.lineTo(newX, newY);
		ctx.strokeStyle = lineColor;
		ctx.lineWidth = lineWidth;
		ctx.lineCap = 'round';
		ctx.stroke();
		oldX = newX;oldY = newY;
	}
}
function ok()
{
	$("canvas").css("z-index","114514");
}
function no()
{
	$("canvas").css("z-index","-19198886");
}