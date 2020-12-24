#include<cstdio>
#include"Heap.h"
int n;
int main(){
	yyx::Heap<int> h;
	h.push(-4);
	h.push(-2);
	h.push(-4);
	h.push(-5);
	h.push(-1);

	while(h.size()){
		printf("%d ",-h.top());
		h.pop();
	}
	return 0;
}
