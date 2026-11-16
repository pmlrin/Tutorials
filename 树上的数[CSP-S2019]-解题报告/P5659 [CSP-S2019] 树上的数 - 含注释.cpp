#include <bits/stdc++.h>
using namespace std;
namespace Force // 暴力
{
#define ms(a) memset(a, 0, sizeof(a))
typedef long long ll;
const ll N = 2000 + 10, inf = 2147483647;
struct edge {
    ll u, v;
} e[N * 2];
ll n, num[N], vis[N], a[N], ans[N], tmp[N], ump[N];
// P 是排列
// 点的个数 点上的数字 生成P要用到 P 最小的P 点上的数字 数字所在编号
void solve() {
    for (ll i = 1; i <= n; i++)
        tmp[i] = num[i];            // 因为下面要用到 num，所以复制一遍防止出锅
    for (ll i = 1; i <= n - 1; i++) // 注意是边的全排列
        swap(tmp[e[a[i]].u], tmp[e[a[i]].v]); // 按照题意 ~~膜你~~ 模拟
    ll flag = 1;                              // 判断是否更新答案
    for (ll i = 1; i <= n; i++)
        ump[tmp[i]] = i;        // 注意判断字典序是以数字为序，点的编号的排列
    for (ll i = 1; i <= n; i++) // 判断字典序的大小
    {
        if (ump[i] > ans[i]) {
            flag = 0;
            break;
        } // 这种特性启发了我们
        if (ump[i] < ans[i])
            break; // 在后面可以利用贪心求解
    }
    if (!flag)
        return;
    for (ll i = 1; i <= n; i++)
        ans[i] = ump[i]; // 更新答案
}
void dfs(ll step) // 必会技能：生成全排列
{
    if (step >= n) {
        solve();
        return;
    }
    for (ll i = 1; i <= n - 1; i++) {
        if (vis[i])
            continue;
        vis[i] = 1;
        a[step] = i;
        dfs(step + 1);
        vis[i] = 0;
    }
}
void main() {
    ll T, a, b;
    scanf("%lld", &T);
    while (T--) {
        scanf("%lld", &n);
        for (ll i = 1; i <= n; i++) {
            scanf("%lld", &a);
            num[a] = i; // 注意题目输入格式，对于正解来说比较方便
            ans[i] = inf;
        }
        for (ll i = 1; i <= n - 1; i++) {
            scanf("%lld%lld", &a, &b);
            e[i].u = a, e[i].v = b;
        }
        dfs(1);
        for (ll i = 1; i <= n; i++)
            printf("%lld ", ans[i]);
        printf("\n");
    }
    return;
}
} // namespace Force
namespace Flower {
#define ms(a) memset(a, 0, sizeof(a))
typedef long long ll;
const ll N = 2000 + 10, inf = 2147483647;
struct UFDS // 并查集
{
    ll dad[N], n;
    void init(ll p) {
        n = p;
        for (ll i = 1; i <= n; i++)
            dad[i] = i;
    }
    ll find(ll x) // 非递归写法，你值得拥有
    {
        while (x != dad[x])
            x = dad[x] = dad[dad[x]]; // 路径压缩
        return x;
    }
    void merge(ll x, ll y) {
        ll d1 = find(x), d2 = find(y);
        dad[d1] = d2;
        return;
    }
    bool check(ll x, ll y) {
        ll d1 = find(x), d2 = find(y);
        if (d1 == d2)
            return 1;
        return 0;
    }
} U;
ll n, num[N], id[N], vis[N], ans[N];
// 结点数 点上的数字 数字所在编号 是否访问过
void solve() {
    U.init(n);
    memset(vis, 0, sizeof(vis));
    // 对于新图来说，vis 数组防止出现一个点连到链的中间的情况
    for (ll i = 1; i <= n; i++) // 枚举数字
    {
        for (ll j = 1; j <= n; j++) // 贪心地选编号小的点
        {
            if (vis[j] || (i != n && U.check(id[i], j)))
                continue;
            // 首先保证不要破坏链，或者说重复搬运到一个点
            // 其次不要使链提前自闭（当枚举到最后一个时就可以自闭了）
            ans[i] = j;
            vis[j] = 1;
            U.merge(j, id[i]);
            break;
            // 加入有向边 <id[i],j> 表示删边的先后与相邻关系

            // 由于并查集的特性（或者说我们已经用 vis 数组进行维护了），
            // 实际上 merge 的两个参数并没有先后关系
        }
    }
    return;
}
void main() {
    ll T, a, b;
    scanf("%lld", &T);
    while (T--) {
        scanf("%lld", &n);
        for (ll i = 1; i <= n; i++) {
            scanf("%lld", id + i);
            num[id[i]] = i;
        }
        for (ll i = 1; i <= n - 1; i++) // 好像连图都没用到
            scanf("%lld%lld", &a, &b);
        solve();
        for (ll i = 1; i <= n; i++)
            printf("%lld ", ans[i]);
        printf("\n");
    }
    return;
}
} // namespace Flower
namespace Chain {
#define ms(a) memset(a, 0, sizeof(a))
typedef long long ll;
const ll N = 2000 + 10, inf = 2147483647;
const ll UnLim = 0, FirS = 1, SecF = 2;
ll n, id[N], ans[N], deg[N];
ll dfn[N], link[N], tag[N], cnt = 0;
// 结点数 数字所在编号 节点的度
// 节点的dfs序 按dfs序排列的节点 按dfs序排列的节点的标记 dfs序的戳
struct graph {
    struct edge {
        ll nxt, to;
    } e[N * 2];
    ll head[N], cnt;
    void clear() {
        ms(e);
        ms(head);
        cnt = 0;
    }
    void add(ll a, ll b) {
        e[++cnt] = (edge){head[a], b};
        head[a] = cnt;
    }
} G;
void dfs(ll root, ll dad) {
    dfn[root] = ++cnt;
    link[cnt] = root;
    for (ll i = G.head[root]; i; i = G.e[i].nxt) {
        ll son = G.e[i].to;
        if (son == dad)
            continue;
        dfs(son, root);
    }
}
void solve() {
    for (ll i = 1; i <= n; i++)
        if (deg[i] == 1) {
            dfs(i, i);
            break;
        }
    for (ll i = 1; i <= n; i++) // 枚举数字
    {
        ll now = dfn[id[i]], des = inf;
        // now 是起始点，des 是终止点
        // 各个变量里面到底存的是什么，一定要分清
        // 有什么不明白的地方可以提问！
        /*
           --0-- now --1-- q --2-- w --3-- e --4-- des --5--
           0 一定是比 1 后删；1 2 3 4 一定先后删；5 一定比 4 先删。
        */
        if (tag[now] != FirS) // 向后找目标
        {
            for (ll j = now + 1; j <= n; j++) {
                if (tag[j] != FirS)
                    des = min(des, link[j]); // 符合 目的地 的条件，可选
                if (tag[j] == SecF)
                    break; // 不符合 继续走 条件，返回
                // 这里，提一个问题：上面的两个语句能不能互换？为什么？
            }
        }
        /*
           --0-- des --1-- q --2-- w --3-- e --4-- now --5--
           5 一定是比 4 后删；4 3 2 1 一定先后删；0 一定比 1 先删。
        */
        if (tag[now] != SecF) // 向前找目标
        {
            for (ll j = now - 1; j >= 1; j--) {
                if (tag[j] != SecF)
                    des = min(des, link[j]); // 符合 目的地 的条件，可选
                if (tag[j] == FirS)
                    break; // 不符合 继续走 条件，返回
            }
        }
        if (dfn[des] > now) // 目标在后面
        {
            for (ll j = dfn[des] - 1; j >= now + 1; j--)
                tag[j] = FirS;               // 一定先后删
            tag[now] = tag[dfn[des]] = SecF; // 前面的后删
        }
        if (dfn[des] < now) // 目标在前面
        {
            for (ll j = dfn[des] + 1; j <= now - 1; j++)
                tag[j] = SecF;               // 一定先后删
            tag[now] = tag[dfn[des]] = FirS; // 后面的后删
        }
        tag[1] = tag[n] = UnLim; // 只有一条边，自然就无所谓了
        ans[i] = des;
    }
}
void main() {
    ll T, a, b;
    scanf("%lld", &T);
    while (T--) {
        G.clear();
        ms(deg);
        ms(tag);
        cnt = 0;
        scanf("%lld", &n);
        for (ll i = 1; i <= n; i++)
            scanf("%lld", id + i);
        for (ll i = 1; i <= n - 1; i++) {
            scanf("%lld%lld", &a, &b);
            G.add(a, b);
            G.add(b, a);
            deg[a]++;
            deg[b]++;
        }
        solve();
        for (ll i = 1; i <= n; i++)
            printf("%lld ", ans[i]);
        printf("\n");
    }
    return;
}
} // namespace Chain
namespace Perfect {
#define ms(a) memset(a, 0, sizeof(a))
#define for(a) for (register a)
typedef long long ll;
const ll N = 20000 + 10, inf = 2147483647;
ll n, id[N], ans[N], deg[N];
// 结点数 数字所在编号 答案 节点的度
struct UFDS {
    // 仍一样，并查集维护的是删边顺序，一条有向边 <u,v>
    // 表示边 u 在边 v 之前删，且相邻
    // 可参考菊花图部分进行理解
    // 注意 u 和 v 都是原图中的边
    ll dad[N], out[N], in[N], n;
    // out 是一个点有没有出边，in 同理
    // size 是集合大小，即链的大小
    ll size[N];
    void init(ll p) {
        n = p;
        for (ll i = 1; i <= n; i++) {
            dad[i] = i;
            out[i] = in[i] = 0;
            size[i] = 1;
        }
    }
    ll find(ll x) {
        while (x != dad[x])
            x = dad[x] = dad[dad[x]];
        return x;
    }
    // 这里不像菊花图的情况，参数不能颠倒
    void merge(ll x, ll y) {
        // 加有向边 <x,y>
        ll d1 = find(x), d2 = find(y);
        dad[d1] = d2;
        size[d2] += size[d1];
        out[x] = in[y] = 1;
        // 标记一个点有了入边或出边
        // 便于判断加入当前点是否会破坏环
        return;
    }
    ll check(ll x, ll y, ll jud) // 简单几行，充满玄机
    {
        if (in[y] || out[x])
            return 0;
        // 保证 x 是链尾，y 是链首
        ll d1 = find(x), d2 = find(y);
        if (d1 == d2 && size[d1] != jud)
            return 0;
        // 用来判断亿些情况，下面会有大段话来解释
        return 1;
    }
} U; // 实际上对于每个点都开了并查集
struct graph {
    struct edge {
        ll nxt, to;
    } e[N * 2];
    ll head[N], cnt;
    void clear() {
        ms(e);
        ms(head);
        cnt = 0;
    }
    void add(ll a, ll b) {
        e[++cnt] = (edge){head[a], b};
        head[a] = cnt;
    }
} G;
ll dfs1(ll root, ll edge) // 寻径算法
{                         // 短短 14 行代码，讲明白不容易啊 qwq
                          // 欢迎观看注释比代码长系列
    ll ret = n + 1;       // 要返回的目标
    if (root != edge && U.check(edge, root, deg[root] + 1))
        // 接下来判断这个点能不能当作终点。
        // 首先，不是起点才有可能当作终点（废话）
        // 其次。只有最后一个删边，才能保证这个数字不会跑掉。

        // 这里，root 是个新图虚点，原图虚边，为了保证这个边是最后一个被删掉的。

        // 分两种情况：
        //   -
        //   终边未被指定。此时两者不属于同一链，可以连接，表示指定它最后删除。
        //     > check 函数对于不同集合会直接返回 1，表示可行。
        //   - 此边和起始边在同一链上。即它们先后顺序已确定。
        //     那么我们必须要保证这个删边顺序组成的链中，长度刚好为这个节点的边数。
        //     否则，边不可能删的完。
        //     > check 函数的参数 3 用来判断边数。

        // 加 1 的原因，可以类比菊花图的花心。考虑每个点，其周围的边的删边顺序。
        // 其删边关系正好是点的度数 +1（想想那个“吃豆人”的动图）。
        // 实际上，由于虚点的存在，度数应该 +1。
        ret = min(ret, root);
    // 可以了，取个最小即可。
    for (ll i = G.head[root]; i; i = G.e[i].nxt) {
        ll son = G.e[i].to;
        if (edge == i)
            continue; // 别返祖了
        // 我们习惯于记录一个点的父亲，其实判断边也行
        if (U.check(edge, i, deg[root] + 1))
            // 接下来判断这个点能不能当作中转点。

            // 实际上也当作是找起始边，因为判断条件相同，
            // 这也是我们 dfs1 传参数刚开始传两个 id[i] 所决定的

            //  - 首先保证不是同一链（我们本来就要连啊）
            //    > check 函数对于同一链，返回 0。
            //  - 特殊情况：这个边连接两条链，包含起始边和终边。
            //    这时一定连，防止提前自闭。
            //    > 由于虚点的存在，实际上 check 函数发现这两条边已经是
            //      同一链了，且恰好就是点的度数，也就返回 1 了。
            //      不禁让我感慨：check 函数太妙了，直接解决了这么多情况！
            ret = min(ret, dfs1(son, i ^ 1));
        // 为了方便，异或 1 表示反向边（这是我们连续添加两条有向边决定的）
        // 也是奇怪的 cnt 从 (n+1)/2*2+1 开始决定的
    }
    return ret;
}
ll dfs2(ll root, ll edge, ll des) // 更新删边条件（并查集）
{                                 // 这些就很好理解了
    if (root == des) {
        U.merge(edge, root);
        return 1; // 为了便于判断到底是要更新哪个路径
    }
    for (ll i = G.head[root]; i; i = G.e[i].nxt) {
        ll son = G.e[i].to;
        if (edge == i)
            continue;
        if (dfs2(son, i ^ 1, des)) // 沿路径更新
        {
            U.merge(edge, i);
            return 1;
        }
    }
    return 0;
}
void solve() {
    for (ll i = 1; i <= n; i++) {
        ans[i] = dfs1(id[i], id[i]);
        dfs2(id[i], id[i], ans[i]);
    }
    return;
}
void main() {
    ll T, a, b;
    scanf("%lld", &T);
    while (T--) {
        scanf("%lld", &n);
        G.clear();
        ms(deg);
        G.cnt = (n + 1) / 2 * 2 + 1;
        // 把它变成奇数，且比 n 大
        // 便于虚边的建立（虚边都是 1~n 的）

        for (ll i = 1; i <= n; i++)
            scanf("%lld", id + i);
        for (ll i = 1; i <= n - 1; i++) {
            scanf("%lld%lld", &a, &b);
            G.add(a, b);
            G.add(b, a);
            deg[a]++;
            deg[b]++;
        }
        U.init(G.cnt); // 依据 cnt 来开并查集
        solve();
        for (ll i = 1; i <= n; i++)
            printf("%lld ", ans[i]);
        printf("\n");
    }
    return;
}
} // namespace Perfect
int main() {
    Perfect::main();
    return 0;
} // 433 行！
