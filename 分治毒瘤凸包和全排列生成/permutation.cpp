#include<iostream>
#include<cstdio>
using namespace std;
long long getrank(int *data, int length){
	int *count = new int[length+1];
	long long *factor = new long long[length+1];
	factor[0] = 1;
	for(int i=1;i<=length;i++)
		factor[i] = i * factor[i-1];
	for(int i=0;i<=length;i++)
		count[i] = 0;
	long long rk = 0;
	for(int i=1;i<=length;i++){
		long long tmp = 0;
		for(int j=1;j<data[i];j++)
			tmp += (count[j] == 0);
		rk += tmp * factor[length - i];
		count[data[i]] = 1;
	}
	return rk;
}

void get_permutation_by_rank(int *data,int length, long long rk){
	long long *factor = new long long[length+1];
	factor[0] = 1;
	for(int i=1;i<=length;i++)
		factor[i] = i * factor[i-1];	
	int *count = new int[length+1];
	for(int i=0;i<=length;i++)
		count[i] = 0;
	for(int i=1;i<=length;i++){
		int tmp = rk/factor[length-i] + 1;
		int pos = 0;
		for(int j=1;j<=length;j++){
			if(count[j] == 0)
				tmp --;
			if(tmp == 0){
				pos = j;
				break;
			}
		}
		data[i] = pos;
		count[pos] = 1;
		rk %= factor[length-i];
	}
}

bool has_next_permutation(int *data, int length){
	long long rk = 1;
	for(int i=2;i<=length;i++)
		rk *= i;
	return getrank(data, length)+1 < rk;
}

void next_permutation(int *data, int length){
	long long rk = getrank(data, length);
	get_permutation_by_rank(data, length, rk+1);
}

int test_data[10];

#define DISPLAY 5

void display(){
	for(int i=1;i<=DISPLAY;i++){
		cout << test_data[i] << " ";
	}
	cout << endl;
}
int main(){
	for(int i=1;i<=DISPLAY;i++){
		test_data[i] = i;
	}
	display();
	while(has_next_permutation(test_data, DISPLAY)){	
		next_permutation(test_data, DISPLAY);
		display();
	}
	return 0;
}
