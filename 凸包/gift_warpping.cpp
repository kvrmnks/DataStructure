#include<cstdio>
#include<cmath>
#include<iostream>
#include<fstream>
#include"Queue.h"
#include<algorithm>
#include<cstring>
#include<ostream>
using namespace std;
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
bool cmp(Vector a, Vector b){
	if(a.x == b.x)
		return a.y < b.y;
	return a.x < b.x;
}

void giftWrapping(Queue<int> *q, Vector v[], int length){
	bool *is_choose = new bool[length+1];
	memset(is_choose, 0,(length+1)*sizeof(bool));
	q->clear();
	q->push(1);
	is_choose[1] = true;
	while(true){
		int cur = -1;
		for(int i=1;i<=length;i++){
			if(!is_choose[i]){
				cur = i;
				break;
			}
		}
		if(cur == -1)break;
		for(int i=1;i<=length;i++){
			double value = (v[i]-v[q->front()]) ^ (v[cur] - v[q->front()]);
			if(value>0 || (value==0 && norm2(v[i]-v[q->front()]) > norm2(v[cur] - v[q->front()]))){
				cur = i;
			}
		}
		if(is_choose[cur]){break;}
		q->push(cur);
		is_choose[cur] = true;
	}	
	delete is_choose;
}

int node_size;
Vector *node;
Queue<int> *q;
int main(){
	ifstream f("node_list.txt");
	f >> node_size;
	node = new Vector[node_size+1];
	for(int i=1 ; i <= node_size ; i++){
		int t1,t2;
		f >> t1 >> t2;
		node[i] = Vector(t1 , t2);
	}
	sort(node+1, node+1+node_size, cmp);
//	for(int i=1;i<=node_size;i++){
//		cout << node[i].x << " " << node[i]
//	}
	ofstream out("convex_nodes.txt");
	q = new Queue<int>();
	giftWrapping(q, node, node_size);
	out << q->size() << endl;
	while(q->size()){
		out <<  node[q->front()].x << " " << node[q->front()].y << endl;
	    q->pop();
		
	}
	return 0;
}
