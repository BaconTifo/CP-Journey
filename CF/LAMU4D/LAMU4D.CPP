#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ldb;
typedef unsigned long long ull;
typedef __int128_t i128;
typedef pair<ll, ll> pll;
typedef stack<tuple<ll, ll, bool>> stpl;
#define file "LAMU4D"
const ll N = 1e6;


ll a[N + 1];
ll dp[N];
ll n;

bool good(ll x){
    while(x){
        ll cur = x % 10;
        if(cur + cur > 9) return false;
        x/=10;
    }
    return true;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    if(fopen(file".INP", "r")){
        freopen(file".INP", "r", stdin);
        freopen(file".OUT", "w", stdout);
    }
    memset(dp, 0, sizeof(dp));
    cin>>n;
    for(ll i = 1; i<=n; i++){
        cin>>a[i];
        dp[a[i]]++;
        //cout<<dp[a[i]]<<'\n';
    }
    ll curpower = 1;
    for(ll j = 1; j<=6; j++){
        for(ll i = 0; i < N; i++){
            ll curdigit = (i/curpower) % 10;
            if(curdigit){
                dp[i] += dp[i - curpower];
            }
        }
        curpower *= 10;
    }
    ll ans = 0;
    for(ll i = 1; i<=n; i++){
        ll rev = N - a[i] - 1;
        //cout<<rev<<" "<<dp[rev]<<'\n';
        ll cnt = dp[rev] - good(a[i]);
        ans += cnt;
    }
    cout<<ans/2;
}
