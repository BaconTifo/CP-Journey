#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ldb;
typedef unsigned long long ull;
typedef __int128_t i128;
typedef pair<ll, ll> pll;
typedef stack<tuple<ll, ll, bool>> stpl;

// PERSISTENT USING VECTOR
struct node{
    ll l, r;
    node() : l(0), r(0) {}
};
vector<node> pool(1); // POOL[0] IS NOTHING VALUE
ll make_new(node cur){
    pool.push_back(cur);
    return pool.size() - 1;
}
ll update(ll i, ll pos_id, ll l, ll r){
    ll cur = make_new(pool[pos_id]); // MAKE NODE
    if(l == r) return cur;
    ll m = (l + r)/2;
    if(i <= m){
        ll old_l = pool[pos_id].l;
        ll new_l = update(i, old_l, l, m);
        pool[cur].l = new_l;
    }
    else{
        ll old_r = pool[pos_id].r;
        ll new_r = update(i, old_r, m + 1, r);
        pool[cur].r = new_r;  
    }
    return cur;
}
vector<ll> root; // NODE INDEX OF TIME


int main(){
    
}