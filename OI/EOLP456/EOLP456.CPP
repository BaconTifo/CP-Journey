#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ldb;
typedef __int128_t i128;
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef stack<tuple<ll, ll, bool>> stpl;
#define file "EOLP456"
const ll N = 16;


ll dp[(1<<N)][N + 1];
ll a[N + 1], used[N + 1];
ll n, m, k;
vector<ll> perm;

void solve(ll pos, ll level, ll mask){
    if(pos > n){
        for(ll i : perm) cout<<i<<" ";
        return;
    }
    ll cnt = 0;
    ll i;
    for(i = 1; i<=n; i++){
        if(used[i]) continue;
        if(!((mask>>(i - 1)) & 1)) continue;
        if(!perm.empty()){
            if(__gcd(perm.back(), a[i]) < k) continue;
        }
        cnt += dp[mask][i];
        if(cnt >= level) break;
    }
    if(cnt < level){
        cout<<-1;
        return;
    }
    used[i] = 1;
    perm.push_back(a[i]);
    cnt -= dp[mask][i];
    //cout<<pos<<" "<<i<<" "<<dp[mask][i]<<'\n';
    level -= cnt;
    mask ^= (1<<(i - 1));
    solve(pos + 1, level, mask);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    if (fopen(file".INP", "r")) {
        freopen(file".INP", "r", stdin);
        freopen(file".OUT", "w", stdout);
    }
    cin>>n>>m>>k;
    for(ll i = 1; i<=n; i++){
        cin>>a[i];
    }
    sort(a + 1, a + 1 + n);
    for(ll i = 1; i<=n; i++){
        dp[(1<<(i - 1))][i] = 1;
    }
    for(ll mask = 1; mask < (1<<n); mask++){
        //if(__builtin_popcount(mask) == 0) continue;
        for(ll x = 1; x<=n; x++){
            if((mask>>(x - 1)) & 1) continue;
            for(ll y = 1; y<=n; y++){
                if(!((mask>>(y - 1)) & 1)) continue;
                if(__gcd(a[x], a[y]) < k) continue;
                //cout<<a[x]<<" "<<a[y]<<'\n';
                // if(mask | (1<<(x - 1)) == 3){
                //     cout<<a[x]<<" "<<a[y]<<'\n';
                // }
                dp[mask | (1<<(x - 1))][x] += dp[mask][y];
            }
        }
    }
    // for(ll i = 1; i<=n; i++){
    //     cout<<i<<": "<<'\n';
    //     for(ll mask = 0; mask < (1<<n); mask++){
    //         for(ll j = 1; j<=n; j++){
    //             cout<<((mask>>(j - 1)) & 1);
    //         }
    //         cout<<": "<<dp[mask][i]<<'\n';
    //     }
    //     cout<<'\n';
    // }
    solve(1, m, (1<<n) - 1);
}
