#include<algorithm>
#include"Stack.h"
#include<fstream>
#include<cmath>
using namespace std;
using namespace yyx;
struct Vector{
	double x,y;
	Vector(){}
	Vector(double x0,double y0){x=x0;y=y0;}
};
double operator ^ (Vector a, Vector b){
	return a.x*b.y - a.y*b.x;
}
Vector operator - (Vector a, Vector b){
	return Vector(a.x-b.x, a.y-b.y);
}
double norm2(Vector a){
	return sqrt(a.x*a.x + a.y*a.y);
}

bool cmp2(Vector a, Vector b){
	double cross = a ^ b;
	if(cross == 0){
		return norm2(a) < norm2(b);
	}
	return cross > 0;
}

bool cmp(Vector a, Vector b){
	if(a.y == b.y) return a.x < b.x;
	return a.y< b.y;
}
void graham(Stack<Vector> *s, Vector v[], int length){
	s->push(v[1]);
	s->push(v[2]);
	for(int i=3;i<=length;i++){
		while(s->size() >= 2){
		//	cout << i << endl;
			Vector cur = s->top();
			s->pop();
			Vector root = s->top();
			double cross = (v[i] - root) ^ (cur - root);

			if(cross > 0 || (cross==0 && norm2(v[i]-root) > norm2(cur-root)) ){
				;//s -> push(v[i]);
			}else{
				s -> push(cur);
				//s -> push(v[i]);
				break;
			}
		}		
		s -> push(v[i]);
	}
	s -> pop();
}
int node_size;
Vector *node;
Stack<Vector> *stack;
int main(){
	ifstream in("node_list.txt");
	in >> node_size;
	node = new Vector[node_size+2];
	for(int i=1;i<=node_size;i++){
		int a,b;
		in >> a >> b;
		node[i] = Vector(a,b);
	}
	sort(node+1, node+1+node_size, cmp);
	for(int i=2;i<=node_size;i++){
		node[i] = node[i] - node[1];
	}
	Vector root = node[1];
	node[1] = Vector(0, 0);
	sort(node+2, node+1+node_size, cmp2);
	node[++node_size] = Vector(0,0);
	stack = new Stack<Vector>();
	graham(stack, node, node_size);
	ofstream out("convex_nodes.txt");
	out << stack->size() << endl;
	while(stack->size()){
		out << stack->top().x+root.x << " " << stack->top().y+root.y << endl;
		stack->pop();
	}
	delete[] node;
	delete stack;
	return 0;
}
