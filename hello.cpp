/**
*    author:  tomo0608
*    created: 09.03.2021 18:17:21
**/

#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
template <class T> using V = vector<T>;
template <class T> using VV = V<V<T>>;
typedef pair<int,int> pii;
typedef pair<long long, long long> pll;

#define all(x) x.begin(),x.end()
#define rep2(i, m, n) for (int i = (m); i < (n); ++i)
#define rep(i, n) rep2(i, 0, n)
#define drep2(i, m, n) for (int i = (m)-1; i >= (n); --i)
#define drep(i, n) drep2(i, n, 0)
#define unique(a) a.erase(unique(a.begin(),a.end()),a.end())
template<class T> using priority_queue_rev = priority_queue<T, vector<T>, greater<T> >;
template<class T, class U> inline bool chmax(T &a, const U &b) { if (a<b) { a=b; return 1; } return 0; }
template<class T, class U> inline bool chmin(T &a, const U &b) { if (a>b) { a=b; return 1; } return 0; }
template<class T1, class T2> istream &operator>>(istream &is, pair<T1, T2> &p) { is >> p.first >> p.second; return is; }
template<class T1, class T2> ostream &operator<<(ostream &os, const pair<T1, T2> &p) { os << '(' << p.first << ", " << p.second << ')'; return os; }
template<class T> istream &operator>>(istream &is, vector<T> &v) { for (auto &e : v) is >> e; return is; }
template<class T> ostream &operator<<(ostream &os, const vector<T> &v) { for (auto &e : v) os << e << ' '; return os; }
template<typename T> ostream& operator << (ostream& os, set<T>& set_var) {os << "{"; for (auto itr = set_var.begin(); itr != set_var.end(); itr++) {os << *itr;++itr;if(itr != set_var.end()) os << ", ";itr--;}os << "}";return os;}
template <typename T, typename U> ostream &operator<<(ostream &os, map<T, U> &map_var) {os << "{";for(auto itr = map_var.begin(); itr != map_var.end(); itr++) {os << *itr;itr++;if (itr != map_var.end()) os << ", ";itr--;}os << "}";return os;}
template<class T> inline int count_between(vector<T> &a, T l, T r) { return lower_bound(all(a), r) - lower_bound(all(a), l); } // [l, r)
#define pb push_back
#define eb emplace_back
#define elif else if
#define mp make_pair
#define bit(n, k) ((n >> k) & 1) /*nのk bit目*/
template<typename T> T gcd(T x, T y){if(x%y == 0)return y;return gcd(y, x%y);}
template<typename T> T gcd(vector<T> a){T res = a[0];for(auto &x: a)res = gcd(res, x);return res;}
template <typename T>T mypow(T x, ll n){T ret = 1;while(n > 0){if(n & 1)(ret *= x);(x *= x);n >>= 1;}return ret;}
#define endl '\n'
int dx[8] = {1, 0, -1, 0, 1, 1, -1, -1};
int dy[8] = {0, 1, 0, -1, 1, -1, -1, 1};


void solve(){
    cout << "Hello, world!" << endl;
    return;
}

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    cout << setprecision(20);
    int codeforces = 1;
    //cin >> codeforces;
    while(codeforces--){
        solve();
    }
    return 0;
}