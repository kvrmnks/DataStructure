#include"Stack.h"
#include<iostream>
using namespace std;
int main(){
	yyx::Stack<int> s;
	for(int i=1;i<=10;i++)
		s.push(i);
	yyx::Stack<int> ttt;
	ttt = s;
	cout << ttt.size();
	for(int i=1;i<=10;i++){
		cout << s.top() << " " << s.size() << endl;
		s.pop();
	}
	return 0;
}
