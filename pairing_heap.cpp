#include<bits/stdc++.h>
using namespace std;
template<typename T>
class PairingHeap{
	private:
		struct Node{
			Node *ch[2];
			T v{};
		};
		Node *root;
		Node *mergeNode(Node *, Node *);
	public:
		PairingHeap();
		void merge(PairingHeap &b);
		T min();
		void pop();
		void insert(T);
};

template<typename T>
PairingHeap<T>::PairingHeap(){
	root = nullptr;
}

template<typename T>
typename PairingHeap<T>::Node * PairingHeap<T>::mergeNode(Node *x, Node *y){
	if(y == nullptr)return x;
	if(x == nullptr)return y;
	if(x->v > y->v)swap(x, y);
	if(x->ch[0] == nullptr){
		x->ch[0] = y;
		y->ch[1] = nullptr;
	}else{
		Node *tmp = x->ch[0];
		x->ch[0] = y;
		y->ch[1] = tmp;
	}
	return x;
}

template<typename T>
void PairingHeap<T>::merge(PairingHeap &b){
	Node *tmp = mergeNode(this->root, b.root);
	this->root = tmp;
	b.root = nullptr;
}

template<typename T>
T PairingHeap<T>::min(){
	if(this->root == nullptr)return T{};
	else{
		return this->root->v;
	}
}

template<typename T>
void PairingHeap<T>::pop(){
	if(this->root == nullptr)return;
	vector<Node *> Q;
	Node *cur = this->root->ch[0];
	while(cur != nullptr){
		Q.push_back(cur);
		cur = cur->ch[1];
	}
	for(int i=0;i<(int)Q.size()-1;i+=2){
		Q[i] = mergeNode(Q[i], Q[i+1]);
	}
	for(int i=2;i<(int)Q.size();i+=2){
		Q[0] = mergeNode(Q[0], Q[i]);
	}
	delete this->root;
	if(Q.size()>=1)this->root = Q[0];
}

template<typename T>
void PairingHeap<T>::insert(T v){
	PairingHeap<T> t;
	t.root = new Node();
	t.root->ch[0] = t.root->ch[1] = nullptr;
	t.root->v = v;
	this->merge(t);
}

int main(){
	PairingHeap<int> ph;
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int x;
		scanf("%d",&x);
		ph.insert(x);
	}
	for(int i=1;i<=n;i++){
		int x = ph.min();
		printf("%d ", x);
		ph.pop();
	}
	return 0;
}
