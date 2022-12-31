#include<bits/stdc++.h>

/* 平衡二分探索木(keyの型(int, long long等の比較が実装されているもの), valueの型), keyは同じ値が入らない仮定が入る*/
template <class S, class T>
class treap
{
    struct xorshift {
        unsigned x = 123456789, y = 362436069, z = 521288629, w = 88675123;
        xorshift(unsigned seed = 0) { z ^= seed; }
        unsigned operator()() {
            unsigned t = x ^ (x << 11);
            x = y;
            y = z;
            z = w;
            return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
        }
    };
    xorshift rnd;// 乱数用


    struct node
    {
        S key;// key(Treapはkeyについて二分探索木)
        S sum;// 木のkeyの和
        T val;// 格納したい値
        node* left;// 左の子のポインタ
        node* right;// 右の子のポインタ
        unsigned pri;// priority(Treapはpriorityについて最大値ヒープ)
        unsigned sz;// 木の頂点数
        node(S key, T val, unsigned pri): key(key), sum(key), val(val), left(nullptr), right(nullptr), pri(pri), sz(1) {}
    }*root = nullptr;
    using Tree = node*;

    unsigned size() { return size(root); }
    unsigned size(Tree v) { return !v ? 0 : v->sz; }
    S sum(Tree v) { return !v ? 0 : v->sum; }

    Tree update(Tree& v) {// vの情報を更新
        v->sum = sum(v->left) + sum(v->right) + v->key;
        v->sz = size(v->left) + size(v->right) + 1;
        return v;
    }
    Tree merge(Tree l, Tree r)// 二つの木をmerge
    {
        if (!l or !r)
            return l ? l : r;
        if (l->pri > r->pri)
        {
            l->right = merge(l->right, r);
            return update(l);
        }
        r->left = merge(l, r->left);
        return update(r);
    }

    std::pair<Tree, Tree> split_by_size(Tree& v, unsigned k)// vをkeyについて小さいk個とそれ以外に分割
    {

        if (!v)
            return std::pair<Tree, Tree>(NULL, NULL);
        if (k <= size(v->left))
        {
            std::pair<Tree, Tree> s = split_by_size(v->left, k);
            v->left = s.second;
            return make_pair(s.first, update(v));
        }
        std::pair<Tree, Tree> s = split_by_size(v->right, k - size(v->left) - 1);
        v->right = s.first;
        return make_pair(update(v), s.second);
    }

    std::pair<Tree, Tree> split_by_key(Tree& v, S key)// vをkey未満のものとkeyより大きいものに分割
    {
        if (!v)return std::pair<Tree, Tree>(NULL, NULL);
        if (key <= v->key) {
            std::pair<Tree, Tree> s = split_by_key(v->left, key);
            v->left = s.second;
            return std::make_pair(s.first, update(v));
        }
        std::pair<Tree, Tree> s = split_by_key(v->right, key);
        v->right = s.first;
        return std::make_pair(update(v), s.second);
    }

    Tree find_by_index(unsigned k) { // k番目に小さい値を持つ頂点の取得(0-indexed)
        Tree v = root;
        while (v) {
            unsigned s = size(v->left);
            if (s > k)v = v->left;
            else if (s == k)return v;
            else {
                v = v->right;
                k -= s + 1;
            }
        }
        return v;
    }

    Tree find_by_key(Tree& v, S key) { // keyとしてkeyをもつ頂点の取得
        if (!v)return NULL;
        if (key < v->key)return find_by_key(v->left, key);
        if (key > v->key)return find_by_key(v->right, key);
        return v;
    }

    Tree _insert(Tree& v, S key, T val, unsigned pri) { // vに(key, val)を挿入
        std::pair<Tree, Tree> s = split_by_key(v, key);
        v = merge(s.first, new node(key, val, pri));
        v = merge(v, s.second);
        return update(v);
    }

    Tree erase_by_key(Tree& v, S key) { // vからkeyのものを削除(存在しないとバグる)
        if (!v)return NULL;
        if (v->key == key)return v = merge(v->left, v->right);
        if (key < v->key) {
            v->left = erase_by_key(v->left, key);
        }
        else {
            v->right = erase_by_key(v->right, key);
        }
        return update(v);
    }

public:
    void erase(S key) {
        erase_by_key(root, key);
    }
    T get_val(S key, T default_value) {
        Tree v = find_by_key(root, key);
        if (v == NULL)return default_value;
        return v->val;
    }
    void insert(S key, T val) {
        Tree v = find_by_key(root, key);
        if (v)erase_by_key(root, key);
        _insert(root, key, val, rnd());
    }
};