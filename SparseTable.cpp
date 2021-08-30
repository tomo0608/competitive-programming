#include<iostream>
#include<vector>

template<class S, S (*op)(S, S)> struct SparseTable{
    std::vector<std::vector<S>> st;
    std::vector<int> lookup;

    SparseTable() = default;

    explicit SparseTable(const std::vector<S> &v){
        const int n = (int) v.size();
        const int b = 32 - __builtin_clz(n);
        st.assign(b, std::vector<S>(n));
        for(int i = 0; i < v.size(); i++)st[0][i] = v[i];
        for(int i = 1; i < b; i++){
            for(int j = 0; j + (1 << i) <= n; j++){
                st[i][j] = op(st[i-1][j], st[i-1][j + (1 << (i-1))]);
            }
        }
        lookup.resize(n+1);
        for(int i = 2; i < lookup.size(); i++)lookup[i] = lookup[i >> 1] + 1;
    }

    inline S query(int l, int r)const{
        int b = lookup[r-l];
        return op(st[b][l], st[b][r-(1<<b)]);
    }
};
//https://old.yosupo.jp/problem/staticrmq
int op(int x, int y){return std::min(x,y);}
using namespace std;
int main(){
    int n,q;cin >> n >> q;
    vector<int> v(n);
    for(int i = 0; i < n; i++)cin >> v[i];
    SparseTable<int,op> dat(v);
    while(q--){
        int l,r;cin >> l >> r;
        cout << dat.query(l, r) << endl;
    }
}