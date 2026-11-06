#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ldb;
typedef unsigned long long ull;
typedef __int128_t i128;
typedef pair<ll, ll> pll;
typedef stack<tuple<ll, ll, bool>> stpl;
#define file "BEULER"
const ll N = 2005, INF = 1e9;
ll n, m;
vector<ll> adj[N], fadj[N];
vector<pll> cadj[N];
ll num[N], deg[N], used[N];
ll c[N][N], f[N][N], d[N];
vector<ll> idx[N][N];
ll t = 0;
struct edge{
    ll u, v, w1, w2;
};
edge edges[N];
void check(ll u, ll p){
    num[u] = t;
    for(ll v : adj[u]){
        if(num[v]) continue;
        check(v, u);
    }
}
void bfs(){
    fill(d, d + 2 + n + m, INF);
    d[0] = 0;
    queue<ll> q;
    q.push(0);
    while(!q.empty()){
        ll u = q.front();
        q.pop();
        for(ll v : fadj[u]){
            if(c[u][v] - f[u][v] == 0) continue;
            if(d[v] != INF) continue;
            d[v] = d[u] + 1;
            q.push(v);
        }
    }
}
ll dfs(ll u, ll curdelta){
    if(curdelta == 0) return 0;
    if(u == n + m + 1) return curdelta;
    for(ll v : fadj[u]){
        if(c[u][v] - f[u][v] == 0) continue;
        if(d[v] != d[u] + 1) continue;
        ll delta = dfs(v, min(curdelta, c[u][v] - f[u][v]));
        if(delta == 0) continue;
        f[u][v] += delta;
        f[v][u] -= delta;
        return delta;
    }
    return 0;
}
bool good(ll x){
    for(ll i = 0; i <= n + m + 1; i++){
        fadj[i].clear();
        for(ll j = 0; j<=n + m + 1; j++){
            c[i][j] = f[i][j] = 0;
        }
    }
    for(ll i = 1; i<=m; i++){
        fadj[0].push_back(i + n);
        fadj[i + n].push_back(0);
        c[0][i + n] = 1;
        if(edges[i].w1 <= x){
            fadj[i + n].push_back(edges[i].u);
            fadj[edges[i].u].push_back(i + n);
            c[i + n][edges[i].u] = 1;
        }
        if(edges[i].w2 <= x){
            fadj[i + n].push_back(edges[i].v);
            fadj[edges[i].v].push_back(i + n);
            c[i + n][edges[i].v] = 1;
        }
    }
    for(ll i = 1; i<=n; i++){
        fadj[i].push_back(n + m + 1);
        fadj[n + m + 1].push_back(i);
        c[i][n + m + 1] = deg[i]/2;
    }
    ll flow = 0;
    while(true){
        bfs();
        if(d[n + m + 1] == INF) break;
        while(ll delta = dfs(0, INF)){
            flow += delta;
        }
    }
    return flow == m;
}
list<ll> solve(ll u){
    list<ll> ans;
    ans.push_back(u);
    while(!cadj[u].empty()){
        ll v = cadj[u].back().first;
        ll id = cadj[u].back().second;
        cadj[u].pop_back();
        if(used[id]) continue;
        used[id] = 1;
        u = v;
        ans.push_back(u);
    }
    for(auto it = ++ans.begin(); it != ans.end(); ++it){
        auto t = solve(*it);
        t.pop_back();
        ans.splice(it, t);
    }
    return ans;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    if(fopen(file".INP", "r")){
        freopen(file".INP", "r", stdin);
        freopen(file".OUT", "w", stdout);
    }  
    cin>>n>>m;
    for(ll i = 1; i<=m; i++){
        ll u, v, w1, w2; cin>>u>>v>>w1>>w2;
        adj[u].push_back(v);
        adj[v].push_back(u);
        edges[i] = {u, v, w1, w2};
    }
    for(ll i = 1; i<=n; i++){
        deg[i] = adj[i].size();
        if(deg[i] % 2 != 0){
            cout<<-1;
            return 0;
        }
    }
    for(ll i = 1; i<=n; i++){
        if(!num[i]){
            t++;
            check(i, -1);
        }
    }
    ll last_l = -1;
    for(ll i = 1; i<=n; i++){
        if(deg[i] > 0){
            if(last_l == -1) last_l = i;
            else if(num[i] != num[last_l]){
                cout<<-1;
                return 0;
            }
        }
    }
    ll ans = 0;
    ll l = 0, r = INF;
    while(l <= r){
        ll mid = (l + r)/2;
        if(good(mid)){
            ans = mid;
            r = mid - 1;
        }
        else l = mid + 1;
    }
    cout<<ans<<'\n';
    good(ans);
    for(ll i = 1; i<=m; i++){
        for(ll j : fadj[i + n]){
            if(j == 0) continue;
            if(f[i + n][j] == 1){
                if(j == edges[i].u){
                    idx[edges[i].u][edges[i].v].push_back(i);
                    cadj[j].push_back({edges[i].v, i});
                }
                else{
                    idx[edges[i].v][edges[i].u].push_back(i);
                    cadj[j].push_back({edges[i].u, i});
                }
            }
        }
    }
    // for(ll i = 1; i<=n; i++){
    //     for(auto [v, id] : cadj[i]){
    //         cout<<v<<" ";
    //     }
    //     cout<<'\n';
    // }
    list<ll> res;
    for(ll i = 1; i<=n; i++){
        if(deg[i]){
            res = solve(i);
            break;
        }
    }
    for(auto it = res.begin(); it != res.end(); it++){
        //cout<<*it<<" ";
        if(next(it) == res.end()) break;
        // if(next(it) == res.end()){
        //     cout<<idx[*it][*res.begin()].back()<<" ";
        //     idx[*it][*res.begin()].pop_back();
        // }
        else{
            cout<<idx[*it][*next(it)].back()<<" ";
            idx[*it][*next(it)].pop_back();
        }
    }
}
