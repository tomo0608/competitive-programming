#include<vector>
#include<stack>
#include<cassert>

template<class Monoid, Monoid(*op)(Monoid, Monoid), Monoid(*e)()> struct SWAG{
    SWAG():l(0),r(0),last_i(0),last_j(0),front(e()),v(0),back(){}
    explicit SWAG(std::vector<Monoid> &_v):l(0),r(0),last_i(0), last_j(0), front(e()),v(_v.size()),back(){
        std::copy(_v.begin(),_v.end(), v.begin());
    }
    void push_back(const Monoid &c){
        v.push_back(c);
    }
    size_t size(){
        return v.size();
    }
    Monoid fold(size_t i, size_t j){ //[l, r)
        assert(i < j && j <= v.size());
        assert(last_i <= i && last_j <= j);
        last_i = i, last_j = j;
        while(r < j)front = op(front, v[r++]);
        while(l < i){
            if(back.empty()){
                Monoid tmp = e();
                for(size_t u = r; u-- > l; ){
                    tmp = op(v[u], tmp);
                    back.emplace(tmp);
                }
                front = e();
            }
            back.pop();
            ++l;
        }
        if(back.empty())return front;
        return op(back.top(), front);
    }
    private:
        std::vector<Monoid> v;
        Monoid front;
        std::stack<Monoid> back;
        size_t l, r, last_i, last_j;
};

// https://old.yosupo.jp/problem/queue_operate_all_composite

#include<iostream>
using namespace std;
#define ll long long
const ll MOD = 998244353;
#define S pair<ll,ll>
S op(S x, S y){
    S z;
    z.first = x.first * y.first % MOD;
    z.second = (y.first * x.second + y.second)%MOD;
    return z;
}
S e(){return {1, 0};}
int main(){
    int q;cin >> q;
    int l = 0, r = 0;
    SWAG<S, op, e> swag;
    while(q--){
        int i;cin >> i;
        if(i == 0){
            ll a,b;cin >> a >> b;
            swag.push_back(S(a, b));
            r++;
        }
        if(i == 1){
            l++;
        }
        if(i == 2){
            ll x;cin >> x;
            if(l == r){
                cout << x << endl;
                continue;
            }
            auto [a,b] = swag.fold(l, r);
            ll fx = (a*x + b)%MOD;
            cout << fx << endl;
        }
    }
}