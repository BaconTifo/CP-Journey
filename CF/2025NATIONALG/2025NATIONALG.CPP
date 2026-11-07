#include <bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long double ldb;
typedef unsigned long long ull;
typedef __int128_t i128;
typedef pair<ll, ll> pll;
typedef stack<tuple<ll, ll, bool>> stpl;
#define file "2025NATIONALG"
const ll N = 3e5;
struct node{
    ll l, r, val;
    bool operator<(const node &other)const{
        return l < other.l;
    }
};
ll n, q;
set<node> s;
ll cnt[N + 1], sum[N + 1];

void update(ll u, ll v){
    ll i = u;
    while(i <= N){
        cnt[i] += v;
        sum[i] += v * u;
        i += (i & (-i));
    }
}
void assign_value(ll l, ll r, ll value){
    auto itl = prev(s.upper_bound({l, 0, 0}));
    auto itr = prev(s.upper_bound({r, 0, 0}));
    ll oldl = itl->l;
    ll oldlv = itl->val;
    ll oldr = itr->r;
    ll oldrv = itr->val;
    auto aft = next(itr);
    for(auto it = itl; it != aft; ++it){
        update(it->r - it->l + 1, -1);
    }
    s.erase(itl, aft);
    if(oldl < l && oldlv != value){
        s.insert({oldl, l - 1, oldlv});
        update(l - oldl, 1);
    }
    else if(oldl < l) l = oldl;
    if(oldr > r && oldrv != value){
        s.insert({r + 1, oldr, oldrv});
        update(oldr - r, 1);
    }
    else if(oldr > r) r = oldr;
    auto it = s.lower_bound({l, 0, 0});
    if(it != s.begin()){
        auto p = prev(it);
        if(p->val == value){
            l = p->l;
            update(p->r - p->l + 1, -1);
            s.erase(p);
        }
    }
    it = s.lower_bound({r + 1, 0, 0});
    if(it != s.end()){
        if(it->val == value){
            update(it->r - it->l + 1, -1);
            r = it->r;
            s.erase(it);
        }
    }
    s.insert({l, r, value});
    update(r - l + 1, 1);
}
pll get(ll u){
    ll ans = 0, res = 0;
    while(u){
        ans += cnt[u];
        res += sum[u];
        u -= (u & (-u));
    }
    return {ans, res};
}
pll query(ll k){
    auto [u, v] = get(n);
    auto [x, y] = get(k);
    return {u - x, v - y}; 
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    if(fopen(file".INP", "r")){
        freopen(file".INP", "r", stdin);
        freopen(file".OUT", "w", stdout);
    }
    cin>>n>>q;
    s.insert({1, n, 1});
    update(n, 1);
    while(q--){
        ll t; cin>>t;
        if(t == 1){
            ll l, r; char c; cin>>l>>r>>c;
            l++;
            r++;
            assign_value(l, r, c - 'A' + 1);
        }
        else{
            ll k; cin>>k;
            auto [ct, su] = query(k);
            cout<<(ll)su - (ll)k * ct<<'\n';
        }
    }
}
