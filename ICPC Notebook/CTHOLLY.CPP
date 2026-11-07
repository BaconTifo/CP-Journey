#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ldb;
typedef unsigned long long ull;
typedef __int128_t i128;
typedef pair<ll, ll> pll;
typedef stack<tuple<ll, ll, bool>> stpl;
#define file "MARISA"
struct node{
    ll l,r;
    mutable ll val;
    bool operator<(const node& other)const{
        return l < other.l;
    }
};
struct ODT{
    ll n;
    set<node> s;
    void init(const vector<ll> &a){
        n = a.size() - 1;
        s.clear();
        for(ll l = 1; l<=n;){
            ll r = l;
            while(r <= n && a[l] == a[r]) r++;
            s.insert({l, r - 1, a[l]});
            l = r;
        }
    }
    set<node>::iterator split(ll pos){
        if(pos > n) return s.end();
        auto it = prev(s.upper_bound({pos, 0, 0}));
        if(it->l == pos){
            return it;
        }
        ll l = it->l, r = it->r, val = it->val;
        s.erase(it);
        s.insert({l, pos - 1, val});
        return s.insert({pos, r, val}).first;
    }
    void assign(ll l, ll r, ll val){
        auto itr = split(r + 1);
        auto itl = split(l);
        s.erase(itl, itr);
        auto it = s.insert({l, r, val}).first;
        if(it != s.begin()){
            auto p = prev(it);
            if(p->val == it->val){
                ll nl = p->l;
                ll nr = it->r;
                ll val = it->val;
                s.erase(p);
                s.erase(it);
                it = s.insert({nl, nr, val}).first;
            }
        }
        auto nxt = next(it);
        if(nxt != s.end()){
            if(nxt->val == it->val){
                ll nl = it->l;
                ll nr = nxt->r;
                ll val = it->val;
                s.erase(nxt);
                s.erase(it);
                it = s.insert({nl, nr, val}).first;
            }
        }
    }
    void add(ll l, ll r, ll val){
        auto itr = split(r + 1);
        auto itl = split(l);
        for(auto it = itl; it != itr; ++it){
            it->val += val;
        }
    }
    ll kth(ll l, ll r, ll k){
        auto itr = split(r + 1);
        auto itl = split(l);
        vector<pll> vals;
        for(auto it = itl; it != itr; ++it){
            vals.push_back({it->val, it->r - it->l + 1});
        }
        sort(vals.begin(), vals.end());
        for(auto [val, cnt] : vals){
            if(k <= cnt) return val;
            k -= cnt;
        }
        return -1;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    if(fopen(file".INP", "r")){
        freopen(file".INP", "r", stdin);
        freopen(file".OUT", "w", stdout);
    }
}