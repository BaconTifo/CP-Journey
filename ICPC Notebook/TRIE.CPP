#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ldb;
typedef unsigned long long ull;
typedef __int128_t i128;
typedef pair<ll, ll> pll;
// TRIE AND AHO-CORASICK CUA CHU VIET THUONG (128 NEU ALL CHU CAI)
struct node{
    ll child[26];
    ll suf, exit; // SUFFIX LINK, EXIT LINK
    ll cnt, exist; // CNT = STRING END, EXIST = STRING PREFIX
    node(){
        for(ll i = 0; i<26; i++){
            child[i] = 0;
        }
        cnt = exist = 0;
        suf = exit = 0;
    }
};
vector<node> pool(1);
ll make_new(){
    pool.push_back(node());
    return pool.size() - 1;
}
ll root = 0;
void add_str(string &u){
    ll pos = root;
    for(char c : u){
        if(!pool[pos].child[c - 'a']) pool[pos].child[c - 'a'] = make_new();
        pos = pool[pos].child[c - 'a'];
        pool[pos].exist++;
    }
    pool[pos].cnt++;
}
void aut(){ // AUTOMATA;
    queue<ll> q;
    q.push(root);
    while(!q.empty()){
        ll f = q.front();
        ll fsuf = pool[f].suf;
        q.pop();
        if(f) pool[f].exit = (pool[fsuf].cnt ? fsuf : pool[fsuf].exit);
        for(ll i = 0; i < 26; i++){
            ll &nxt = pool[f].child[i];
            ll nxt_suf = (f ? pool[fsuf].child[i] : root);
            if(!nxt) nxt = nxt_suf;
            else{
                pool[nxt].suf = nxt_suf;
                q.push(nxt);
            }
        }
    }
}

int main(){
    
}