#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ldb;
typedef unsigned long long ull;
typedef __int128_t i128;
typedef pair<ll, ll> pll;
typedef stack<tuple<ll, ll, bool>> stpl;
#define file "QOJ4231"
const ll N = 505;


char a[N][N];

vector<ll> adj[N * N];
ll n, m;
stack<ll> st;
ll vis[N * N];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    if(fopen(file".INP", "r")){
        freopen(file".INP", "r", stdin);
        freopen(file".OUT", "w", stdout);
    }
    cin>>n>>m;
    for(ll i = 1; i<=n; i++){
        for(ll j = 1; j<=m; j++){
            cin>>a[i][j];
        }
    }
    for(ll i = 1; i<=n; i++){
        for(ll j = 1; j<=m; j++){
            if(a[i][j] == '<'){
                if(i > 1){
                    adj[i * m + j].push_back((i - 1) * m + j);
                }
            }
            else if(a[i][j] == '>'){
                if(i < n){
                    adj[i * m + j].push_back((i + 1) * m + j);
                }
            }
            else if(a[i][j] == '^'){
                if(j > 1){
                    adj[i * m + j].push_back(i * m + j - 1);
                }
            }
            else if(a[i][j] == 'v'){
                if(j < n){
                    adj[i * m + j].push_back(i * m + j + 1);
                }
            }
        }
    }
    for(ll i = 1; i<=n * n; i++){
        
    }
}