#include "Queue.h"
#include <iostream>
using namespace std;
int main(){
	Queue<int> q;
	for(int i=1;i<=10;i++){
		q.push(i);
	}
	for(int i=1;i<=10;i++){
		cout << q.front() << " " << q.size() << endl;
		q.pop();
	}
	return 0;
}
