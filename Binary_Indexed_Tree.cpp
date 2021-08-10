#include<bits/stdc++.h>
template<class T>
struct Binary_Indexed_Tree{
    public:
        Binary_Indexed_Tree():_n(0){}
        Binary_Indexed_Tree(int n): _n(n){
            for(int i = 0; i < 2; i++)data[i].assign(n, 0);
        }

        void add(int l, int r, T x){ // [l, r)にxを加算
            assert(0 <= l && l < r && r <= _n);
            add_sub(0, l, -x * (l - 1));
            add_sub(0, r, x * (r - 1));
            add_sub(1, l, x);
            add_sub(1, r, -x);
        }

        void add(int p, T x){ // pにxを加算
            assert(0 <= p && p < _n);
            add(p, p+1, x);
        }

        T sum(int r){ // [0, r)
            return sum_sub(0, r) + sum_sub(1, r) * (r-1);
        }
        T sum(int l, int r){ // [l,r)
            assert(0 <= l && l <= r && r <= _n);
            return sum(r)-sum(l);
        }
        T operator[](int r){return sum(r+1)-sum(r);}

        int lower_bound(T w){ // \sum_{i=0}^{x}a_x >= wとなるような最小のx なければn, ただしa_xは全て非負であることが条件
            if(w <= 0)return 0;
            int x = 0, r = 1;
            while(r < _n)r = r << 1;
            for(int len = r; len > 0; len = len >> 1){
                if(x + len < _n && sum(x,x+len) < w){
                    w -= sum(x,x+len);
                    x += len;
                }
            }
            if(w > 0)x++;
            return x;
        }

    private:
        int _n;
        std::vector<T> data[2];

        void add_sub(int i, int p, T x){ // 0-indexed
            assert(0 <= p && p <= _n);
            p++; // 内部では1-indexed
            while(p <= _n){
                data[i][p-1] += x;
                p += p & -p;
            }
        }
        T sum_sub(int i, int p){
            T s = 0;
            for(int idx = p; idx > 0; idx -= (idx & -idx)){
                s += data[i][idx-1];
            }
            return s;
        }
};