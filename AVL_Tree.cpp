#include<bits/stdc++.h>
template<typename T>
class AVL{
private:
    struct Node{
        Node *ch[2], *fa;
        int height;
        T data;
    };
    Node *root, *nil;
    void rotate(Node *);
    void pushup(Node *);
    void repair(Node *);
    Node* maintain(Node *);
    void _display(Node *);
public:
    AVL();
    void insert(T);
    void erase(T);
    void display();
};
template<typename T>
void AVL<T>::pushup(AVL<T>::Node *x){
    if(x == this->nil)return;
    x->height = 1 + std::max(x->ch[0]->height, x->ch[1]->height);
}

template<typename T>
void AVL<T>::rotate(Node *x){
    Node *y=x->fa, *z=y->fa;
    z->ch[z->ch[1]==y] = x;
    int t = (y->ch[1] == x);
    y->fa = x; x->fa = z;
    x->ch[t^1]->fa = y;
    y->ch[t] = x->ch[t^1];
    x->ch[t^1] = y;
    if(y == root) root = x;
    pushup(y); pushup(x);
}

template<typename T>
AVL<T>::AVL(){
    nil = new Node();
    nil->ch[0]=nil->ch[1]=nil->fa=nullptr;
    nil->height=0;
    root = nil;
}

template<typename T>
typename AVL<T>::Node* AVL<T>::maintain(AVL<T>::Node *y){
    // std::assert(std::abs(y->ch[0]->height - y->ch[1]->height) > 1);
    Node *x, *xx;
    int t1 = y->ch[1]->height > y->ch[0]->height;
    x = y->ch[t1];
    int t2 = x->ch[1]->height > x->ch[0]->height;
    xx = x->ch[t2];
    if(t1 ^ t2){
        rotate(xx);
        rotate(xx);
        return xx;
    }else{
        rotate(x);
        return x;
    }
}
template<typename T>
void AVL<T>::repair(Node *y){
    while(y != nil){
        // std::cout << y-> data << std::endl;
        int old = y->height;
        pushup(y);
        if(abs(y->ch[0]->height - y->ch[1]->height) <= 1){
            if(y->height == old)break;
        }else{
            y = maintain(y);
        }
        y = y->fa;
    }
}
template<typename T>
void AVL<T>::insert(T data){
    Node *cur = new Node();
    cur->ch[0] = cur->ch[1] = nil;
    cur->data = data;
    cur->height = 1;

    Node *y = nil, *x = root;
    while(x != nil){
        y = x;
        if(data < x->data) x = x->ch[0];
        else x = x->ch[1];
    }
    cur->fa = y;
    if(y == nil){root = cur;}
    if(data < y->data){y->ch[0] = cur;}
    else {y->ch[1] = cur;}
    repair(y);
}
template<typename T>
void AVL<T>::erase(T data){
    Node *y=nil, *x=root;
    while(x!=nil){
        // std::cout << x->data << std::endl;
        y = x;
        if(data < x->data){x = x->ch[0];}
        else if(data > x->data){x = x->ch[1];}
        else break;
    }
    if(x->data != data)return;
    y = x->fa;
    if(x->ch[0] == nil && x->ch[1] == nil){
        y->ch[y->ch[1] == x] = nil;
        if(x  == root) root = nil;
        delete x;
    }else if(x->ch[0] == nil || x->ch[1] == nil){
        int t = (x->ch[0] == nil);
        y->ch[y->ch[1] == x] = x->ch[t];
        x->ch[t]->fa = y;
        if(x == root) root = x->ch[t];
        delete x;
    }else{
        Node *v = x->ch[1];
        // _display(v);
        while(v->ch[0] != nil){/*std::cout << v->ch[0] <<" " << nil<<" "<<v->ch[0]->data << std::endl;*/ v = v->ch[0];}
        x->data = v->data;
        if(v->ch[1] == nil){
            v->fa->ch[v->fa->ch[1]==v] = nil;
            y = v->fa;
            delete v;
            // y = v->fa;
        }else{
            Node *w = v->ch[1];
            v->fa->ch[v->fa->ch[1]==v] = w;
            w->fa = v->fa;
            delete v;
            y = w->fa;
        }
    }
    repair(y);
}
template<typename T>
void AVL<T>::_display(Node *x){
    if(x->ch[0] != nil) _display(x->ch[0]);
    // std::cout << x->data <<" " << x->ch[0] << " " << x->ch[1] << " " << x->ch[0]->data << " " << x->ch[1]->data << " " << x->ch[0]->height << " " << x->ch[1]->height<< std::endl;
        std::cout << x->data<< std::endl;

    if(x->ch[1] != nil)_display(x->ch[1]);
}
template<typename T>
void AVL<T>::display(){
    _display(this->root);
}
const int MAXN = 200;
const int LEN = 30;
int data[MAXN];
int main(){
    std::srand(0);
    AVL<int> a;
    for(int i=1;i<=LEN;i++)
        data[i] = i;
    std::random_shuffle(data+1, data+1+LEN);
    for(int i=1;i<=LEN;i++){
        std::cout << "insert " << data[i] << std::endl;
        a.insert(data[i]);
    }
    // a.display();
    for(int i=1;i<=LEN/4;i++){
        std::cout << "erase " << data[i] << std::endl;
        a.erase(data[i]);
        // a.display();
    }
    std::puts("");
    a.display();
    return 0;
}