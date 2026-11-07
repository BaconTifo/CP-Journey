#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ldb;
typedef unsigned long long ull;
typedef __int128_t i128;
typedef pair<ll, ll> pll;
typedef stack<tuple<ll, ll, bool>> stpl;
#define file "PTNKTRAINING5"
const ll N = 2e5 + 5;
ll n, l, k, q;

ll a[N];

map<vector<ll>, ll> cnt;

vector<ll> merge(vector<ll> a, vector<ll> b){

    while(!b.empty()){
        a.push_back(b.back());
        b.pop_back();
    }
    return a;
}

void calc(){
    cnt.clear();
    vector<ll> p;
    vector<ll> su;
    for(ll i = n; i>=1; i--){
        su.push_back(a[i]);
    }
    for(ll i = 1; i<=n - l + 1; i++){
        vector<ll> newsu = su;
        // for(ll j : su) cout<<j<<" ";
        // cout<<'\n';
        for(ll j = i; j <= i + k - 1; j++){
            if(!newsu.empty()) newsu.pop_back();
            if(j - i + 1 >= l){
                cnt[merge(p, newsu)]++;
            }
        }
        p.push_back(a[i]);
        su.pop_back();
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    if(fopen(file".INP", "r")){
        freopen(file".INP", "r", stdin);
        freopen(file".OUT", "w", stdout);
    }
    cin>>n>>l>>k>>q;
    for(ll i = 1; i<=n; i++){
        cin>>a[i];
    }
    while(q--){
        ll i, v; cin>>i>>v;
        a[i] = v;
        // for(ll i = 1; i<=n; i++){
        //     cout<<a[i]<<" ";
        // }
        // cout<<'\n';
        calc();
        // for(auto i : cnt){
        //     for(ll j : i.first) cout<<j<<" ";
        //     cout<<'\n';
        // }
        cout<<cnt.size()<<'\n';
    }
}