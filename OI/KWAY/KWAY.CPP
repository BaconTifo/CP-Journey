#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ldb;
typedef unsigned long long ull;
typedef __int128_t i128;
typedef pair<ll, ll> pll;
typedef stack<tuple<ll, ll, bool>> stpl;
#define file "KWAY"
const ll N = 105;
ll n, m, k, s, f;
struct edge{
    ll to, f, c, w, ptr;
};
vector<edge> adj[N];
ll par[N];
ll ford(){
    fill(par + 1, par + 1 + n, 0);
    par[s] = -1;
    queue<ll> q;
    q.push(s);
    while(!q.empty()){
        ll u = q.front();
        q.pop();
        for(auto &e : adj[u]){
            if(e.c - e.f == 0) continue;
            if(par[e.to]) continue;
            par[e.to] = u;
            q.push(e.to);
        }
    }
    ll flow = LLONG_MAX;
    
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    if(fopen(file".INP", "r")){
        freopen(file".INP", "r", stdin);
        freopen(file".OUT", "w", stdout);
    }
    cin>>n>>m>>k>>s>>f;
    for(ll i = 1; i<=m; i++){
        ll u, v, w; cin>>u>>v>>w;
        adj[u].push_back({v, 1, 0, w, ll(adj[v].size())});
        adj[v].push_back({u, 1, 0, w, ll(adj[u].size() - 1)});
    }
    ll cost = 0;
    vector<vector<ll>> ans;
    while(k){
        ll cost = ford();
    }
}
