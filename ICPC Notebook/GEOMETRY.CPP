#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ldb;
typedef unsigned long long ull;
typedef __int128_t i128;
typedef pair<ll, ll> pll;
typedef stack<tuple<ll, ll, bool>> stpl;
const ldb EPS = 1e-6; // TANG GIAM THEO DE BAI
// I LOVE GEOMETRY

bool EQUAL(float x, float y){
    return fabsl(x - y) <= EPS * max({1.0L, fabsl(y), fabsl(x)});
} // FLOATING PRECS
struct point{
    ll x, y;
    point() : x(0), y(0) {}
    point(ll x, ll y) : x(x), y(y) {} 
    bool operator<(const point &k)const{
        if(x != k.x) return x < k.x;
        return y < k.y;
    }
};
struct line{
    point a, b;
    line() : a(point()), b(point()) {}
    line(point a, point b) : a(a), b(b) {}
};
point get(line u){ // DUA VE DANG DIEM CHO DE TINH
    return point(u.b.x - u.a.x, u.b.y - u.a.y);
}
ll cross(line u, line v){ // TICH CO HUONG
    point gu = get(u);
    point gv = get(v);
    return gu.x * gv.y - gv.x * gu.y;
}
ll dot(line u, line v){ // TICH VO HUONG
    point gu = get(u);
    point gv = get(v);
    return gu.x * gv.x + gu.y * gv.y;
}
ll sign(ll x){
    if(x < 0) return -1;
    if(x > 0) return 1;
    return 0;
}
bool on_segment(point a, point b, point c){
    return (c.x - a.x) * (c.x - b.x) <= 0 && (c.y - a.y) * (c.y - b.y) <= 0;
}
bool intersect(line u, line v){
    point a = u.a, b = u.b, c = v.a, d = v.b;
    ll c1 = cross(line(a, b), line(a, c));
    ll c2 = cross(line(a, b), line(a, d));
    ll c3 = cross(line(c, d), line(c, a));
    ll c4 = cross(line(c, d), line(c, b));

    if(c1 == 0 && on_segment(a, b, c)) return true;
    if(c2 == 0 && on_segment(a, b, d)) return true;
    if(c3 == 0 && on_segment(c, d, a)) return true;
    if(c4 == 0 && on_segment(c, d, b)) return true;
    return (c1 * c2 < 0 && c3 * c4 < 0);
}
vector<point> make_hull(vector<point> &pts){
    vector<point> hull;
    ll n = pts.size();
    for(ll i = 0; i < n; i++){
        while(hull.size() > 1 && cross(line(hull[hull.size() - 2], hull.back()), line(hull.back(), pts[i])) >= 0) hull.pop_back();
        hull.push_back(pts[i]);
    }
    ll k = hull.size();
    for(ll i = n - 2; i>=0; i--){
        while(hull.size() > k && cross(line(hull[hull.size() - 2], hull.back()), line(hull.back(), pts[i])) >= 0) hull.pop_back();
        hull.push_back(pts[i]);
    }
    if(n > 1) hull.pop_back();
    return hull;
}
ll area(vector<point> &pts){ // tra ve 2 * S
    sort(pts.begin(), pts.end());
    vector<point> hull = make_hull(pts); // tao bai loi (neu cac dinh chua loi)
    ll ans = 0;
    ll n = hull.size();
    for(ll i = 0; i < n; i++){
        ans += (hull[i].x - hull[(i + 1) % n].x) * (hull[i].y + hull[(i + 1) % n].y);
    }
    return ans;
}
// A = I + B/2 - 1, VOI A LA DIEN TICH, I LA SO DINH NGUYEN TRONG, B LA NGOAI
ll pick(vector<point> &pts){ // tra ve B
    ll ans = 0;
    ll n = pts.size();
    for(ll i = 0; i < n; i++){
        ans += gcd(abs(pts[i].x - pts[(i + 1) % n].x), abs(pts[i].y - pts[(i + 1) % n].y));
    }
    return ans;
}
int main(){
    
}