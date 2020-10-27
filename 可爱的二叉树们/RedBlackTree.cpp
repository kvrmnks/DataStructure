#include<bits/stdc++.h>
using namespace std;
typedef int valueType;
#define BLACK 1
#define RED 0
#define debug(x) cout << #x << " = " << x <<endl;
bool debug_flag = false;
class RedBlackTree{
private:
	struct Node{
		Node *ch[2],*p;
		int color,sz,height;
		valueType key;
	};
	valueType tmp;
	Node *createNode(valueType x);
	void update(Node *x);
	void rotate(Node *x);
	Node *treeMinimum(Node *x);
	void treeInsert(Node *x, Node *v);
	void treeInsertFixup(Node *x);
	void treeRemoveFixup(Node *x);
	void treeRemove(Node *x, Node *v);
	void treeTransplant(Node *x, Node *y);
	void treeBruteForceMinimum(Node *x);
public:Node *NIL;
	Node *root;
	RedBlackTree();
	void insert(valueType v);
	void remove(valueType v);
	valueType bruteForceMinimum();
	valueType minimum();
	void display_tree(Node *x);
	void make_height(Node *x);
	bool check_balance(Node *x);
	bool check_red(Node *x);
	
};

RedBlackTree::Node *RedBlackTree::createNode(valueType v){
	Node *x = new Node();
	x->ch[0] = x->ch[1] = x->p = NIL;
	x->color = RED; x->sz = 1;
	x->key = v;
	return x;
}

void RedBlackTree::update(Node *x){
	x->sz = x->ch[0]->sz + x->ch[1]->sz + 1;
}

void RedBlackTree::rotate(Node *x){
	Node *y=x->p, *z=y->p;
	if(y == root) root = x;
	int t = (y->ch[1] == x);
	z->ch[z->ch[1] == y] = x;
	x->p = z; y->p = x;
	x->ch[t^1]->p = y;
	y->ch[t] = x->ch[t^1];
	x->ch[t^1] = y;
	update(y); update(x);
}

RedBlackTree::Node *RedBlackTree::treeMinimum(Node *x){
	Node *y = x;
	while(x != NIL){y = x; x = x->ch[0];}
	return y;
}

RedBlackTree::RedBlackTree(){
	NIL = new Node();
	NIL->ch[0] = NIL->ch[1] = NIL->p = NIL;
	NIL->color = BLACK; NIL->sz = 0;
	root = NIL;
}

void RedBlackTree::treeInsertFixup(Node *x){
	Node *y=x->p, *z=y->p;
	int t = (z->ch[1] == y);
	while(y->color == RED && y!=root){
		t = (z->ch[1] == y);
		Node *w = z->ch[t^1];
		if(w->color == RED){
			z->color = RED;
			y->color = w->color = BLACK;
			x = z;
		}else{
			if((z->ch[1] == y) ^ (y->ch[1] == x)){
				rotate(x);
				swap(x, y);
			}
			rotate(y);
			swap(y->color, z->color);
		}
		y = x->p; z = y->p;
	}
	root->color = BLACK;
}

void RedBlackTree::treeInsert(Node *x, Node *v){
	Node *y = NIL;
	while(x != NIL){
		y = x;
		if(v->key > x->key){x = x->ch[1];}
		else x = x->ch[0];
	}
	v->p = y;
	if(y == NIL){root = v;}
	else{
		if(v->key > y->key){y->ch[1] = v;}
		else{y->ch[0] = v;}
	}
	treeInsertFixup(v);
}	

void RedBlackTree::treeTransplant(Node *x, Node *y){
	if(x == root){
		root = y;
	}
	Node *z = x->p;
	z->ch[z->ch[1] == x] = y;
	y->p = z;
}

void RedBlackTree::treeRemoveFixup(Node *x){
	while(x->color == BLACK && x != root){
		
		Node *y = x->p;
		Node *w = y->ch[y->ch[0] == x];
		if(debug_flag){
			debug(x);
			debug(x->key);
			debug(y);
			debug(w);
		}
//		cout << x << endl;
		assert(w != NIL);
		if(w->color == RED){
			swap(y->color, w->color);
			rotate(w);
			continue;
		}
		int t = (y->ch[1] == x);
		if(w->color == BLACK && w->ch[t]->color == BLACK && w->ch[t^1]->color == BLACK){
			w->color = RED;
			x = y;
			continue;			
		}
		if(w->color == BLACK && w->ch[t]->color == RED && w->ch[t^1]->color == BLACK){
			swap(w->color, w->ch[t]->color);
			rotate(w->ch[t]);
			continue;
		}
		if(w->color == BLACK && w->ch[t^1]->color == RED){
			w->ch[t^1]->color = BLACK;
			swap(y->color, w->color);
			rotate(w);
			x = root;
		}
	}
	x->color = BLACK;
}

void RedBlackTree::treeRemove(Node *x, Node *y){
	while(x != NIL){
		if(x->key == y->key)break;
		else if(y->key > x->key) x = x->ch[1];
		else x = x->ch[0];
	}
	if(x == NIL)return;
	if(x->ch[0]==NIL && x->ch[1]==NIL){
		if(x->color == BLACK)treeRemoveFixup(x);
		treeTransplant(x, NIL);
	}else if(x->ch[0] == NIL || x->ch[1] == NIL){
		int t = (x->ch[0] == NIL);
		treeTransplant(x, x->ch[t]);
		if(x->color == BLACK) treeRemoveFixup(x->ch[t]);
	}else{
		Node *z = treeMinimum(x->ch[1]);
		Node *e = z->ch[1];
		bool flag = (e == NIL);
		int ocolor = z->color;
		z->color = x->color;
		if(flag){e = createNode(0); e->color=BLACK; e->p=z; z->ch[1]=e;}
		if(z == x->ch[1]){
			treeTransplant(x, z);
			z->ch[0] = x->ch[0];
			z->ch[0]->p = z;
		}else{
			treeTransplant(z, e);
			treeTransplant(x, z);
			z->ch[0] = x->ch[0];
			z->ch[1] = x->ch[1];
			z->ch[0]->p = z->ch[1]->p = z;
		}
		if(ocolor == BLACK) treeRemoveFixup(e);
		if(flag){treeTransplant(e, NIL); delete e;}
	}
}

void RedBlackTree::insert(valueType v){
	Node *x = createNode(v);
	treeInsert(root, x);
}

void RedBlackTree::remove(valueType v){
	Node *x = createNode(v);
	treeRemove(root, x);
}

valueType RedBlackTree::minimum(){
	return treeMinimum(root)->key;
}
int cnt = 0;
int n;
void RedBlackTree::display_tree(Node *x){
//	cout << x << endl;
	if(x == NIL)return;
	display_tree(x->ch[0]);
	cout << x->color << " " << x->key << " " << x->ch[0]->key << " " << x->ch[1]->key <<" " << x << " " << x->ch[0] << " " << x->ch[1]<<  endl;
//	cnt ++;
//	if(cnt == n){
//		printf("%d",x->key);
//	}else{
//		printf("%d ",x->key);
//	}
	display_tree(x->ch[1]);	
}

int mn = 0;
void RedBlackTree::make_height(Node *x){
	if(x == NIL)return;
	x->height += (x->color == BLACK);
	mn = max(mn, x->height);
	x->ch[0]->height = x->height;
	x->ch[1]->height = x->height;
	make_height(x->ch[0]);
	make_height(x->ch[1]);
}

bool RedBlackTree::check_balance(Node *x){
//	debug(x->key);
//	debug(x->height);
//	debug(mn);
	if(root == NIL)return true;
	if(x->ch[0]==NIL || x->ch[1]==NIL){
		if(x->ch[0]!=NIL)check_balance(x->ch[0]);
		if(x->ch[1]!=NIL)check_balance(x->ch[1]);
		if(x->height != mn) return false;
		else return true;
	}
		
	return check_balance(x->ch[0]) && check_balance(x->ch[1]);
}

void RedBlackTree::treeBruteForceMinimum(Node *x){
//	cout << x << endl;
	if(x == NIL)return;
	tmp = min(tmp, x->key);
	treeBruteForceMinimum(x->ch[0]);
	treeBruteForceMinimum(x->ch[1]);
}

valueType RedBlackTree::bruteForceMinimum(){
	this->tmp = 2147483647;
	treeBruteForceMinimum(this->root);
	return this->tmp;
	
}

bool RedBlackTree::check_red(Node *x){
	if(x == NIL)return true;
	if(x->color == RED && x->ch[0]->color == RED){return false;}
	if(x->color == RED && x->ch[1]->color == RED){return false;}
	return check_red(x->ch[0]) && check_red(x->ch[1]);
}

int main(){
//	freopen("P3378_8.in","r",stdin);
//	freopen("my.txt","w",stdout);
	scanf("%d",&n);
	RedBlackTree rbt;
	for(int i=1;i<=n;i++){
		int o;
		if(scanf("%d",&o)==EOF)break;
//		cout << endl;
////		cout << "fd";

//		debug(o);
//		debug(rbt.root->key);
//		mn =0;
//		if(i >= 59425){
//			debug_flag = true;
//			rbt.display_tree(rbt.root);
//		}
//		
//		rbt.root->height = 0;
//		rbt.make_height(rbt.root);
//		debug(i);
//		if(!rbt.check_balance(rbt.root)){exit(2);}
//		assert(rbt.check_red(rbt.root));
//		assert(rbt.check_balance(rbt.root));
//		debug(mn);
		switch(o){
			case 1:
				scanf("%d",&o);
				rbt.insert(o);
				break;
			case 2:
				printf("%d\n", rbt.minimum());
				break;
			case 3:
				rbt.remove(rbt.minimum());
				break;
		}
		

	}
	return 0;
	
}

