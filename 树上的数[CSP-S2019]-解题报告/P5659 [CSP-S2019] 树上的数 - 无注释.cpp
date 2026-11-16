#include <bits/stdc++.h>
using namespace std;
namespace Force {
#define ms(a) memset(a, 0, sizeof(a))
typedef long long ll;
const ll N = 2000 + 10, inf = 2147483647;
struct edge {
    ll u, v;
} e[N * 2];
ll n, num[N], vis[N], a[N], ans[N], tmp[N], ump[N];
void solve() {
    for (ll i = 1; i <= n; i++)
        tmp[i] = num[i];
    for (ll i = 1; i <= n - 1; i++)
        swap(tmp[e[a[i]].u], tmp[e[a[i]].v]);
    ll flag = 1;
    for (ll i = 1; i <= n; i++)
        ump[tmp[i]] = i;
    for (ll i = 1; i <= n; i++) {
        if (ump[i] > ans[i]) {
            flag = 0;
            break;
        }
        if (ump[i] < ans[i])
            break;
    }
    if (!flag)
        return;
    for (ll i = 1; i <= n; i++)
        ans[i] = ump[i];
}
void dfs(ll step) {
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
            num[a] = i;
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
struct UFDS {
    ll dad[N], n;
    void init(ll p) {
        n = p;
        for (ll i = 1; i <= n; i++)
            dad[i] = i;
    }
    ll find(ll x) {
        while (x != dad[x])
            x = dad[x] = dad[dad[x]];
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
void solve() {
    U.init(n);
    memset(vis, 0, sizeof(vis));
    for (ll i = 1; i <= n; i++) {
        for (ll j = 1; j <= n; j++) {
            if (vis[j] || (i != n && U.check(id[i], j)))
                continue;
            ans[i] = j;
            vis[j] = 1;
            U.merge(j, id[i]);
            break;
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
        for (ll i = 1; i <= n - 1; i++)
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
    for (ll i = 1; i <= n; i++) {
        ll now = dfn[id[i]], des = inf;
        if (tag[now] != FirS) {
            for (ll j = now + 1; j <= n; j++) {
                if (tag[j] != FirS)
                    des = min(des, link[j]);
                if (tag[j] == SecF)
                    break;
            }
        }
        if (tag[now] != SecF) {
            for (ll j = now - 1; j >= 1; j--) {
                if (tag[j] != SecF)
                    des = min(des, link[j]);
                if (tag[j] == FirS)
                    break;
            }
        }
        if (dfn[des] > now) {
            for (ll j = dfn[des] - 1; j >= now + 1; j--)
                tag[j] = FirS;
            tag[now] = tag[dfn[des]] = SecF;
        }
        if (dfn[des] < now) {
            for (ll j = dfn[des] + 1; j <= now - 1; j++)
                tag[j] = SecF;
            tag[now] = tag[dfn[des]] = FirS;
        }
        tag[1] = tag[n] = UnLim;
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
struct UFDS {
    ll dad[N], out[N], in[N], n;
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
    void merge(ll x, ll y) {
        ll d1 = find(x), d2 = find(y);
        dad[d1] = d2;
        size[d2] += size[d1];
        out[x] = in[y] = 1;
        return;
    }
    ll check(ll x, ll y, ll jud) {
        if (in[y] || out[x])
            return 0;
        ll d1 = find(x), d2 = find(y);
        if (d1 == d2 && size[d1] != jud)
            return 0;
        return 1;
    }
} U;
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
ll dfs1(ll root, ll edge) {
    ll ret = n + 1;
    if (root != edge && U.check(edge, root, deg[root] + 1))
        ret = min(ret, root);
    for (ll i = G.head[root]; i; i = G.e[i].nxt) {
        ll son = G.e[i].to;
        if (edge == i)
            continue;
        if (U.check(edge, i, deg[root] + 1))
            ret = min(ret, dfs1(son, i ^ 1));
    }
    return ret;
}
ll dfs2(ll root, ll edge, ll des) {
    if (root == des) {
        U.merge(edge, root);
        return 1;
    }
    for (ll i = G.head[root]; i; i = G.e[i].nxt) {
        ll son = G.e[i].to;
        if (edge == i)
            continue;
        if (dfs2(son, i ^ 1, des)) {
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
        for (ll i = 1; i <= n; i++)
            scanf("%lld", id + i);
        for (ll i = 1; i <= n - 1; i++) {
            scanf("%lld%lld", &a, &b);
            G.add(a, b);
            G.add(b, a);
            deg[a]++;
            deg[b]++;
        }
        U.init(G.cnt);
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
}
