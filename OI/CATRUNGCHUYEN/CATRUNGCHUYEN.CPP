#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ldb;
typedef unsigned long long ull;
typedef __int128_t i128;
typedef pair<ll, ll> pll;
typedef stack<tuple<ll, ll, bool>> stpl;
#define file "CATRUNGCHUYEN"
const ll N = 2e5 + 5, INF = 2e9;
ll n, k;
struct state{
    ll sum, cnt;
    state() : sum(0), cnt(0) {}
};
ll c[N];
ll a[N];
state check(ll lamba){
    priority_queue<pll, vector<pll>, greater<pll>> pq;
    for(ll i = n; i>=1; i--){
        if(c[i]){
            pq.push({a[i] - lamba, i});
        }
        else{
            pq.push({a[i], i});
        }
        ll len = n - i + 1;
        while(!pq.empty() && pq.size() > len/2){
            pq.pop();
        }
    }
    state ans;
    while(!pq.empty()){
        auto [u, v] = pq.top();
        pq.pop();
        ans.sum += u;
        if(c[v]) ans.cnt++;
    }
    return ans;
}
bool valid(){
    priority_queue<ll, vector<ll>, greater<ll>> pq;
    for(ll i = n; i>=1; i--){
        if(c[i]){
            pq.push(1);
        }
        else{
            pq.push(0);
        }
        ll len = n - i + 1;
        while(pq.size() > len/2){
            pq.pop();
        }
    }
    ll sum = 0;
    while(!pq.empty()){
        sum += pq.top();
        pq.pop();
    }
    return sum >= k;
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    if(fopen(file".INP", "r")){
        freopen(file".INP", "r", stdin);
        freopen(file".OUT", "w", stdout);
    }
    cin>>n>>k;
    for(ll i = 1; i<=n; i++){
        cin>>a[i];
    }
    for(ll i = 1; i<=n; i++){
        cin>>c[i];
    }
    if(!valid()){
        cout<<-1;
        return 0;
    }
    ll l = -INF, r = k * INF;
    ll lamba = -INF;
    bool found = false;
    while(l <= r){
        ll m = (l + r)/2;
        state candidate = check(m);
        if(candidate.cnt >= k){
            found = true;
            //found = true;
            lamba = m;
            l = m + 1;
        }
        else r = m - 1;
    }
    // if(!found){
    //     cout<<-1;
    //     return 0;
    // }
    state ans = check(lamba);
    //cout<<lamba<<" "<<ans.sum<<" "<<ans.cnt<<'\n';
    cout<<ans.sum + k * lamba;
}
