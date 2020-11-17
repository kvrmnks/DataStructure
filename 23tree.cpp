#include <iostream>
#include <algorithm>
#include <cassert>
using namespace std;
template<typename T>
class _23Tree{
private:
    struct Node{
        Node *ch[4], *fa;
        T data[3];
        unsigned int height;
        bool isThree;
    };
    Node *createNode();
    Node *root;
    void maintain(Node *x);
    void erase_maintain(Node *);
    void _display(Node *x);
    Node *_find(T);
public:
    _23Tree();
    unsigned int getHeight()const;
    void insert(T);
    void erase(T);
    bool find(T);
    void display();
};

template<typename T>
_23Tree<T>::_23Tree(){
    root = nullptr;
}

template<typename T>
typename _23Tree<T>::Node *_23Tree<T>::createNode(){
    Node *t = new Node();
    // clear node
    for(int i = 0; i < 3; i++)t->ch[i] = nullptr;
    t->fa = nullptr;
    t->height = 0;
    t->isThree = false;
    return t;
}

template<typename T>
void _23Tree<T>::maintain(_23Tree<T>::Node *x){
    // maintain for a single tree
    // whose father is to be inserted
    // initially x's father exists
    Node *y = x->fa;
    if(y->isThree){
        // when x's father is 3-type

        //find the loc
        int ch_loc = 0;
        for(int i = 0; i < 3 ; i++){
            if(y->ch[i] == x) {
                ch_loc = i;
                break;
            }
        }

        //insert the pointers into y
        for(int i = 3; i > ch_loc; i--){
            y->ch[i] = y->ch[i - 1];
        }
        y->ch[ch_loc] = x->ch[0];
        y->ch[ch_loc+1] = x->ch[1];
        for(int i = 0 ; i < 4; i++){
            y->ch[i]->fa = y;
        }

        //insert data into y
        y->data[2] = x->data[0];
        sort(y->data, y->data+3);

        //split y
        Node *tmp = createNode();
        Node *p1 = createNode();
        Node *p2 = createNode();
        tmp->data[0] = y->data[1];
        p1->data[0] = y->data[0];
        p2->data[0] = y->data[2];

        p1->ch[0] = y->ch[0];
        p1->ch[1] = y->ch[1];
        p2->ch[0] = y->ch[2];
        p2->ch[1] = y->ch[3];
        p1->fa  = p2->fa = tmp;
        p1->ch[0]->fa = p1->ch[1]->fa = p1;
        p2->ch[0]->fa = p2->ch[1]->fa = p2;
        tmp->ch[0] = p1;
        tmp->ch[1] = p2;
        p1->height = p2->height = y->height;
        tmp->height = p1->height + 1;

        // exchange y's father
        Node *z = y->fa;
        tmp->fa = z;
        if(z == nullptr){
            root = tmp;
        }else{
            int child_size = z->isThree ? 3 : 2;
            for(int i=0;i<child_size ;i++){
                if(z->ch[i] == y){
                    child_size = i;
                    break;
                }
            }
            z->ch[child_size] = tmp;
            delete y;
            maintain(tmp);
        }

    }else{
        // when x's father is 2-type
        y->isThree = true;
        //find the loc
        int ch_loc = 0;
        for(int i = 0; i < 2; i++){
            if(y->ch[i] == x){
                ch_loc = i;
                break;
            }
        }
        ch_loc ^= 1;

        // insert the pointer into y
        if(ch_loc == 0){
            y->ch[1] = x->ch[0];
            y->ch[2] = x->ch[1];
        }else{
            y->ch[2] = y->ch[1];
            y->ch[0] = x->ch[0];
            y->ch[1] = x->ch[1];
        }
        for(int i=0;i<3;i++){
            y->ch[i]->fa = y;
        }

        //insert the data into y
        y->data[1] = x->data[0];
        std::sort(y->data, y->data+2);
        delete x;
    }
}

template<typename T>
unsigned int _23Tree<T>::getHeight()const{
    return root->height;
}

template<typename T>
void _23Tree<T>::insert(T x){
    Node *cur = root;
    if(cur == nullptr){
        root = createNode();
        root->data[0] = x;
        return;
    }
    Node *y = cur;
    while(cur != nullptr){
        int R = cur->isThree ? 2 : 1;
        int i;
        for(i = 0; i < R; i++){
            if(cur -> data[i] < x){
//                break;
            }else{
                break;
            }
        }
//        i = min(i, R-1);
        y = cur;
        cur = cur->ch[i];
    }
    if(y->isThree){
        //insert new node
        y->data[2] = x;
        std::sort(y->data, y->data+3);

        // cur is y's father
        cur = y->fa;

        // split 4-type node
        Node *tmp = createNode();
        Node *p1 = createNode();
        Node *p2 = createNode();
        p1->data[0] = y->data[0];
        tmp->data[0] = y->data[1];
        p2->data[0] = y->data[2];
        tmp->ch[0] = p1;
        tmp->ch[1] = p2;
        p1->fa = tmp;
        p2->fa = tmp;
        tmp->height = 1;
        tmp->fa = y->fa;

        //exchange cur's son to the new 3 node
            //when father is nullptr
        if(cur == nullptr){
            root = tmp;
            delete y;
            return;
        }
            //when father exists
        int child_size = (cur->isThree ? 3 : 2);
        for(int i = 0; i < child_size; i++){
            if(cur -> ch[i] == y){
                child_size = i;
                break;
            }
        }
        cur->ch[child_size] = tmp;
        tmp->fa = cur;
        delete y;

        //update recursively
        maintain(tmp);

    }else{
        y->data[1] = x;
        std::sort(y->data, y->data+2);
        y->isThree = true;
    }
}

template<typename T>
void _23Tree<T>::erase(T v) {
    Node *x = _find(v);
    if(x == nullptr) return;
    if(x->ch[0] == nullptr){
        // x is leaf
        if(x->isThree){
            int child_size = x->isThree ? 2 : 1;
            x->isThree = false;
            int loc = 0;
            for(loc = 0; loc < child_size; loc++){
                if(x->data[loc] != v)break;
            }
            swap(x->data[loc], x->data[0]);
            x->data[1] = T{};
        }else{
            erase_maintain(x);
        }
    }else{
        // x is not leaf
        int loc = 0;
        int child_size = x->isThree ? 2 : 1;
        for(loc = 0; loc < child_size; loc ++){
            if(x->data[loc] == v)break;
        }
        assert(loc < child_size);

        // find next in InOrder
        Node *y = x->ch[loc + 1];
        while(y->ch[0] != nullptr)
            y = y->ch[0];
        x->data[loc] = y->data[0];

        if(y->isThree){
            int child_size = y->isThree ? 2 : 1;
            y->isThree = false;
            swap(y->data[1], y->data[0]);
            y->data[1] = T{};
        }else{
            erase_maintain(y);
        }

    }

}

template<typename T>
bool _23Tree<T>::find(T v) {
    return (_find(v) != nullptr);
}

template<typename T>
void _23Tree<T>::display() {
    _display(root);
}

template<typename T>
void _23Tree<T>::_display(_23Tree::Node *x) {
//    cout << x << endl;
    if(x == nullptr) return;

    int child_size = x->isThree ? 2 : 1;
    //son list
    _display(x->ch[0]);
    for(int i=0;i<child_size;i++){
        cout << x->data[i] << " " << x->height << endl;
        _display(x->ch[i+1]);
    }
}

template<typename T>
typename _23Tree<T>::Node *_23Tree<T>::_find(T v) {
    Node *x = this->root;
    while(x != nullptr){
        int child_size = x->isThree ? 2 : 1;
        bool flag = false;
        for(int i=0;i<child_size;i++){
            if(x->data[i] == v)flag = true;
        }
        if(flag) break;
        int i = 0;
        for(i=0;i<child_size;i++){
            if(v < x->data[i])break;
        }
        x = x->ch[i];
    }
    return x;
}

template<typename T>
void _23Tree<T>::erase_maintain(_23Tree::Node *x) {
    int child_size = x->isThree ? 2 : 1;
    // x is 2-type node
    Node *y = x->fa;
    if(y == nullptr){
        // when father doesn't exist
        root = x->ch[1];
    }else{
        // when father exists

        //find x's location in y
        child_size = y->isThree ? 2 : 1;
        int loc = -1;
        for(int i=0; i<= child_size; i++){
            if(y->ch[i] == x){
                loc = i;
                break;
            }
        }
        assert(loc != -1);

        if(y -> isThree){
            // father is 3-type node
            int to = 0;
            if(loc == 0)to = 1;
            if(loc == 1)to = 2;
            if(loc == 2)to = 1;
            Node *w = y->ch[to];
            if(w->isThree){
                if(loc == 0){
                    if(x->ch[0] == nullptr) x->ch[0] = x->ch[1];
                    x->data[0] = y->data[0];
                    y->data[0] = w->data[0];
                    w->data[0] = w->data[1];
                    w->data[1] = T{};
                    w->isThree = false;
                    x->ch[1] = w->ch[0];
                    for(int i=0;i<=1;i++)w->ch[i] = w->ch[i+1];
                    w->ch[2] = nullptr;
                    if(x->ch[1]!=nullptr)x->ch[1]->fa = x;
                }else if(loc == 1){
                    if(x->ch[0] == nullptr) x->ch[0] = x->ch[1];
                    x->data[0] = y->data[1];
                    y->data[1] = w->data[0];
                    w->data[0] = w->data[1];
                    w->data[1] = T{};
                    w->isThree = false;
                    x->ch[1] = w->ch[0];
                    for(int i=0;i<=1;i++)w->ch[i] = w->ch[i+1];
                    w->ch[2] = nullptr;
                    if(x->ch[1]!=nullptr)x->ch[1]->fa = x;
                }else{
                    if(x->ch[1] == nullptr) x->ch[1] = x->ch[0];
                    x->data[0] = y->data[1];
                    y->data[1] = w->data[1];
                    w->data[1] = T{};
                    w->isThree = false;
                    x->ch[0] = w->ch[2];
                    w->ch[2] = nullptr;
                    if(x->ch[0]!=nullptr)x->ch[0]->fa = x;
                }
            }else{
                if(loc == 0){
                    w->isThree = true;
                    w->data[1] = w->data[0];
                    w->data[0] = y->data[0];
                    y->data[0] = y->data[1];
                    y->data[1] = T{};
                    y->isThree = false;
                    for(int i=0;i<=1;i++)y->ch[i] = y->ch[i+1];
                    y->ch[2] = nullptr;
                    for(int i=1;i>=0;i--)w->ch[i+1] = w->ch[i];
                    w->ch[0] = x->ch[0]==nullptr ? x->ch[1] : x->ch[0];
                    for(int i=0;i<=2;i++)if(w->ch[i]!=nullptr)w->ch[i]->fa = w;
                    delete x;
                }else if(loc == 1){
                    w->isThree = true;
                    w->data[1] = w->data[0];
                    w->data[0] = y->data[1];
                    y->data[1] = T{};
                    y->isThree = false;
                    y->ch[1] = y->ch[2];
                    y->ch[2] = nullptr;
                    for(int i=1;i>=0;i--)w->ch[i+1] = w->ch[i];
                    w->ch[0] = x->ch[0]==nullptr ? x->ch[1] : x->ch[0];
                    for(int i=0;i<=2;i++)if(w->ch[i]!=nullptr)w->ch[i]->fa = w;
                    delete x;
                }else{
                    w->isThree = true;
                    w->data[1] = y->data[1];
                    y->data[1] = T{};
                    y->isThree = false;
                    y->ch[2] = nullptr;
                    w->ch[2] = x->ch[0]==nullptr ? x->ch[1] : x->ch[0];
                    for(int i=0;i<=2;i++)if(w->ch[i]!=nullptr)w->ch[i]->fa = w;
                    delete x;
                }
            }
        }else{
            // father is 2-type node
            Node* w = y->ch[loc^1];
            if(w->isThree){
                w->isThree = false;
                if(loc == 1){
                    x->data[0] = y->data[0];
                    y->data[0] = w->data[1];
                    w->data[1] = T{};
                    if(x->ch[1] == nullptr) x->ch[1] = x->ch[0];
                    x->ch[0] = w->ch[2];
                    w->ch[2] = nullptr;
                    if(x->ch[0] != nullptr)x->ch[0]->fa = x;
                }else{
                    x->data[0] = y->data[0];
                    y->data[0] = w->data[0];
                    w->data[0] = w->data[1];
                    w->data[1] = T{};
                    if(x->ch[0] == nullptr) x->ch[0] = x->ch[1];
                    x->ch[1] = w->ch[0];
                    w->ch[0] = w->ch[1];
                    w->ch[1] = w->ch[2];
                    w->ch[2] = nullptr;
                    if(x->ch[1] != nullptr)x->ch[1]->fa = x;
                }
            }else{
                w->isThree = true;
                w->data[1] = y->data[0];
                //y->data[0] = 20000526;
                sort(w->data, w->data+2);
                if(x->ch[0] == nullptr) x->ch[0] = x->ch[1];
                if(loc == 0){
                    w->ch[2] = w->ch[1];
                    w->ch[1] = w->ch[0];
                    w->ch[0] = x->ch[0];
                    if(w->ch[0] != nullptr)w->ch[0]->fa = w;
                }else{
                    w->ch[2] = x->ch[0];
                    if(w->ch[2] != nullptr)w->ch[2]->fa = w;
                }
                y->ch[loc] = nullptr;
                delete x;
                erase_maintain(y);
            }
        }
    }

}

int data[100000];
int main(int argc, char **argv){
//    freopen("1.txt","w",stdout);
    srand(0);
    _23Tree<int> x;
    int n = 20;
    for(int i=1;i<=n;i++)
        data[i] = i;
    random_shuffle(data+1, data+1+n);
    for(int i=1;i<=n;i++){
        x.insert(data[i]);
    }

    for(int i=1;i<=n/4;i++){
        x.erase(data[i]);
        cout << "erase " << data[i] << endl;
//        x.display();
    }
    x.display();
    cout << x.getHeight() << endl;
    return 0;
}
//1/k - (1 - C(n,k)k!/n^k) > 0