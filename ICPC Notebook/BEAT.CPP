#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ldb;
typedef unsigned long long ull;
typedef __int128_t i128;
typedef pair<ll, ll> pll;
typedef stack<tuple<ll, ll, bool>> stpl;
const ll N = 1e5, INF = LLONG_MAX;
// SGT BEAT FOR RANGE MIN AND RANGE ADD
struct node{
    ll sum, mx1, mx2, mxcnt, lazy;
    node() : sum(0), mx1(-INF), mx2(-INF), mxcnt(0), lazy(0) {}
};
node st[4 * N + 1]; // 1-BASED;
ll a[N + 1];
void pull(ll pos){
    st[pos].sum = st[2 * pos].sum + st[2 * pos + 1].sum;
    st[pos].mxcnt = 0;
    st[pos].mx1 = max(st[2 * pos].mx1, st[2 * pos + 1].mx1);
    if(st[2 * pos].mx1 == st[pos].mx1) st[pos].mxcnt += st[2 * pos].mxcnt;
    if(st[2 * pos + 1].mx1 == st[pos].mx1) st[pos].mxcnt += st[2 * pos + 1].mxcnt;
    st[pos].mx2 = max(st[2 * pos].mx2, st[2 * pos + 1].mx2);
    if(st[2 * pos].mx1 != st[pos].mx1) st[pos].mx2 = max(st[pos].mx2, st[2 * pos].mx1);
    if(st[2 * pos + 1].mx1 != st[pos].mx1) st[pos].mx2 = max(st[pos].mx2, st[2 * pos + 1].mx1);
}
void apply_min(ll pos, ll v){
    st[pos].sum -= (st[pos].mx1 - v) * st[pos].mxcnt;
    st[pos].mx1 = v;
}
void apply_add(ll pos, ll l, ll r, ll x){
    st[pos].sum += (r - l + 1) * x;
    st[pos].mx1 += x;
    if(st[pos].mx2 != -INF) st[pos].mx2 += x;
    st[pos].lazy += x;
}
void fix(ll pos, ll l, ll r){
    if(st[pos].lazy){
        if(l != r){
            ll m = (l + r)/2;
            apply_add(2 * pos, l, m, st[pos].lazy);
            apply_add(2 * pos + 1, m + 1, r, st[pos].lazy);
        }
        st[pos].lazy = 0;
    }
    if(l != r){
        if(st[2 * pos].mx1 > st[pos].mx1) apply_min(2 * pos, st[pos].mx1);
        if(st[2 * pos + 1].mx1 > st[pos].mx1) apply_min(2 * pos + 1, st[pos].mx1);
    }
}
void build(ll pos, ll l, ll r){
    if(l == r){
        st[pos].sum = st[pos].mx1 = a[l];
        st[pos].mxcnt = 1;
        return;
    }
    ll m = (l + r)/2;
    build(2 * pos, l, m);
    build(2 * pos + 1, m + 1, r);
    pull(pos);
}
void range_chmin(ll l, ll r, ll v, ll pos, ll lx, ll rx){ 
    fix(pos, lx, rx);
    if(lx > r || l > rx || st[pos].mx1 <= v) return;
    if(lx >= l && rx <= r && st[pos].mx2 < v){
        apply_min(pos, v);
        return;
    }
    fix(pos, lx, rx);
    ll m = (lx + rx)/2;
    range_chmin(l, r, v, 2 * pos, lx, m);
    range_chmin(l, r, v, 2 * pos + 1, m + 1, rx);
    pull(pos);
}
void range_add(ll l, ll r, ll v, ll pos, ll lx, ll rx){
    fix(pos, lx, rx);
    if(lx > r || l > rx) return;
    if(lx >= l && rx <= r){
        apply_add(pos, lx, rx, v);
        return;
    }
    fix(pos, lx, rx);
    ll m = (lx + rx)/2;
    range_add(l, r, v, 2 * pos, lx, m);
    range_add(l, r, v, 2 * pos + 1, m + 1, rx);
    pull(pos);
}
ll sum_query(ll l, ll r, ll pos, ll lx, ll rx){
    fix(pos, lx, rx);
    if(lx > r || l > rx) return 0;
    if(lx >= l && rx <= r) return st[pos].sum;
    fix(pos, lx, rx);
    ll m = (lx + rx)/2;
    return sum_query(l, r, 2 * pos, lx, m) + sum_query(l, r, 2 * pos + 1, m + 1, rx);
}

int main(){
    
}