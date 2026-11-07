#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ldb;
typedef unsigned long long ull;
typedef __int128_t i128;
typedef pair<ll, ll> pll;
typedef stack<tuple<ll, ll, bool>> stpl;
#define file "MARISA"
ll ext_euc(ll a, ll b, ll &x, ll &y){
    if(!b){
        x = (a >= 0 ? 1 : -1);
        y = 0;
        return abs(a);
    }
    ll x1, y1;
    ll d = ext_euc(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a/b);
    return d;
}
bool inv_mod(ll a, ll mod, ll &inv){
    if(mod <= 0) return false;
    a %= mod;
    if(a < 0) a += mod;
    ll x, y;
    ll d = ext_euc(a, mod, x, y);
    if(d != 1) return false;
    inv = x % mod;
    if(inv < 0) inv += mod;
    return true;
}
bool diophantine(ll a, ll b, ll c, ll &x, ll &y){
    if(a == 0 && b == 0){
        return c == 0;
    }
    ll d = ext_euc(a, b, x, y);
    if(c % d != 0) return false;
    x *= c/d;
    y *= c/d;
    return true;
} // CAC NGHIEM KHAC BAO GOM (x + b/d * t, y - a/d * t)
bool crt_merge(ll &a, ll &m, ll b, ll n){
    ll d = __gcd(m, n);
    ll dif = (i128)b - a;
    if(dif % d != 0) return false;
    ll mod = n/d;
    ll t = 0;
    if(mod != 1){
        ll x, y;
        ext_euc(m/d, mod, x, y);
        t = (i128)((i128)(dif/d) * x) % mod;
        if(t < 0) t+= mod;
    }
    ll lcm = (i128)(m/d) * n;
    a = ((i128)a + (i128)m * t) % lcm;
    if(a < 0) a+=lcm;
    m = lcm;
    return true;
}
bool crt(vector<pll> eq, ll &x, ll &mod){
    x = 0;
    mod = 1;
    for(auto [a, m] : eq){
        if(m <= 0) return false;
        a %= m;
        if(a < 0) a+=m;
        if(!crt_merge(x, mod, a, m)) return false;
    }
    return true;
}
ll modpow(ll base, ll expo, ll mod){
    ll res = 1;
    base %= mod;
    while(expo){
        if(expo & 1) res = (res * base) % mod;
        base = (base * base) % mod;
        expo>>=1;
    }
    return res;
}
vector<ll> phi(ll n){
    vector<ll> p(n + 1);
    for(ll i = 1; i<=n; i++) p[i] = i;
    for(ll i = 2; i <= n; i++){
        if(p[i] == i){
            for(ll j = i; j<=n; j+=i){
                p[j] -= p[j]/i;
            }
        }
    }
    return p;
}



int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    if(fopen(file".INP", "r")){
        freopen(file".INP", "r", stdin);
        freopen(file".OUT", "w", stdout);
    }
    
}