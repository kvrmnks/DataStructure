#include<cstdio>
#include<algorithm>
#include"Algorithm.h"

int data[100001];
bool cmp(const int &x, const int &y){
	return x < y;
}
int main(){
	int n;
	n = 5;
	data[1] = 4;
	data[2] = 2;
	data[3] = 4;
	data[4] = 5;
	data[5] = 1; 
	std::random_shuffle(data+1,data+1+n);
	yyx::quick_sort_recursive(data+1, data+1+n, cmp);
	for(int i=1;i<=n;i++){
		printf("%d ",data[i]);
	}
	return 0;
}
