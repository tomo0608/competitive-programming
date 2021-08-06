/**
*    author:  tomo0608
*    created: 05.08.2021 21:40:22
**/

#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#if __has_include(<atcoder/all>)
#include<atcoder/all>
using namespace atcoder;
#endif

typedef long long ll;
typedef long double ld;
template <class T> using V = vector<T>;
template <class T> using VV = V<V<T>>;
template <class T> using VVV = V<VV<T>>;
typedef pair<int,int> pii;
typedef pair<long long, long long> pll;

#define all(x) x.begin(),x.end()
#define rep1(a)          for(long long i = 0; i < a; i++)
#define rep2(i, a)       for(long long i = 0; i < a; i++)
#define rep3(i, a, b)    for(long long i = a; i < b; i++)
#define rep4(i, a, b, c) for(long long i = a; i < b; i += c)
#define drep1(a)          for(long long i = a-1; i >= 0; i--)
#define drep2(i, a)       for(long long i = a-1; i >= 0; i--)
#define drep3(i, a, b)    for(long long i = a-1; i >= b; i--)
#define drep4(i, a, b, c) for(long long i = a-1; i >= b; i -= c)
#define overload4(a, b, c, d, e, ...) e
#define rep(...) overload4(__VA_ARGS__, rep4, rep3, rep2, rep1)(__VA_ARGS__)
#define drep(...) overload4(__VA_ARGS__, drep4, drep3, drep2, drep1)(__VA_ARGS__)
#define unique(a) a.erase(unique(a.begin(),a.end()),a.end())
template<class... T>void input(T&... a){(cin >> ... >> a);};
#define INT(...) int __VA_ARGS__; input(__VA_ARGS__)
#define LL(...) ll __VA_ARGS__; input(__VA_ARGS__)
#define STRING(...) string __VA_ARGS__; input(__VA_ARGS__)
void print(){cout << '\n';}
template<class T, class... Ts>void print(const T& a, const Ts&... b){cout << a; (cout << ... << (cout << ' ', b)); cout << '\n';}
template<class T> using priority_queue_rev = priority_queue<T, vector<T>, greater<T> >;
template<class T, class U> inline bool chmax(T &a, const U &b) { if (a<b) { a=b; return 1; } return 0; }
template<class T, class U> inline bool chmin(T &a, const U &b) { if (a>b) { a=b; return 1; } return 0; }
template<class T1, class T2> istream &operator>>(istream &is, pair<T1, T2> &p) { is >> p.first >> p.second; return is; }
template<class T1, class T2> ostream &operator<<(ostream &os, const pair<T1, T2> &p) { os << '(' << p.first << ", " << p.second << ')'; return os; }
template<class T> istream &operator>>(istream &is, vector<T> &v) { for (auto &e : v) is >> e; return is; }
template<class T> ostream &operator<<(ostream &os, const vector<T> &v) { for (auto &e : v) os << e << ' '; return os; }
template<typename T> ostream& operator << (ostream& os, set<T>& set_var) {os << "{"; for (auto itr = set_var.begin(); itr != set_var.end(); itr++) {os << *itr;++itr;if(itr != set_var.end()) os << ", ";itr--;}os << "}";return os;}
template <typename T, typename U> ostream &operator<<(ostream &os, map<T, U> &map_var) {os << "{";for(auto itr = map_var.begin(); itr != map_var.end(); itr++) {os << *itr;itr++;if (itr != map_var.end()) os << ", ";itr--;}os << "}";return os;}
#ifdef __LOCAL
void debug_out(){ cerr << endl;}
template < class Head, class... Tail> void debug_out(Head H, Tail... T) { cerr << ' ' << H; debug_out(T...);}
#define debug(...) cerr << 'L' << __LINE__ << " [" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#define dump(x) cerr << 'L' << __LINE__ << " " << #x << " = " << (x) << endl
#else
#define debug(...) (void(0))
#define dump(x) (void(0))
#endif
template<class T> inline int count_between(vector<T> &a, T l, T r) { return lower_bound(all(a), r) - lower_bound(all(a), l); } // [l, r)
#define mp make_pair
#define bit(n, k) ((n >> k) & 1) /*nのk bit目*/
template <typename T>T mypow(T x, ll n){T ret = 1;while(n > 0){if(n & 1)(ret *= x);(x *= x);n >>= 1;}return ret;}
#define endl '\n'
int dx[8] = {1, 0, -1, 0, 1, 1, -1, -1};
int dy[8] = {0, 1, 0, -1, 1, -1, -1, 1};


namespace geometry{
        // ここからコピー
    const double EPS = 1e-10;
    const double PI = 3.1415926535897932;
    double radian_to_degree(double r){return r*180.0/PI;}
    double degree_to_radian(double d){return d*PI/180.0;}

    class Point{
        // R^2上の点
        public:
        double x, y;
        Point(double x = 0, double y = 0): x(x), y(y){}

        Point operator+(const Point &p)
        {
            return {x + p.x, y + p.y};
        }

        Point operator-(const Point &p)
        {
            return {x - p.x, y - p.y};
        }

        Point operator*(const double k){
            return {k*x, k*y};
        }

        Point operator/(const double k){
            return {x/k, y/k};
        }

        Point rotate_radian(const double theta){
            return {cos(theta)*x - sin(theta)*y, sin(theta)*x + cos(theta)*y};
        }

        double operator*(const Point &p){
            return x*p.x + y*p.y;
        }

        double operator^(const Point &p){
            return x*p.y - y*p.x;
        }

        bool operator<(const Point &p){
            if(x < p.x)return true;
            if(x > p.x)return false;
            if(y < p.y)return true;
            return false;
        }
        
        bool operator==(const Point &p){
            return abs(x - p.x) < EPS && abs(y - p.y) < EPS;
        }

        double norm(){
            return sqrt(x*x + y*y);
        }
        
        Point standardize(){
            Point res = *this;
            return res/res.norm();
        }

        double getangle(){
            // 偏角を度数で求める(0 <= angle <= 360)
            if(y >= 0.0){
                double I = x / norm();
                double angle = acos(I) * 180.0 / 3.14159265358979;
                return angle;
            }
            else{
                double I = x / norm();
                double angle = acos(I) * 180.0 / 3.14159265358979;
                return 360.0 - angle;
            }
        }
        friend istream &operator>>(istream &is, Point &p) { is >> p.x >> p.y; return is; }
        friend ostream &operator<<(ostream &os, const Point &p) { os  << p.x << ' ' << p.y; return os; }
    };
    #define POINT(...) Point __VA_ARGS__; input(__VA_ARGS__)
    struct Line{
        public:
        Point a, b;
        Point vec;
        Line(Point a = Point(), Point b = Point()): a(a),b(b),vec(b-a){}
        friend istream &operator>>(istream &is, Line &l) { is >> l.a >> l.b; return is; }
        friend ostream &operator<<(ostream &os, Line &l) { os  << l.a << ' ' << l.b; return os; }

        //Projection
        Point projection(Point p){ // pのLineへの射影
            p = p - a;
            return a + vec * ((vec * p)/(vec * vec));
        }

        Point reflection(Point p){ // pのLineに対する線対称な位置
            p = p - a;
            return a - p + vec * ((vec * p)/(vec * vec)) * 2;
        }
        bool is_Parallel(const Line &other_l){ // lとother_lが平行かどうか
            return abs(vec ^ other_l.vec) < EPS;
        }
        bool is_Orthogonal(const Line &other_l){ // lとother_lが垂直かどうか
            return abs(vec * other_l.vec) < EPS;
        }
    };

    struct Segment:Line{
        Segment(Point a = Point(), Point b = Point()): Line(a,b){}
    };

    struct Circle{
        Point c;
        double r;
        Circle(Point c = Point(), double r = 0.0):c(c),r(r){}
    };

    using Points = vector<Point>;
    using Polygon = vector<Point>;
    using Segments = vector<Segment>;
    using Lines = vector<Line>;
    using Circles = vector<Circle>;

    int ccw(const Point &a, Point b, Point c){ // a,b,cの順に見て
        b = b - a, c = c - a;
        if((b^c) > EPS)return +1; // "COUNTER_CLOCKWISE"
        if((b^c) > -EPS)return -1; // "CLOCKWISE"
        if((b*c) < -EPS)return +2; // "ONLINE_BACK"
        if((b*b) < c*c)return -2;  // "ONLINE_FRONT"
        return 0; // "ON_SEGMENT"
    }
}
