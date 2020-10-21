#include<iostream>
#include<cassert>
#include<algorithm>
#include<set>
using namespace std;


template<typename T>
class BinarySearchTree{
private:
	struct Node{
		T data;
		Node *ch[2], *fa;
		bool flag[2];
	};
	Node *createNode(T);
    Node *rmod(Node *);
    void raise(Node *);
    void transplant(Node *,Node *);
    void _display(Node *);
    void _clear(Node *);
	Node *root, *NIL;
public:
    class Iterator{
    private:
        BinarySearchTree<T> *self;
        Node *cur;
    public:
        Iterator(BinarySearchTree<T>*, Node*);
        bool operator == (const Iterator &b)const;
        bool operator != (const Iterator &b)const;
        Iterator operator++();
        Iterator operator--();
        Iterator operator++(int);
        Iterator operator--(int);
        T operator *()const;
    };
    BinarySearchTree();
    BinarySearchTree(BinarySearchTree &);
	BinarySearchTree& operator= (BinarySearchTree &);
	~BinarySearchTree();
	void insert(T);
    void erase(T);
    void display();
    void clear();
    
	Iterator begin();	
    Iterator rbegin();
    Iterator end();
    Iterator rend();
};

template<typename T>
BinarySearchTree<T>::BinarySearchTree(){
    root = nullptr;
    NIL = new Node();
}

template<typename T>
BinarySearchTree<T>::BinarySearchTree(BinarySearchTree<T> &x){
	root = nullptr;
	NIL = new Node();
	for(BinarySearchTree<T>::Iterator it=x.begin(); it!=x.end(); it++){
		this->insert(*it);
	}
}

template<typename T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=(BinarySearchTree<T> &x){
	if(x.root == this->root)return *this;
	else{
		this->clear();
		for(BinarySearchTree<T>::Iterator it=x.begin(); it!=x.end(); it++){
			this->insert(*it);
		}
		return *this;
	}
}

template<typename T>
void BinarySearchTree<T>::_clear(Node *x){
	if(x->flag[0])_clear(x->ch[0]);
	if(x->flag[1])_clear(x->ch[1]);
	delete x;
}

template<typename T>
void BinarySearchTree<T>::clear(){
	root = nullptr;
	delete NIL;
	NIL = new Node();
}

template<typename T>
BinarySearchTree<T>::~BinarySearchTree(){
	this->clear();
	delete NIL;
}

	
template<typename T>
typename BinarySearchTree<T>::Node *BinarySearchTree<T>::createNode(T data){
	Node *cur = new Node();
	cur->data = data;
	cur->ch[0] = cur->ch[1] = cur->fa =  nullptr;
	cur->flag[0] = cur->flag[1] = false;
	return cur;
}

template<typename T>
void BinarySearchTree<T>::_display(Node *x){
    if(x->flag[0])_display(x->ch[0]);
    cout << x->data << " " <<x->flag[0] << " "<< x->ch[0]->data << " " << x->flag[1] << " " << x->ch[1]->data << endl;
    if(x->flag[1])_display(x->ch[1]);
}

template<typename T>
void BinarySearchTree<T>::raise(Node *x){
    assert(x->flag[0] == false && x->flag[1] == false);
    Node *y = x->fa;
    if(y == nullptr){
        root = nullptr;
    }else{
        int t = (y->ch[1] == x) ? 1 : 0;
        y->ch[t] = x->ch[t];
        y->flag[t] = false;
    }
}

template<typename T>
typename BinarySearchTree<T>::Node * BinarySearchTree<T>::rmod(BinarySearchTree<T>::Node *x){
    // raise son of x
    assert((x->flag[0] == true || x->flag[1] == true) && (x->flag[0]==false || x->flag[1] == false));
    int t = x->flag[1] ? 1 : 0;
    Node *z = x->fa, *y = x->ch[t];
    y->fa = z;
    if(z==nullptr){
        root = y;
    }else{
        z->ch[z->ch[1] == x ? 1 : 0] = y;
    }
    Node *v = x->ch[t];
    while(v->flag[t^1])v=v->ch[t^1];
    v->ch[t^1] = x->ch[t^1];
    return y;
}

template<typename T>
void BinarySearchTree<T>::transplant(BinarySearchTree<T>::Node *x, BinarySearchTree<T>::Node *y){
    Node *z = x->fa;
    y->fa = z;
    if(z == nullptr){
        root = y;
    }else{
        z->ch[z->ch[1] == x] = y;
    }
    Node *v = x->ch[1];
    if(x->flag[1]){
	    while(v->flag[0])v = v->ch[0];
	    v->ch[0] = y;
	}
    v = x->ch[0];
    while(v->flag[1])v = v->ch[1];
    v->ch[1] = y;

    y->ch[0] = x->ch[0];
    y->flag[0] = x->flag[0];
	if(y->flag[0])y->ch[0]->fa = y;
	
    y->ch[1] = x->ch[1];
    y->flag[1] = x->flag[1];
    if(y->flag[1])y->ch[1]->fa = y;
}

template<typename T>
void BinarySearchTree<T>::erase(T data){
    Node *y = nullptr, *x = this->root;
    while(x != nullptr){
        y = x;
        if(data < x->data){
            if(x->flag[0])x = x->ch[0];
            else{return;}
        }else if(data > x->data){
            if(x->flag[1])x = x->ch[1];
            else{return;}
        }else{
            break;
        }
    }

    if(x->flag[0] == false && x->flag[1] == false){
        raise(x); delete x;
    }else if(x->flag[0] == false || x->flag[1] == false){
        rmod(x); delete x;
    }else{
        Node *v = x->ch[1];
        while(v->flag[0])v = v->ch[0];
        if(v->flag[0]==false && v->flag[1]==false)raise(v);
        else rmod(v);
        transplant(x, v);
    }
}

template<typename T>
void BinarySearchTree<T>::insert(T data){
    Node *y = nullptr;
    Node *x = root;
    while(x != nullptr){
        y = x;
        if(data < x->data){
            if(x->flag[0]) x = x->ch[0];
            else    break;
        }
        else{
            if(x->flag[1]) x = x->ch[1];
            else    break;
        }
    }
    if(y == nullptr){root = createNode(data); root->ch[1] = root->ch[0] = NIL;}
    else{
        if(data < y->data){
            x = y->ch[0];
            y->ch[0] = createNode(data); 
            y->ch[0]->fa = y;
            y->flag[0] = true;
            y->ch[0]->ch[1] = y;
            y->ch[0]->ch[0] = x;
        }
        else{
            x = y->ch[1];
            y->ch[1] = createNode(data); 
            y->ch[1]->fa = y;
            y->flag[1] = true;
            y->ch[1]->ch[1] = x;
            y->ch[1]->ch[0] = y;
        }
    }
}

template<typename T>
BinarySearchTree<T>::Iterator::Iterator(BinarySearchTree<T>* _self, BinarySearchTree<T>::Node *_node){
    this->self = _self;
    this->cur = _node;
}

template<typename T>
bool BinarySearchTree<T>::Iterator::operator==(const BinarySearchTree<T>::Iterator &b)const{
    return this->cur == b.cur;
}

template<typename T>
bool BinarySearchTree<T>::Iterator::operator!=(const BinarySearchTree<T>::Iterator &b)const{
    return this->cur != b.cur;
}

template<typename T>
typename BinarySearchTree<T>::Iterator BinarySearchTree<T>::Iterator::operator++(){
    if(this->cur == self->NIL) return *this;
    if(this->cur->flag[1] == false){
        this->cur = this->cur->ch[1];
    }else{
        this->cur = this->cur->ch[1];
        while(this->cur->flag[0])
            this->cur = this->cur->ch[0];
    }
    return *this;
}

template<typename T>
typename BinarySearchTree<T>::Iterator BinarySearchTree<T>::Iterator::operator--(){
    if(this->cur == self->NIL) return *this;
    if(this->cur->flag[0] == false){
        this->cur = this->cur->ch[0];
    }else{
        this->cur = this->cur->ch[0];
        while(this->cur->flag[1])
            this->cur = this->cur->ch[1];
    }
    return *this;
}

template<typename T>
typename BinarySearchTree<T>::Iterator BinarySearchTree<T>::Iterator::operator++(int){
    Iterator tmp = *this;
    this->operator++();
    return tmp;
}

template<typename T>
typename BinarySearchTree<T>::Iterator BinarySearchTree<T>::Iterator::operator--(int){
    Iterator tmp = *this;
    this->operator--();
    return tmp;
}
template<typename T>
T BinarySearchTree<T>::Iterator::operator*()const{
    return this->cur->data;
}

template<typename T>
typename BinarySearchTree<T>::Iterator BinarySearchTree<T>::begin(){
    Node *t = this->root;
    while(t->flag[0])
        t = t->ch[0];
    Iterator it(this, t);
    return it;
}

template<typename T>
typename BinarySearchTree<T>::Iterator BinarySearchTree<T>::rbegin(){
    Node *t = this->root;
    while(t->flag[1]) t = t->ch[1];
    return Iterator(this, t);
}

template<typename T>
typename BinarySearchTree<T>::Iterator BinarySearchTree<T>::rend(){
    return this->end();
}

template<typename T>
typename BinarySearchTree<T>::Iterator BinarySearchTree<T>::end(){
    return Iterator(this, this->NIL);
}

template<typename T>
void BinarySearchTree<T>::display(){
	cout << root->data << endl;
    _display(root);
}
const int MAXN = 20;
int data[MAXN<<1];

int main(){
    srand(0);
    BinarySearchTree<int> b;
    for(int i=1;i<=MAXN;i++)data[i] = i;
    random_shuffle(data+1,data+1+MAXN);
    for(int i=1;i<=MAXN;i++){
        b.insert(data[i]);
        cout << "insert " << data[i] << endl;
    }
    for(int i=1;i<=MAXN/3;i++){
        cout << "delete " << data[i] << endl;
        b.erase(data[i]);
        
    }
    cout << "increasing inOrder" << endl;
    for(BinarySearchTree<int>::Iterator it=b.begin(); it!=b.end(); it++){
        cout << *it << " ";
    }
    cout << endl;
    cout << "decreasing inOrder" << endl;
    for(BinarySearchTree<int>::Iterator it=b.rbegin(); it!=b.rend(); it--){
        cout << *it << " ";
    }
	return 0;
}

