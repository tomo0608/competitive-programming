#include<iostream>
#include<vector>

template<typename S, S (*op)(S, S)> struct DisjointSparseTable{
    std::vector<std::vector<S>> dst;
    int n;

    DisjointSparseTable(const std::vector<S> &v){
        n = (int) v.size();
        dst.emplace_back(v);
        for(int i = 2; i < n; i <<= 1){
            dst.emplace_back(std::vector<S>(n));
            for(int j = i; j < n; j += i << 1){
                dst.back()[j-1] = dst[0][j-1];
                for(int k = 2; k <= i; k++){
                    dst.back()[j-k] = op(dst[0][j-k], dst.back()[j-k+1]);
                }
                dst.back()[j] = dst[0][j];
                for(int k = 2; k <= i && j + k <= n; k++){
                    dst.back()[j+k-1] = op(dst.back()[j+k-2], dst[0][j+k-1]);
                }
            }
        }
    }

    inline S query(int l, int r)const{
        if(l < 0)l = 0;
        if(r > n)r = n;
        r--;
        if(l == r)return dst[0][l];
        int k = 31 - __builtin_clz(l^r);
        return op(dst[k][l], dst[k][r]);
    }
};
//https://old.yosupo.jp/problem/staticrmq
int op(int x, int y){return std::min(x,y);}
using namespace std;
int main(){
    int n,q;cin >> n >> q;
    vector<int> v(n);
    for(int i = 0; i < n; i++)cin >> v[i];
    DisjointSparseTable<int,op> dat(v);
    while(q--){
        int l,r;cin >> l >> r;
        cout << dat.query(l, r) << endl;
    }
}