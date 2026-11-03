#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ldb;
typedef unsigned long long ull;
typedef __int128_t i128;
typedef pair<ll, ll> pll;
typedef stack<tuple<ll, ll, bool>> stpl;
using type = ll; // TUY THEO DE BAI YEU CAU CTDL GI
// TAT CA DEU LA 0-INDEXED
struct matrix{
    vector<vector<type>> a;
    matrix(ll n, ll m){
        a.assign(n, vector<ll>(m, 0));
    }
    matrix(vector<vector<ll>> k){
        a = k;
    }
    ll row(){
        return a.size();
    }
    ll col(){
        return a[0].size();
    }
    auto &operator[](ll i){
        return a[i];
    }
    const auto &operator[](ll i)const{
        return a[i];
    } // 2 CAI TREN DUNG DE ACCESS NHIEU TANG 
    static matrix indentity(ll n){
        matrix I(n, n);
        for(ll i = 0; i < n; i++) I[i][i]++;
        return I;
    }
    matrix operator+(matrix &b){
        matrix a = *this;
        for(ll i = 0; i < a.row(); i++){
            for(ll j = 0; j < a.col(); j++){
                a[i][j] += b[i][j];
            }
        }
        return a;
    }
    matrix operator-(matrix &b){
        matrix a = *this;
        for(ll i = 0; i < a.row(); i++){
            for(ll j = 0; j < a.col(); j++){
                a[i][j] -= b[i][j];
            }
        }
        return a;
    }
    matrix operator*(matrix &b){
        matrix a = *this;
        matrix c(a.row(), b.col()); // A COL = B ROW
        for(ll i = 0; i < a.row(); i++){
            for(ll j = 0; j < b.col(); j++){
                for(ll k = 0; k < a.col(); k++){
                    c[i][j] += a[i][k] * b[k][j];
                }
            }
        }
        return c;
    }
    matrix operator^(ll expo){
        matrix base = *this;
        matrix res = indentity(base.row());
        while(expo){
            if(expo & 1) res = res * base;
            base = base * base;
            expo>>=1;
        }
        return res;
    }
};
matrix F = vector<vector<ll>>({{1, 1}, {1, 0}});



int main(){
}