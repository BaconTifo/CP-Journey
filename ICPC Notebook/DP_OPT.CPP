#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ldb;
typedef unsigned long long ull;
typedef __int128_t i128;
typedef pair<ll, ll> pll;
typedef stack<tuple<ll, ll, bool>> stpl;
const ll INF = LLONG_MAX;
// CHT VA LICHAO TREE CHI DUNG KHI DP[I] CO DANG U + FJ(X), VOI U PHU THUOC VAO I VA FJ(X)
// LA 1 HAM CO DANG AX + B VOI A, B THEO J VA X THEO I
// CHI NEN CHT KHI SLOPE MONOTONIC VA BIEN X MONOTONIC, CON LAI LICHAO
const ll N = 1e5;
struct line{
    ll a, b;
    line() : a(0), b(0) {}
    line(ll a, ll b) : a(a), b(b) {}
    ll calc(ll x){
        return a * x + b;
    }
    ll slope(){
        return a;
    }
    ll add(ll x, ll y){
        return (max(x, y) == INF ? INF : x + y);
    }
    void operator+=(line k){
        a = add(a, k.a);
        b = add(b, k.b);
    }
};
// CHT
line f[N + 1];
ldb slope(ll i, ll j){
    return ldb(f[j].b - f[i].b) * ldb(f[i].a - f[j].a); 
}
bool decreasing(ll i, ll j, ll k){
    return ((i128)f[j].b - f[i].b)*((i128)f[j].a - f[k].a) >= ((i128)f[k].b - f[j].b)*((i128)f[i].a - f[j].a);
}
vector<ll> get_dp(ll n){ // TINH MIN DP (LAM NGC LAI KHI TINH MAX)
    vector<ll> dp(n + 1, 0);
    deque<ll> dq;
    dq.push_back(0);
    for(ll i = 1; i<=n; i++){
        while(dq.size() > 1 && f[dq[0]].calc(i) > f[dq[1]].calc(i)) dq.pop_front();
        dp[i] = f[dq[0]].calc(i);
        while(dq.size() > 1 && decreasing(dq[dq.size() - 2], dq.back(), i)) dq.pop_back();
        dq.push_back(i);
    }
    return dp;
}
// LICHAO + LAZYYY
line g[4 * N + 1]; // DE TINH MIN NHE
line lazy[4 * N + 1];
void build(ll pos, ll l, ll r){
    g[pos] = line(0, INF);
    if(l == r){
        return;
    }
    ll m = (l + r)/2;
    build(2 * pos, l, m);
    build(2 * pos + 1, m + 1, r);
}
void apply(ll pos, line f){
    g[pos] += f;
    lazy[pos] += f;
}
void down(ll pos, ll l, ll r){
    if(!lazy[pos].a && !lazy[pos].b) return;
    if(l != r){
        apply(2 * pos, lazy[pos]);
        apply(2 * pos + 1, lazy[pos]);
    }
    lazy[pos] = line(0, 0);
}
void update(line cur, ll pos, ll l, ll r){ // CHEN DOAN THANG
    if(l == r){
        g[pos] = (cur.calc(l) < g[pos].calc(l) ? cur : g[pos]);
        return;
    }
    ll m = (l + r)/2;
    down(pos, l, r);
    if(cur.calc(m) < g[pos].calc(m)) swap(cur, g[pos]);
    if(cur.slope() > g[pos].slope()) update(cur, 2 * pos, l, m);
    if(cur.slope() < g[pos].slope()) update(cur, 2 * pos + 1, m + 1, r);
}
void push(ll pos, ll l, ll r){
    ll m = (l + r)/2;
    if(g[pos].b != INF){
        if(l != r){
            update(g[pos], 2 * pos, l, m);
            update(g[pos], 2 * pos + 1, m + 1, r);
        }
        g[pos] = line(0, INF);
    }
}
void insert(ll l, ll r, line cur, ll pos, ll lx, ll rx){
    if(lx > r || l > rx) return;
    if(lx >= l && rx <= r){
        update(cur, pos, lx, rx);
        return;
    }
    ll m = (lx + rx)/2;
    down(pos, lx, rx);
    insert(l, r, cur, 2 * pos, lx, m);
    insert(l, r, cur, 2 * pos + 1, m + 1, rx);
}
void increase(ll l, ll r, line cur, ll pos, ll lx, ll rx){
    if(lx > r || l > rx) return;
    if(lx >= l && rx <= r){
        apply(pos, cur);
        return;
    }
    down(pos, lx, rx);
    push(pos, lx, rx);
    ll m = (lx + rx)/2;
    increase(l, r, cur, 2 * pos, lx, m);
    increase(l, r, cur, 2 * pos + 1, m + 1, rx);
}
ll query(ll x, ll pos, ll l, ll r){
    if(l == r){
        return g[pos].calc(x);
    }
    down(pos, l, r);
    ll cur = g[pos].calc(x);
    ll m = (l + r)/2;
    if(x <= m) cur = min(cur, query(x, 2 * pos, l, m));
    else cur = min(cur, query(x, 2 * pos + 1, m + 1, r));
    return cur;
}

int main(){
    
}