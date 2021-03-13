#include<bits/stdc++.h>
using namespace std;


template<class T> // T は　比較可能なもの(int, long long, pair<int,int> など)
class RedBlackTree{
    class Node{ 
    public:
        Node *parent;
        Node *left;
        Node *right;
        T key;
        int color;
        int size; // 部分木のサイズ
    };

    public:
    Node *root;
    Node *nil;

    RedBlackTree(){
        nil = new Node;
        nil ->color = 1;
        nil ->size = 0;
        root = nil;
    }
   
    void _print_tree(Node *x){
        std::cout << "(";
        if(x != nil){
            std::cout <<'[' <<  x->key;
            if(x->color)cout << "B] ";else std::cout << "R] ";
            cout << "size: " << x->size;
            _print_tree(x->left);
            _print_tree(x->right);
        }
        std::cout << ")";
    }

    int rb_bheight(Node *x){
        int lh, rh;
        if(x == nil)return 0;

        if(!(x->color)){ // 赤節点の子はどちらも黒
            if(!((x->left)->color)){
                printf("rb_bheight: error node=%d, R left=%d,R\n",x->key, (x->left)->key);
            }
            if (!((x->right)->color)) {
                printf("rb_bheight: error node=%d,R right=%d,R\n",x->key, (x->right)->key);
            }
        }
        lh = rb_bheight(x->left); // 左部分木の黒高さ
        if(x->left->color)lh++; // 左部分木から決まる黒高さ
        rh = rb_bheight(x->right); // 右部分木の黒高さ
        if(x->right->color)rh++; // 右部分木から決まる黒高さ
        if(lh != rh){ // 左右の黒高さが一致していなければエラー
            printf("rb_bheight: error node=%d lh=%d rh=%d\n", x->key, lh, rh);
        }
        return lh;
    }

    Node *maximum(Node *x){
        while(x->right != nil)x = x->right;
        return x;
    }

    Node *minimum(Node *x){
        while(x->left != nil)x = x->left;
        return x;
    }

    Node *successor(Node *x){
        Node *y;
        if(x->right != nil)return minimum(x->right);
        y = x->parent;
        while(y != nil && x == y->right){
            x = y;
            y = y->parent;
        }
        return y;
    }

    Node *search(int k){
        Node *x = root;
        while(x != nil && k != x->key){
            if(k < x->key)x = x->left;
            else x = x->right;
        }
        if(x == nil)x = NULL;
        return x;
    }

    void left_rotate(Node *x){
        Node *y = x->right;
        x->right = y->left;
        if(y->right != nil)(y->left)->parent = x;
        y->parent = x->parent;
        if(x->parent == nil)root = y;
        else{
            if(x == (x->parent)->left)(x->parent)->left = y;
            else (x->parent)->right = y;
        }
        y->left = x;
        x->parent = y;
        x->size = (x->left)->size + (x->right)->size + 1;
        y->size = (y->left)->size + (y->right)->size + 1;
    }

    void right_rotate(Node *x){
        Node *y = x->left;
        x->left = y->right;
        if(y->left != nil)(y->right)->parent = x;
        y->parent = x->parent;
        if(x->parent == nil)root = y;
        else{
            if(x == (x->parent)->right)(x->parent)->right = y;
            else (x->parent)->left = y;
        }
        y->right = x;
        x->parent = y;
        x->size = (x->left)->size + (x->right)->size + 1;
        y->size = (y->left)->size + (y->right)->size + 1;
    }

    void rb_insert_fixup(Node *x){
        Node *y, *z;
        while(!((x->parent)->color)){ // 2色木条件を満たしていないなら修正
            z = x->parent; // z は x の親
            if(z == (z->parent)->left){ // z が左の子の場合
                y = (z->parent)->right; // y は z の兄弟
                if(!(y->color)){ // 場合1: y　が赤のとき
                    z->color = 1;
                    y->color = 1;
                    (z->parent)->color = 0;
                    x = z->parent;
                }else{
                    if(x == z->right){ // 場合2: y が黒でxが右の子の場合
                        x = z;
                        left_rotate(x);
                    }// 場合3 へ続く
                    (x->parent)->color = 1; // 場合3: y が黒で　x が左の子の場合
                    ((x->parent)->parent)->color = 0;
                    right_rotate((x->parent)->parent);
                }
            }else{ // z が右の子の場合
                y = (z->parent)->left; // y は z の兄弟
                if(!(y->color)){ // 場合1: y　が赤のとき
                    z->color = 1;
                    y->color = 1;
                    (z->parent)->color = 0;
                    x = z->parent;
                }else{
                    if(x == z->left){ // 場合2: y が黒でxが左の子の場合
                        x = z;
                        right_rotate(x);
                    }// 場合3 へ続く
                    (x->parent)->color = 1; // 場合3: y が黒で　x が右の子の場合
                    ((x->parent)->parent)->color = 0;
                    left_rotate((x->parent)->parent);
                }
            }
        }
        root->color = 1;
    }

    void insert(T k){
        Node *z = new Node;
        z->key = k;
        z->parent = nullptr;
        z->left = nil;
        z->right = nil; // z は葉
        z->color = 0; // 新節点は赤
        z->size = 1;
        Node *y = nil, *x = root;
        while(x != nil){ // z を挿入する場所xを決める
            y = x; // yはxの親
            if(z->key < x->key)x = x->left;
            else               x = x->right;
        }
        z->parent = y; // zの親をyにする
        if(y == nil)root = z; // T が空ならzが根節点
        else{
            if(z->key < y->key) y->left = z; // yの子をzに
            else                y->right = z;
            while(y!= nil){
                y->size++;
                y = y->parent;
            }
        }
        rb_insert_fixup(z);
    }

    void rb_delete_fixup(Node *x){
        Node *w;
        while(x != root && x->color){
            if(x == (x->parent)->left){ // x が左の子の場合
                w = (x->parent)->right; // w は x の兄弟
                if(!(w->color)){ // 場合1: w が赤
                    w->color = 1;
                    (x->parent)->color = 0;
                    left_rotate(x->parent);
                    w = (x->parent)->right;
                }// 場合2　へ続く
                if((w->left)->color && (w->right)->color){ // 場合2: wの左右の色が黒
                    w->color = 0;
                    x = x->parent; // 1つ上に移動して再度繰り返す
                    }else{
                    if((w->right)->color){ // 場合3: wの右の子が黒
                        (w->left)->color = 1;
                        w->color = 0;
                        right_rotate(w);
                        w = (x->parent)->right;
                    }// 場合4 へ続く
                    w->color = (x->parent)->color; // 場合4: wの右の子が赤
                    (x->parent)->color = 1;
                    (w->right)->color = 1;
                    left_rotate(x->parent);
                    x = root;
                }
            }else{ // xが右の子の場合
                w = (x->parent)->left; // w は x の兄弟
                if(!(w->color)){ // 場合1: w が赤
                    w->color = 1;
                    (x->parent)->color = 0;
                    right_rotate(x->parent);
                    w = (x->parent)->left;
                }// 場合2　へ続く
                if((w->right)->color && (w->left)->color){ // 場合2: wの左右の色が黒
                    w->color = 0;
                    x = x->parent; // 1つ上に移動して再度繰り返す
                    }else{
                    if((w->left)->color){ // 場合3: wの左の子が黒
                        (w->right)->color = 1;
                        w->color = 0;
                        left_rotate(w);
                        w = (x->parent)->left;
                    }// 場合4 へ続く
                    w->color = (x->parent)->color; // 場合4: wの左の子が赤
                    (x->parent)->color = 1;
                    (w->left)->color = 1;
                    right_rotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = 1;
    }

    Node *del(int k){
        Node *x, *y, *z = search(k);
        if(z==NULL)return NULL;
        if(z->left == nil || z->right == nil){ // zの子の数が0か1
            y = z;
        }else{ // zの子の数が2
            y = successor(z);
        }
        if(y->left != nil)x = y->left;
        else              x = y->right;
        x->parent = y->parent;
        if(y->parent == nil){
            root = x;
        }else{
            if(y == (y->parent)->left){
                (y->parent)->left = x;
            }else{
                (y->parent)->right = x;
            }
            Node *w = y->parent;
            while(w != nil){
                w->size--;
                w = w->parent;
            }
        }
        if(y!=z)z->key = y->key;
        //delete z;
        if(y->color)rb_delete_fixup(x); // 黒節点を削除した場合は木を修正
        return y;
    }

    Node *os_select(Node *x, int i){ // xを根とする部分木の中でi番目に小さいキーを持つ節点を返す
        int r = (x->left)->size + 1;
        if(i == r)return x;
        else if(i < r)return os_select(x->left, i);
        else return os_select(x->right, i-r);
    }

    T get(int i){ // i番目に小さいキー(1-indexed)
        assert(root->size >= i);
        return os_select(root, i)->key;
    }

    int os_rank(Node *x){ // x->keyが小さい方から何番目か(1-indexed)
        int r = (x->left)->size + 1;
        Node *y = x;
        while(y != root){
            if(y == (y->parent)->right)r += ((y->parent)->left)->size + 1;
            y = y->parent;
        }
        return r;
    }

    Node *getRoot(){
        return this->root;
    }

    void printTree(){
        if(root)_print_tree(this->root);
        cout << endl;
    }

    void printArray(){
        if(root)inOrder(this->root);
        cout << endl;
    }
};

int main(){
    int q;cin >> q;
    RedBlackTree<int> rbt;
    while(q--){
        int t,x;cin >> t >> x;
        if(t == 1)rbt.insert(x);
        else{
            int ans = rbt.get(x);
            cout << ans << endl;
            rbt.del(ans);
        }
    }
}