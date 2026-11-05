#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ldb;
typedef unsigned long long ull;
typedef __int128_t i128;
typedef pair<ll, ll> pll;
typedef stack<tuple<ll, ll, bool>> stpl;
#define file "JJOOII2"
const ll N = 2e5 + 5;
ll n, k;
string s;

ll pj[N], po[N], pi[N];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    if(fopen(file".INP", "r")){
        freopen(file".INP", "r", stdin);
        freopen(file".OUT", "w", stdout);
    }
    cin>>n>>k>>s;
    s = " " + s;
    for(ll i = 1; i<=n; i++){
        pj[i] = pj[i - 1];
        po[i] = po[i - 1];
        pi[i] = pi[i - 1];
        if(s[i] == 'J') pj[i]++;
        if(s[i] == 'O') po[i]++;
        if(s[i] == 'I') pi[i]++;
    }
    ll ans = LLONG_MAX;
    ll l = 1, r = 1, r2 = 1;
    for(ll i = 1; i<=n; i++){
        if(pj[i] - pj[l - 1] < k) continue;
        if(r < i) r = i;
        while(r <= n && po[r] - po[i] < k){
            r++;
        }
        if(r > n) break;
        if(r2 < r) r2 = r;
        while(r2 <= n && pi[r2] - pi[r] < k){
            r2++;
        }
        if(r2 > n) break;
        while(l < i && pj[i] - pj[l] >= k){
            l++;
        }
        ll cost1 = (i - l + 1 - (pj[i] - pj[l - 1]));
        ll cost2 = (r - i - (po[r] - po[i]));
        ll cost3 = (r2 - r - (pi[r2] - pi[r]));
        ans = min(ans, cost1 + cost2 + cost3);
    }   
    if(ans == LLONG_MAX) cout<<-1;
    else cout<<ans;
}
