#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ldb;
typedef unsigned long long ull;
typedef __int128_t i128;
typedef pair<ll, ll> pll;
typedef stack<tuple<ll, ll, bool>> stpl;
const ll N = 1e5, M = 1e5; // GOM CAC THUAT TOAN CO BAN TIM KHOP, CAU, SCC, BCC, EULER PATH
struct edge{
    ll to, weight, index;
};
ll num[N + 1], low[N + 1], del[N + 1];
vector<edge> adj[N + 1];
ll isB[M + 1], isC[N + 1];
stack<ll> st, st_e;
bool used[M + 1];
ll ptr[M + 1];
ll timer;
void dfs(ll u, ll p){ // DFS TREE + TIM KHOP/CAU
    timer++; low[u] = num[u] = timer;
    ll childcnt = 0;
    for(edge e : adj[u]){
        if(e.to == p) continue;
        if(!num[e.to]){
            childcnt++;
            dfs(e.to, u);
            low[u] = min(low[u], low[e.to]);
            if(low[e.to] == num[e.to]){ // CANH CAU
                isB[e.index] = 1;
            }
            if(p == -1){
                if(childcnt > 1) isC[u] = 1; // DINH KHOP
            }
            else{
                if(low[e.to] >= num[u]) isC[u] = 1; // DINH KHOP
            }
        }
        else{
            low[u] = min(low[u], num[e.to]);
        }
    }
}
void scc(ll u, ll p){ // STRONGLY CONNECTED COMPONENT
    st.push(u);
    timer++; low[u] = num[u] = timer;
    for(edge e : adj[u]){
        if(del[e.to]) continue;
        if(!num[e.to]){
            scc(e.to, u);
            low[u] = min(low[u], low[e.to]);
        }
        else low[u] = min(low[u], num[e.to]);
    }
    if(low[u] == num[u]){ // FOUND SCC;
        ll v;
        do{
            v = st.top();
            st.pop();
            del[v] = 1;
        } while(v != u);
    }
}
void bcc(ll u, ll p_edge){ // BICONNECTED COMPONENT
    timer++;
    low[u] = num[u] = timer;
    for(edge e: adj[u]){
        if(e.index == p_edge) continue;
        if(!num[e.to]){
            st_e.push(e.index);
            bcc(e.to, e.index);
            low[u] = min(low[u], low[e.to]);
            if(low[e.to] >= num[u]){
                ll v;
                do{
                    v = st_e.top();
                    st_e.pop();
                } while(v != e.index); // TIM DUOC BCC
            }
        }
        else{
            if(num[e.to] < num[u]){
                st_e.push(e.index);
                low[u] = min(low[u], num[e.to]);
            }
        }
    }
}
list<ll> euler_walk(ll u){ // IMPLEMENT BANG LINKED LIST
    list<ll> ans;
    ans.push_back(u);
    while(!adj[u].empty()){
        ll v = adj[u].back().to;
        ll index = adj[u].back().index;
        adj[u].pop_back();
        if(used[index]) continue;
        used[index] = 1;
        u = v;
        ans.push_back(v);
    }
    for(auto it = ++ans.begin(); it != ans.end(); it++){
        auto t = euler_walk(*it);
        t.pop_back();
        ans.splice(it, t);
    }
    return ans;
}
vector<ll> euler_circuit(ll u, ll m){ // m la so canh
    vector<ll> ans, path;
    path.push_back(u);
    while(!path.empty()){
        ll v = path.back();
        while(ptr[v] < adj[v].size() && used[adj[v][ptr[v]].index]) ptr[v]++;
        if(ptr[v] == adj[v].size()){
            ans.push_back(v);
            path.pop_back();
        }
        else{
            edge e = adj[v][ptr[v]];
            ptr[v]++;
            if(used[e.index]) continue;
            used[e.index] = 1;
            path.push_back(e.to);
        }
    }
    reverse(ans.begin(), ans.end());
    if(ans.size() != m + 1 || ans.front() != ans.back()) return {};
    return ans;
}

int main(){
    
}