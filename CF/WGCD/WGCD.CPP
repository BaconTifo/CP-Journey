#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ldb;
typedef unsigned long long ull;
typedef __int128_t i128;
typedef pair<ll, ll> pll;
typedef stack<tuple<ll, ll, bool>> stpl;
#define file "WGCD"
const ll N = 1e5;

ll T, H;

ll pi[N + 1];
ll w[N + 1];
vector<ll> fac[N + 1];

ll dp(ll x, ll lim){
    ll n = fac[x].size();
    //cout<<n<<'\n';
    //return 0;
    ll ans = lim;
    for(ll i = 1; i < (1<<n); i++){
        //if(!__builtin_popcount(i)) continue;
        ll p = 1;
        for(ll j = 0; j < n; j++){
            if((i>>j) & 1){
                p *= fac[x][j];
            }
        }
        if(__builtin_popcount(i) % 2){
            ans -= lim/p;
        }
        else ans += lim/p;
    }
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    if(fopen(file".INP", "r")){
        freopen(file".INP", "r", stdin);
        freopen(file".OUT", "w", stdout);
    }
    cin>>T>>H;
    for(ll i = 1; i<=H; i++){
        pi[i] = i - 1;
        ll x = i;
        cin>>w[i];
        for(ll j = 2; j * j <= x; j++){
            if(x % j == 0){
                fac[i].push_back(j);
                pi[i] -= x/j;
                while(x && x % j == 0){
                    x/=j;
                }
            }
        }
        if(x > 1){
            fac[i].push_back(x);
            pi[i]--;
        }
    }
    while(T--){
        ll n, m; cin>>n>>m;
        ll ans = 0;
        for(ll i = 1; i<=min(n, m); i++){
            ll cnt = 0;
            ll y = min(n, m)/i;
            for(ll x = 1; i * x <= max(n, m); x++){
                cnt += dp(x, y);
            }
            //cout<<i<<" "<<cnt<<'\n';
            ans += cnt * w[i];
        }
        cout<<ans<<'\n';
    }
    //cout<<dp(3, 2);
}
