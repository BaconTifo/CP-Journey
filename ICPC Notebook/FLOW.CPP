#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ldb;
typedef unsigned long long ull;
typedef __int128_t i128;
typedef pair<ll, ll> pll;
typedef stack<tuple<ll, ll, bool>> stpl;
const ll INF = LLONG_MAX;
struct edge{
    ll to, c, f, w, ptr; // DINH DEN, CAPACITY, CURRENT FLOW, WEIGHT
    edge(ll to, ll c, ll f, ll w, ll ptr) : to(to), c(c), f(f), w(w), ptr(ptr) {}
};
struct dinic{ // O(M * SQRT(N)), OVERALL MOST USEFUL, KHONG THE MIN COST
    vector<vector<edge>> adj;
    vector<ll> d, ptr;
    ll n, m, s, t;
    void init(){
        cin>>n>>m>>s>>t;
        adj.assign(n + 1, vector<edge>());
        d.assign(n + 1, INF);
        ptr.assign(n + 1, 0);
        for(ll i = 1; i<=m; i++){
            ll u, v, c; cin>>u>>v>>c;
            adj[u].push_back(edge(v, c, 0, 0, adj[v].size()));
            adj[v].push_back(edge(u, 0, 0, 0, adj[u].size() - 1));
        }
        solve();
    }
    void solve(){
        ll flow = 0;
        while(true){
            bfs();
            if(d[t] == INF) break;
            for(ll i = 1; i<=n; i++) ptr[i] = 0;
            while(ll delta = dfs(s, INF)){
                flow += delta;
            }
        }
        cout<<flow;
    }
    void bfs(){
        for(ll i = 1; i<=n; i++) d[i] = INF;
        d[s] = 0;
        queue<ll> q;
        q.push(s);
        while(!q.empty()){
            ll u = q.front();
            q.pop();
            for(edge &e : adj[u]){
                if(e.c - e.f == 0) continue;
                if(d[e.to] != INF) continue;
                d[e.to] = d[u] + 1;
                q.push(e.to);
            }
        }
    }
    ll dfs(ll u, ll curdelta){
        if(curdelta == 0) return 0;
        if(u == t) return curdelta;
        for(; ptr[u] < adj[u].size(); ptr[u]++){
            auto &e = adj[u][ptr[u]];
            if(e.c - e.f == 0) continue;
            if(d[e.to] != d[u] + 1) continue;
            ll delta = dfs(e.to, min(curdelta, e.c - e.f));
            if(delta == 0) continue;
            e.f += delta;
            adj[e.to][e.ptr].f -= delta;
            return delta;
        }
        return 0;
    }
};
struct ford{ // O(M * ~~~), FOR WEIGHTED-EDGES AND MIN COST
    vector<vector<edge>> adj;
    vector<ll> d, ptr, pi, inq, par, pari;
    ll n, m, s, t;
    void init(){
        cin>>n>>m>>s>>t;
        adj.assign(n + 1, vector<edge>());
        d.assign(n + 1, INF);
        ptr.assign(n + 1, 0);
        pi.assign(n + 1, INF);
        inq.assign(n + 1, 0);
        par.assign(n + 1, 0);
        pari.assign(n + 1, 0);
        for(ll i = 1; i<=m; i++){
            ll u, v, c, w; cin>>u>>v>>c>>w;
            adj[u].push_back(edge(v, c, 0, w, adj[v].size()));
            adj[v].push_back(edge(u, 0, 0, -w, adj[u].size() - 1));
        }
        solve();
    }
    void solve(){
        setpi();
        ll flow = 0, cost = 0;
        while(true){
            auto [u, v] = dijikstra();
            if(u <= 0) break;
            flow += u;
            cost += v * u; 
            ll cur = t;
            while(par[cur]){
                ll nxt = par[cur];
                adj[nxt][pari[cur]].f += u;
                adj[cur][adj[nxt][pari[cur]].ptr].f -= u;
                cur = nxt;
            }
        }
        cout<<flow<<" "<<cost;
    }
    pll dijikstra(){
        for(ll i = 1; i<=n; i++){
            d[i] = INF;
        }
        d[s] = 0;
        priority_queue<pll, vector<pll>, greater<pll>> pq;
        pq.push({0, s});
        while(!pq.empty()){
            auto [x, u] = pq.top();
            pq.pop();
            if(x != d[u]) continue;
            for(ll i = 0; i < adj[u].size(); i++){
                auto &e = adj[u][i];
                if(e.c - e.f == 0) continue;
                if(x + e.w + pi[u] - pi[e.to] < d[e.to]){
                    d[e.to] = x + e.w + pi[u] - pi[e.to];
                    pari[e.to] = i;
                    par[e.to] = u;
                    pq.push({d[e.to], e.to});
                }
            }
        }
        if(d[t] == INF){
            return {-1, -1};
        }
        ll cur = t;
        ll flow = INF, cost = 0;
        while(par[cur]){
            ll nxt = par[cur];
            flow = min(flow, adj[nxt][pari[cur]].c - adj[nxt][pari[cur]].f);
            cost += adj[nxt][pari[cur]].w;  
            cur = nxt;
        }
        for(ll i = 1; i<=n; i++){
            if(d[i] == INF) continue;
            pi[i] += d[i];
        }
        return {flow, cost};
    }
    void setpi(){
        pi[s] = 0;
        queue<pll> pq;
        pq.push({0, s});
        inq[s] = 1;
        while(!pq.empty()){
            auto [x, u] = pq.front();
            pq.pop();
            if(x != pi[u]) continue;
            inq[u] = 0;
            for(auto &e : adj[u]){
                if(e.c - e.f == 0) continue;
                if(x + e.w < pi[e.to]){
                    pi[e.to] = x + e.w;
                    if(!inq[e.to]){
                        pq.push({pi[e.to], e.to});
                        inq[e.to] = 1;
                    }
                }
            }
        }
    }
};
struct karp{ // O(M * SQRT(N)), FOR BIPARTITE ONLY
    vector<vector<ll>> adj;
    vector<ll> seen, dist, matchL, matchR;
    ll cnt, n, m, L, R, ite;
    void init(){
        cin>>L>>R>>m;
        n = L + R;
        matchL.assign(L + 1, 0);
        matchR.assign(R + 1, 0);
        seen.assign(L + 1, 0);
        dist.assign(L + 1, INF);
        adj.assign(L + 1, vector<ll>());
        for(ll i = 1; i<=m; i++){
            ll u, v; cin>>u>>v;
            adj[u].push_back(v);
        }
        solve();
    }       
    ll dfs(ll u){
        if(seen[u] == ite) return 0;
        seen[u] = ite;
        for(ll v : adj[u]){
            if(!matchR[v]){
                matchL[u] = v;
                matchR[v] = u;
                return 1;
            }
        }
        for(ll v : adj[u]){
            if(dist[matchR[v]] == dist[u] + 1 && dfs(matchR[v])){
                matchL[u] = v;
                matchR[v] = u;
                return 1;
            }
        }
        return 0;
    }
    void solve(){
        cnt = 0, ite = 0;
        while(true){
            queue<ll> q;
            for(ll i = 1; i<=L; i++){
                if(!matchL[i]){
                    q.push(i);
                    dist[i] = 0;
                }
                else dist[i] = INF;
            }
            while(!q.empty()){
                ll u = q.front();
                q.pop();
                for(ll v : adj[u]){
                    if(matchR[v] && dist[matchR[v]] == INF){
                        dist[matchR[v]] = dist[u] + 1;
                        q.push(matchR[v]);
                    }
                }
            }
            ll match = 0;
            ite++;
            for(ll i = 1; i<=L; i++){
                if(!matchL[i]){
                    match += dfs(i);
                }
            }
            if(!match) break;
            cnt += match;
        }
        cout<<cnt<<'\n';
        for(ll i = 1; i<=L; i++){
            if(matchL[i]){
                cout<<i<<" "<<matchL[i]<<'\n';
            }
        }
    }
};
// LUU Y, NEU LA DO THI HAI PHIA, CHUNG TA SE DAT C(U, V) = C(V, U) = CAP, NGUOC LAI CHI DAT C(U, V) = CAP


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    karp Karp;
    Karp.init();
}