#include <bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long double ldb;
typedef unsigned long long ull;
typedef __int128_t i128;
typedef pair<ll, ll> pll;
typedef stack<tuple<ll, ll, bool>> stpl;
#define file "2041I"
const ll N = 2e6 + 5;

struct cust{
    bool operator()(const pll &u, const pll &v)const{
        if(u.first != v.first) return u.first > v.first;
        return u.second < v.second;
    }
};


struct node{
    ll child[93];
    set<pll, cust> cnt;
    ll best_len, best_lexi, best_id;
    ll par, par_e;
    node(){
        for(ll i = 0; i < 93; i++) child[i] = 0; 
        par = 1, par_e = -1;
        best_len = 0;
        best_lexi = 128;
        best_id = N;
    }
};
node ptr[N];
ll node_cnt = 1;
ll get_child(ll u, ll c){
    return ptr[u].child[c];
}
ll make_child(ll u, ll c){
    if(!ptr[u].child[c]){
        ptr[u].child[c] = ++node_cnt;
        ptr[ptr[u].child[c]].par = u;
        ptr[ptr[u].child[c]].par_e = c;
    }
    ptr[ptr[u].child[c]].par = u;
    ptr[ptr[u].child[c]].par_e = c;
    return ptr[u].child[c];
}
void update(ll u){
    ll &best_id = ptr[u].best_id;
    ll &best_len = ptr[u].best_len;
    ll &best_lexi = ptr[u].best_lexi;
    best_id = N, best_len = 0, best_lexi = 128;
    for(ll i = 0; i < 93; i++){
        ll v = get_child(u, i);
        if(!v) continue;
        if(ptr[v].best_len > best_len){
            best_len = ptr[v].best_len;
            best_id = ptr[v].best_id;
            best_lexi = i;
        }
        else if(ptr[v].best_len == best_len){
            if(i < best_lexi){
                best_lexi = i;
                best_id = ptr[v].best_id;
            }
            else if(i == best_lexi){
                best_id = min(best_id, ptr[v].best_id);
            }
        }
    }
    if(!ptr[u].cnt.empty()){
        auto [len, id] = *ptr[u].cnt.begin();
        if(len > best_len){
            best_len = len;
            best_id = id;
            best_lexi = 128;
        }
    }
}
void add_str(string &u, ll i){
    ll pos = 1;
    for(char c : u){
        pos = make_child(pos, c - 33);
        ptr[pos].cnt.insert({u.size(), i});
    }
    while(pos >= 1){
        update(pos);
        if(pos == 1) break;
        pos = ptr[pos].par;
    }
    //ptr[pos].cnt.insert(i);
}
void del_str(string &u, ll i){
    ll pos = 1;
    for(char c : u){
        pos = get_child(pos, c - 33);
        auto it = ptr[pos].cnt.find({u.size(), i});
        if(it != ptr[pos].cnt.end()){
            ptr[pos].cnt.erase(it);
        }
    }
    while(pos >= 1){
        update(pos);
        if(pos == 1) break;
        pos = ptr[pos].par;
    }
    //ptr[pos].cnt.erase(ptr[pos].cnt.find(i));
}
ll query(ll pos){
    if(ptr[pos].best_id == N) return -1;
    return ptr[pos].best_id;
}


ll n;
string p[N];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    if(fopen(file".INP", "r")){
        freopen(file".INP", "r", stdin);
        freopen(file".OUT", "w", stdout);
    }
    cin>>n;
    string t;
    ptr[1] = node();
    ll j = 0, pos = 1;
    while(n--){
        string op; cin>>op;
        if(op == "add"){
            ll i; string s; cin>>i>>s;
            p[i] = s;
            add_str(p[i], i);
        }
        else if(op == "delete"){
            ll i; cin>>i;
            del_str(p[i], i);
        }
        else if(op == "append"){
            string s; cin>>s;
            t += s;
        }
        else{
            ll i; cin>>i;
            while(t.size() && i){
                if(t.size() == j){
                    pos = ptr[pos].par;
                    j--;
                }
                t.pop_back();
                i--;
            }
        }
        while(j < t.size()){
            ll v = get_child(pos, t[j] - 33);
            if(!v || !ptr[v].cnt.size()) break;
            j++;
            pos = v;
        }
        // cout<<t<<" "<<pos<<" ";
        // cout<<j<<": ";
        if(j < t.size()) cout<<-1<<'\n';
        else cout<<query(pos)<<'\n';
    }
}