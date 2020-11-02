#include<iostream>
using namespace std;
const int MAXN = 200000;
int N,n,fenwick[MAXN];

void update(int idx, int delta){
    while(idx <= N){
        fenwick[idx] += delta;
        idx += idx&-idx;
    }
}

int query(int idx){
    int sum = 0;
    while(idx > 0){
        sum += fenwick[idx];
        idx -= idx&-idx;
    }
    return sum;
}

void pre_computation(int *arr, int n){
    for(int i=0;(n>>i)>0;i++){
        for(int j=0;j<=(n>>(i+1));j++){
        	int idx1 = (j<<(i+1)) + (1<<i), idx2 = (j<<(i+1)) + ((1<<i)<<1);
			if(idx2 <= n)
            	arr[idx2] += arr[idx1];
        }
    }

}
int main(){
    scanf("%d%d",&N,&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&fenwick[i]);
    }
    pre_computation(fenwick, n);
    
    // test1
    for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++){
			cout << "query "<<i<<" " << j<<endl<<query(j)-query(i-1)<<endl;
		}
	}
	update(3, -53);//test modify
	cout << endl;
	//test1
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++){
			cout << "query "<<i<<" " << j<<endl<<query(j)-query(i-1)<<endl;
		}
	}
    
    return 0;
}
/* test_data
8 8
1 2 53 3 5 8 3 3

*/
