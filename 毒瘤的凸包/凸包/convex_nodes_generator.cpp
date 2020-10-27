#include<iostream>
#include<ctime>
#include<cstdio>
using namespace std;
int main(){
	srand(time(0));
	int n = 100;
	freopen("node_list.txt", "w", stdout);
	printf("%d\n", n);
	for(int i=1;i<=n;i++){
		printf("%d %d\n", rand(), rand());
	}
	return 0;
}
