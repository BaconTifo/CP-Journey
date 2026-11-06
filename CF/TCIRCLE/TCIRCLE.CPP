#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ldb;
typedef unsigned long long ull;
typedef __int128_t i128;
typedef pair<ll, ll> pll;
typedef stack<tuple<ll, ll, bool>> stpl;
#define file "TCIRCLE"
const ll N = 3e5 + 5, Q = 20, MOD = 998244353;
ll n, q;
vector<ll> adj[2 * N];
ll par[2 * N], num[2 * N], up[2 * N][Q + 1], tour[2 * N];
ll st[2 * N], e[2 * N], h[2 * N];
ll num_lca[2 * N];
ll x[2 * N];
ll findpar(ll u){
    if(par[u] == u) return u;
    return par[u] = findpar(par[u]);
}
ll cnt, m;
void join(ll u, ll v, ll w){
    u = findpar(u), v = findpar(v);
    if(u == v) return;
    cnt++;
    par[v] = par[u] = cnt;
    adj[cnt].push_back(u);
    adj[cnt].push_back(v);
    num[cnt] = max({num[u], num[v], w});
}
void dfs(ll u){
    m++;
    st[u] = m;
    tour[m] = u;
    for(ll v : adj[u]){
        up[v][0] = u;
        h[v] = h[u] + 1;
        dfs(v);
    }
    e[u] = m;
}
// ll seg[4 * N];
// void update(ll i, ll v, ll node, ll l, ll r){
//     if(l == r){
//         seg[node] = v;
//         return;
//     }
//     ll mid = (l + r)/2;
//     if(i <= mid) update(i, v, 2 * node, l, mid);
//     else update(i, v, 2 * node + 1, mid + 1, r);
//     seg[node] = seg[2 * node] + seg[2 * node + 1];
// }
// ll query(ll l, ll r, ll node, ll lx, ll rx){
//     if(lx >=l && rx <= r) return seg[node];
//     if(lx > r || l > rx) return 0;
//     ll mid = (lx + rx)/2;
//     return query(l, r, 2 * node, lx, mid) + query(l, r, 2 * node + 1, mid + 1, rx);
// }
ll findlca(ll u, ll v){
    if(h[u] < h[v]) swap(u, v);
    if(h[u] != h[v]){
        ll dis = h[u] - h[v];
        for(ll j = 0; (1<<j)<=dis; j++){
            if((dis>>j) & 1){
                u = up[u][j];
            }
        }
    }
    if(u == v) return u;
    for(ll j = Q; j>=0; j--){
        if(up[u][j] != up[v][j]){
            u = up[u][j];
            v = up[v][j];
        }
    }
    return up[u][0];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    if(fopen(file".INP", "r")){
        freopen(file".INP", "r", stdin);
        freopen(file".OUT", "w", stdout);
    }
    cin>>n;
    cnt = n;
    m = 0;
    for(ll i = 1; i<2 * n; i++){
        num[i] = 1;
        par[i] = i;
    }
    for(ll i = 1; i < n; i++){
        ll u, v; cin>>u>>v;
        join(u, v, i);
    }
    ll root = findpar(1);
    dfs(root);
    for(ll j = 1; j<=Q; j++){
        for(ll i = 1; i<2*n; i++){
            if((h[i] >= (1<<j))){
                up[i][j] = up[up[i][j - 1]][j - 1];
            }
        }
    }
    cin>>q;
    while(q--){
        ll k;
        cin>>k;
        for(ll i = 1; i<=k; i++){
            num_lca[i] = n + 1;
            cin>>x[i];
        }
        if(k == 1){
            cout<<n<<'\n';
            continue;
        }
        sort(x + 1, x + 1 + k, [](const ll &u, const ll &v){
            return st[u] < st[v];
        });
        ll ans = 1;
        for(ll i = 1; i<=k; i++){
            if(i > 1){
                ll lca = findlca(x[i], x[i - 1]);
                num_lca[i] = min(num_lca[i], num[lca]);
            }
            if(i < k){
                ll lca = findlca(x[i], x[i + 1]);
                num_lca[i] = min(num_lca[i], num[lca]);
            }
            ans = (ans * num_lca[i]) % MOD;
        }
        cout<<ans<<'\n';
    }
}
