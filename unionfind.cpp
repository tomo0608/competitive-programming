#include<bits/stdc++.h>

struct unionfind{
    public:
        unionfind(): _n(0){}
        unionfind(int n):  _n(n),parent_or_size(n, -1){}

        int find(int a){
            assert(0 <= a && a < _n);
            if(parent_or_size[a] < 0)return a;
            return parent_or_size[a] = find(parent_or_size[a]);
        }

        bool same(int a, int b){
            assert(0 <= a && a < _n && 0 <= b && b < _n);
            return find(a) == find(b);
        }

        bool merge(int a, int b){
            assert(0 <= a && a < _n && 0 <= b && b < _n);
            int x = find(a), y = find(b);
            if(x == y)return true;
            if(-parent_or_size[x] < -parent_or_size[y])std::swap(x,y);
            parent_or_size[x] += parent_or_size[y];
            parent_or_size[y] = x;
            return false;
        }

    private:
        int _n;
        std::vector<int> parent_or_size;
};

// https://old.yosupo.jp/problem/unionfind
using namespace std;
int main(){
    int n,q;cin >> n >> q;
    unionfind uf(n);
    while(q--){
        int t,u,v;cin >> t >> u >> v;
        if(t)cout << uf.same(u, v) << endl;
        else uf.merge(u, v);
    }
    return 0;
}