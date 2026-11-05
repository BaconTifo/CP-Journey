#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ldb;
typedef unsigned long long ull;
typedef __int128_t i128;
typedef pair<ll, ll> pll;
typedef stack<tuple<ll, ll, bool>> stpl;
#define file "TONGLOAI_CENTROID"
const ll N = 2e5 + 5, Q = 20;
struct seg{
    ll s = 1;
    vector<ll> a;
    void init(ll n){
        s = n;
        a.assign(4 * s + 1, 0);
    }
    seg(ll n){
        s = n;
        a.assign(4 * s + 1, 0);
    }
    void update(ll i, ll v, ll node, ll l, ll r){
        if(l == r){
            a[node] = v;
            return;
        }
        ll m = (l + r)/2;
        if(i <= m) update(i, v, 2 * node, l, m);
        else update(i, v, 2 * node + 1, m + 1, r);
        a[node] = a[2 * node] + a[2 * node + 1];
    }
    ll query(ll l, ll r, ll node, ll lx, ll rx){
        if(lx >= l && rx <= r){
            return a[node];
        }
        if(lx > r || l > rx) return 0;
        ll m = (lx + rx)/2;
        return query(l, r, 2 * node, lx, m) + query(l, r, 2 * node + 1, m + 1, rx);
    }
};
ll n, q, K;
ll c[N], a[N], sz[N], del[N], par[N], up[N][Q + 1], h[N];
vector<ll> grp[N];
vector<vector<pll>> d[N], dv[N];
vector<seg> p[N], pv[N];
vector<ll> adj[N];
ll gets(ll u, ll p){
    sz[u] = 1;
    for(ll v : adj[u]){
        if(v == p || del[v]) continue;
        sz[u] += gets(v, u);
    }
    return sz[u];
}
ll getc(ll u, ll p, ll m){
    for(ll v : adj[u]){
        if(v == p || del[v]) continue;
        if(sz[v] > m/2) return getc(v, u, m);
    }
    return u;
}
void build(ll u, ll p){
    ll cent = getc(u, -1, gets(u, -1));
    del[cent] = 1;
    par[cent] = p;
    for(ll v : adj[cent]){
        if(del[v]) continue;
        build(v, cent);
    }
}
void dfs(ll u, ll p){
    for(ll v : adj[u]){
        if(v == p) continue;
        h[v] = h[u] + 1;
        up[v][0] = u;
        dfs(v, u);
    }
}   
ll findlca(ll u, ll v){
    if(h[u] < h[v]) swap(u, v);
    if(h[u] != h[v]){
        ll dis = h[u] - h[v];
        for(ll j = 0; (1<<j)<=dis; j++){
            if((dis>>j) & 1) u = up[u][j];
        }
    }
    if(u == v) return u;
    for(ll j = Q; j>=0; j--){
        if((up[u][j] != up[v][j])){
            u = up[u][j];
            v = up[v][j];
        }
    }
    return up[u][0];
}
ll getdis(ll u, ll v){
    ll lca = findlca(u, v);
    return h[u] + h[v] - 2 * h[lca];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    if(fopen(file".INP", "r")){
        freopen(file".INP", "r", stdin);
        freopen(file".OUT", "w", stdout);
    }
    cin>>n>>q>>K;
    for(ll i = 1; i<=n; i++){
        cin>>c[i];
    }
    for(ll i = 1; i<=n; i++){
        cin>>a[i];
    }
    for(ll i = 1; i < n; i++){
        ll u, v; cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1, -1);
    for(ll j = 1; j<=Q; j++){
        for(ll i = 1; i<=n; i++){
            if((h[i] >= (1<<j))){
                up[i][j] = up[up[i][j - 1]][j - 1];
            }
        }
    }
    build(1, 0);
    for(ll i = 1; i<=n; i++){
        ll u = i;
        while(u){
            grp[u].push_back(c[i]);
            u = par[u];
        }
    }
    for(ll i = 1; i<=n; i++){
        sort(grp[i].begin(), grp[i].end());
        grp[i].erase(unique(grp[i].begin(), grp[i].end()), grp[i].end());
        d[i].assign(grp[i].size(), vector<pll>());
        dv[i].assign(grp[i].size(), vector<pll>());
    }
    for(ll i = 1; i<=n; i++){
        ll u = i;
        while(u){
            ll j = lower_bound(grp[u].begin(), grp[u].end(), c[i]) - grp[u].begin();
            d[u][j].push_back({getdis(i, u), i});
            if(par[u]){
                dv[u][j].push_back({getdis(i, par[u]), i});
            }
            u = par[u];
        }
    }
    for(ll i = 1; i<=n; i++){
        for(ll j = 0; j < grp[i].size(); j++){
            if(!d[i][j].empty()){
                p[i].push_back(seg(d[i][j].size()));
                sort(d[i][j].begin(), d[i][j].end());
                for(ll k = 0; k < d[i][j].size(); k++){
                    
                }
            }
        }
    }
    while(q--){

    }
}
