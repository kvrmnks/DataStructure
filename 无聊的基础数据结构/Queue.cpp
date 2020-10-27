#include "Queue.h"
#include <iostream>
using namespace std;
int main(){
	yyx::Queue<int> q;
	for(int i=1;i<=10;i++){
		q.push(i);
	}
	for(int i=1;i<=10;i++){
		cout << q.back() << " " << q.size() << endl;
		q.pop();
	}
	q.push(4);
	q.back() = 3;
	cout << q.back();
	return 0;
}
