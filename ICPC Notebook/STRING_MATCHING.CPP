#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ldb;
typedef unsigned long long ull;
typedef __int128_t i128;
typedef pair<ll, ll> pll;
typedef stack<tuple<ll, ll, bool>> stpl;
// KMP, Z-FUNC, MANACHER TRIE, AHO
vector<ll> prefix_function(string &u){
    ll n = u.size();
    vector<ll> pi(n, 0);
    for(ll i = 1; i<n; i++){
        ll j = pi[i - 1];
        while(j && u[i] != u[j]) j = pi[j - 1];
        if(u[i] == u[j]) j++;
        pi[i] = j;
    }
    return pi;
}
vector<vector<ll>> fail_tree(string &u){
    vector<ll> pi = prefix_function(u);
    ll n = u.size();
    vector<vector<ll>> tree(n + 1);
    for(ll i = 1; i<=n; i++){
        ll par = pi[i - 1];
        tree[par].push_back(i);
    }
    return tree;
}
vector<ll> z_function(string &u){
    ll n = u.size();
    vector<ll> z(n, 0);
    for(ll i = 1, l = 0, r = 0; i<n; i++){
        if(i < r) z[i] = min(r - i, z[i - l]);
        while(i + z[i] < n && u[z[i]] == u[i + z[i]]) z[i]++;
        if(i + z[i] > r){
            r = i + z[i];
            l = i;
        }
    }
    return z;
}
vector<ll> manacher_odd(string &u){
    ll n = u.size();
    vector<ll> d1(n);
    for(ll i = 0, l = 0, r = -1; i < n; i++){
        ll k = (i > r ? 1 : min(d1[l + r - i], r - i + 1));
        while(i - k >= 0 && i + k < n && u[i - k] == u[i + k]) k++;
        d1[i] = k;
        if(i + k - 1 > r){
            r = i + k - 1;
            l = i - k + 1;
        }
    }
    return d1;
}
vector<ll> manacher_even(string &u){
    ll n = u.size();
    vector<ll> d2(n);
    for(ll i = 0, l = 0, r = -1; i < n; i++){
        ll k = (i > r ? 0 : min(d2[l + r - i + 1], r - i + 1));
        while(i - k - 1 >= 0 && i + k < n && u[i - k - 1] == u[i + k]) k++;
        d2[i] = k;
        if(i + k - 1 > r){
            r = i + k - 1;
            l = i - k;
        }
    }
    return d2;
}


int main(){
    
}