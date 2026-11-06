#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ldb;
typedef unsigned long long ull;
typedef __int128_t i128;
typedef pair<ll, ll> pll;
typedef stack<tuple<ll, ll, bool>> stpl;
#define file "LAMU4C"
const ll N = 2e5 + 5;
ll t;
ll a[N];
ll n, q;
struct item{
    ll lbegin, lend, rbegin, rend, lsize, rsize, curgcd;
    item() : lbegin(0), lend(0), rbegin(0), rend(0), lsize(0), rsize(0), curgcd(0) {}
    item(ll i){
        lbegin = lend = rbegin = rend = i;
        lsize = rsize = 1;
        curgcd = 1;
    }
    item(item left, item right){
        if(!left.lsize) *this = right;
        else if(!right.rsize) *this = left;
        else{
            if(left.lbegin == left.rbegin && right.rbegin == right.lbegin){
                if(a[left.rend] <= a[right.lbegin]){
                    lbegin = left.lbegin;
                    lend = right.rend;
                    rbegin = left.lend;
                    rend = right.rend;
                    lsize = rend - rbegin + 1;
                    rsize = rend - rbegin + 1;
                    curgcd = lsize;
                }
                else{
                    lbegin = left.lbegin;
                    lend = left.lend;
                    lsize = left.lsize;
                    rbegin = right.rbegin;
                    rend = right.rend;
                    rsize = right.rsize;
                    if(rend == n){
                        curgcd = left.curgcd;
                    }
                    else{
                        curgcd = __gcd(left.curgcd, right.curgcd);
                    }
                }
            }
            else if(right.rbegin == right.lbegin){
                if(a[left.rend] <= a[right.lbegin]){
                    lbegin = left.lbegin;
                    lend = left.lend;
                    lsize = left.lsize;
                    rbegin = left.rbegin;
                    rend = right.rend;
                    rsize = rend - rbegin + 1;
                    if(rend == n){
                        curgcd = left.curgcd;
                    }
                    else{
                        curgcd = __gcd(left.curgcd, rsize);
                    }
                }
                else{
                    lbegin = left.lbegin;
                    lend = left.lend;
                    lsize = left.lsize;
                    rbegin = right.rbegin;
                    rend = right.rend;
                    rsize = right.rsize;
                    if(rend == n){
                        curgcd = left.curgcd;
                    }
                    else{
                        curgcd = __gcd(left.curgcd, right.curgcd);
                    }
                }
            }
            else{
                lbegin = left.lbegin;
                lend = left.lend;
                lsize = left.lsize;
                rbegin = left.rbegin;
                rend = right.rend;
                rsize = right.rsize;
                if(a[left.rend] <= a[right.lbegin]){
                    ll newlen = right.lend - left.rbegin + 1;
                    curgcd = __gcd(left.curgcd, right.curgcd);
                    curgcd = __gcd(curgcd, newlen);
                }
                else{
                    curgcd = __gcd(left.curgcd, right.curgcd);
                }
            }
        }
    }
};
item st[4 * N];
void build(ll node, ll l, ll r){
    if(l == r){
        st[node] = item(l);
        return;
    }
    ll m = (l + r)/2;
    build(2 * node, l, m);
    build(2 * node + 1, m + 1, r);
    st[node] = item(st[2 * node], st[2 * node + 1]);
}
void update(ll i, ll node, ll l, ll r){
    if(l == r){
        st[node] = item(l);
        return;
    }
    ll m = (l + r)/2;
    if(i <= m) update(i, 2 * node, l, m);
    else update(i, 2 * node + 1, m + 1, r);
    st[node] = item(st[2 * node], st[2 * node + 1]);
}

ll demuoc(ll x){
    ll ans = 0;
    for(ll i = 1; i * i <=x; i++){
        if(x % i == 0){
            ans++;
            if(x/i != i) ans++;
        }
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
    cin>>t;
    while(t--){
        cin>>n>>q;
        for(ll i = 1; i<=n; i++){
            cin>>a[i];
        }
        build(1, 1, n);
        cout<<demuoc(st[1].curgcd)<<" "<<st[1].curgcd<<'\n';
        while(q--){
            ll i, v; cin>>i>>v;
            a[i] = v;
            update(i, 1, 1, n);
            cout<<demuoc(st[1].curgcd)<<" "<<st[1].curgcd<<'\n';
        }
    }
}   
