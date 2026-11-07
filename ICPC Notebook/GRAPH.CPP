#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ldb;
typedef unsigned long long ull;
typedef __int128_t i128;
typedef pair<ll, ll> pll;
typedef stack<tuple<ll, ll, bool>> stpl;
#define file "MARISA"
const ll N = 1e5 + 5;
vector<ll> adj[N];
vector<tuple<ll, ll, ll>> edges;
ll Ideg[N], dis[N], state[N], par[N];
ll n, m;
bool topo(vector<ll> &vec){
    vec.clear();
    fill(Ideg + 1, Ideg + 1 + n, 0);
    for(ll i = 1; i<=n; i++){
        for(ll j : adj[i]){
            Ideg[j]++;
        }
    }
    queue<ll> q;
    for(ll i = 1; i<=n; i++){
        if(!Ideg[i]) q.push(i);
    }
    while(!q.empty()){
        ll u = q.front();
        vec.push_back(u);
        q.pop();
        for(ll v : adj[u]){
            Ideg[v]--;
            if(!Ideg[v]) q.push(v);
        }
    }
    return vec.size() == n;
}
vector<ll> cyc;
bool dfs_cyc(ll u){
    state[u] = 1;
    for(ll v : adj[u]){
        if(state[v] == 0){
            par[v] = u;
            if(dfs_cyc(v)) return true;
        }
        else if(state[v] == 1){
            cyc.push_back(v);
            for(ll x = u; x != v; x = par[x]) cyc.push_back(x);
            cyc.push_back(v);
            reverse(cyc.begin(), cyc.end());
            return true;
        }
    }
    state[u] = 2;
    return false;
}
vector<ll> path;
vector<vector<ll>> cycs;
void johnson(ll s, ll u){
    state[u] = 1;
    path.push_back(u);
    for(ll v : adj[u]){
        if(v == s){
            vector<ll> cur = path;
            cur.push_back(s);
            cycs.push_back(cur);
        }
        else if(v > s && !state[v]){
            johnson(s, v);
        }
    }
    path.pop_back();
    state[u] ^= 1;
}
void all_cyc(){
    cycs.clear();
    for(ll s = 1; s<=n; s++){
        path.clear();
        fill(state + 1, state + 1 + n, 0);
        johnson(s, s);
    }
}
bool bellman(ll s){
    fill(dis + 1, dis + 1 + n, LLONG_MAX);
    fill(par + 1, par + 1 + n, 0);
    dis[s] = 0;
    for(ll i = 1; i < n; i++){
        bool shifted = false;
        for(auto [u, v, w] : edges){
            if(dis[u] == LLONG_MAX) continue;
            if(dis[u] + w < dis[v]){
                dis[v] = dis[u] + w;
                shifted = true;
                par[v] = u;
            }
        }
        if(!shifted) break;
    }
    for(auto [u, v, w] : edges){
        if(dis[u] != LLONG_MAX && dis[u] + w < dis[v]) return false;
    }
    return true;
}
bool floyd(vector<vector<ll>> &d){
    for(ll i = 1; i<=n; i++){
        for(ll j = 1; j<=n; j++){
            d[i][j] = (i == j ? 0 : LLONG_MAX);
        }
    }
    for(auto [u, v, w] : edges){
        d[u][v] = min(d[u][v], w);
        // NEU UNDIRECTED THI SET CA D[V][U]
    }
    for(ll k = 1; k<=n; k++){
        for(ll i = 1; i<=n; i++){
            if(d[i][k] == LLONG_MAX) continue;
            for(ll j = 1; j<=n; j++){
                if(d[k][j] == LLONG_MAX) continue;
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
    for(ll i = 1; i<=n; i++){
        if(d[i][i] < 0) return false;
    }
    return true;
}

int main(){
}