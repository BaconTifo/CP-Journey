#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ldb;
typedef unsigned long long ull;
typedef __int128_t i128;
typedef pair<ll, ll> pll;
typedef stack<tuple<ll, ll, bool>> stpl;
// NICE TO HAVE BUT DOUBT WILL APPEAR
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ull mul_mod(ull a, ull b, ull M){
    return (i128)a * b % M;
}
ull pow_mod(ull a, ull b, ull M){
    ull res = 1;
    while(b){
        if(b & 1) res = mul_mod(res, a, M);
        a = mul_mod(a, a, M);
        b>>=1;
    }
    return res;
}
bool is_p(ull n){
    if(n < 2) return false;
    for(ull p : {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL,
    17ULL, 19ULL, 23ULL, 29ULL, 31ULL, 37ULL}){
        if(n % p == 0) return n == p;
    }
    ull d = n - 1;
    int s = 0;
    while((d & 1) == 0){
        d >>=1;
        s++;
    }
    for(ull a : {2ULL, 325ULL, 9375ULL, 28178ULL,
    450775ULL, 9780504ULL, 1795265022ULL}){
        if(a % n == 0) continue;
        ull x = pow_mod(a % n, d, n);
        if(x == 1 || x == n - 1) continue;
        bool passed = false;
        for(int r = 1; r < s; r++){
            x = mul_mod(x, x, n);
            if(x == n - 1){
                passed = true;
                break;
            }
        }
        if(!passed) return false;
    }
    return true;
}
ull rho_f(ull x, ull c, ull n){ // F(X) = X^2 + C MOD N
    return ((i128)mul_mod(x, x, n) + c) % n;
}
ull pollard(ull n){
    if(n % 2 == 0) return 2;
    if(n % 3 == 0) return 3;
    while(true){
        ull y = rng() % (n - 1) + 1;
        ull c = rng() % (n - 1) + 1;
        const ull BLOCK_SIZE = 128;
        ull g = 1;
        ull r = 1;
        ull x = 0;
        ull ys = 0;
        while(g == 1){
            x = y;
            for(ull i = 0; i < r; i++){
                y = rho_f(y, c, n);
            }
            ull k = 0;
            while(k < r && g == 1){
                ys = y;
                ull q = 1;
                ull lim = min(BLOCK_SIZE, r - k);
                for(ull i = 0; i < lim; i++){
                    y = rho_f(y, c, n);
                    ull diff = (x > y ? x - y : y - x);
                    q = mul_mod(q, diff, n);
                }
                g = gcd(q, n);
                k += lim;
            }
            r <<= 1;
        }
        if(g == n){
            do{
                ys = rho_f(ys, c, n);
                ull diff = (x > ys ? x - ys : ys - x);
                g = gcd(diff, n);
            } while(g == 1);
        }
        if(g > 1 && g < n) return g;
    }
}
void factorize(ull n, map<ull, int> &factors){
    if(n == 1) return;
    if(is_p(n)){
        factors[n]++;
        return;
    }
    ull d = pollard(n);
    factorize(d, factors);
    factorize(n/d, factors);
}
map<ull, int> prime_factorize(ull n){
    map<ull, int> factors;
    factorize(n, factors);
    return factors;
}
int main(){
    
}