#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ldb;
typedef unsigned long long ull;
typedef __int128_t i128;
typedef pair<ll, ll> pll;
typedef stack<tuple<ll, ll, bool>> stpl;
#define file "PERMUTATION_ORDER"
const ll N = 20;
ll t;
ll fac[N + 1];
vector<ll> perm;
ll used[N + 1];
vector<ll> original;
ll n, k;
void solve(ll pos, ll level){
    if(pos > n){
        for(ll i : perm) cout<<i<<" ";
        cout<<'\n';
        return;
    }
    ll i;
    for(i = 1; i<=n; i++){
        if(used[i]) continue;
        if(fac[n - pos] >= level) break;
        level -= fac[n - pos];
    }
    perm.push_back(i);
    used[i] = 1;
    solve(pos + 1, level);
}
void reverse_engineer(ll pos, ll level){
    if(pos > n){
        cout<<level<<'\n';
        return;
    }
    for(ll i = 1; i<=n; i++){
        if(used[i]) continue;
        if(i == original[pos - 1]) break;
        level += fac[n - pos];
    }
    used[original[pos - 1]] = 1;
    reverse_engineer(pos + 1, level);
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    if(fopen(file".INP", "r")){
        freopen(file".INP", "r", stdin);
        freopen(file".OUT", "w", stdout);
    }
    fac[0] = 1;
    for(ll i = 1; i<=N; i++){
        fac[i] = fac[i - 1] * i;
    }   
    cin>>t;
    while(t--){
        ll ti; cin>>ti;
        if(ti == 1){
            cin>>n>>k;
            for(ll i = 1; i<=n; i++) used[i] = 0;
            perm.clear();
            solve(1, k);
        }
        else if(ti == 2){
            original.clear();
            cin>>n;
            for(ll i = 0; i < n; i++){
                used[i + 1] = 0;
                ll x; cin>>x;
                original.push_back(x);
            }
            reverse_engineer(1, 1);
        }
    }
}