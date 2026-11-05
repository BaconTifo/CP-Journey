#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ldb;
typedef unsigned long long ull;
typedef __int128_t i128;
typedef pair<ll, ll> pll;
typedef stack<tuple<ll, ll, bool>> stpl;
#define file "LAMU4B"
const ll M = 1e9 + 7, BASE = 33;
ll n;
string a;
map<pair<string, string>, ll> cnt;
void build1(){
    for(ll i = 0; i < (1<<n); i++){
        ll red = 0, blue = 0;
        string r, bl;
        for(ll j = 0; j < n; j++){
            if((i >> j) & 1){
                red = (red + (a[j] - 'a')) * BASE % M;
                r.push_back(a[j]);
            }
        }
        for(ll j = n - 1; j>=0; j--){
            if((i>>j) & 1) continue;
            blue = (blue + (a[j] - 'a')) * BASE % M;
            bl.push_back(a[j]);
        }
        //cout<<r<<" "<<bl<<'\n';
        //cnt[{red, blue}]++;
        cnt[{r, bl}]++;
    }
    //cout<<'\n';
}
ll ans = 0;
void build2(){
    for(ll i = 0; i < (1<<n); i++){
        ll red = 0, blue = 0;
        string r, bl;
        for(ll j = n - 1; j >=0; j--){
            if((i >> j) & 1){
                blue = (blue + (a[j + n] - 'a')) * BASE % M;
                bl.push_back(a[j + n]);
            }
        }
        for(ll j = 0; j < n; j++){
            if((i>>j) & 1) continue;
            red = (red + (a[j + n] - 'a')) * BASE % M;
            r.push_back(a[j + n]);
        }
        // if(cnt.count({blue, red})){
        //     ans += cnt[{blue, red}];
        // }
        if(cnt.count({bl, r})){
            //cout<<bl<<" "<<r<<" "<<cnt[{bl, r}]<<'\n';
            ans += cnt[{bl, r}];
        }
        //cout<<bl<<" "<<r<<'\n';
    }
    //cout<<'\n';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    if(fopen(file".INP", "r")){
        freopen(file".INP", "r", stdin);
        freopen(file".OUT", "w", stdout);
    }
    cin>>n>>a;
    build1();
    build2();
    // for(auto i : cnt){
    //     cout<<i.first.first<<" "<<i.first.second<<'\n';
    // }
    cout<<ans;
}
