#include<iostream>
#include"LinkedList.h"
int main(){
	LinkedList<int> l;
	
	LinkedList<int>::Item it = l.begin();
	for(int i=1;i<=10;i++)
		it.insert(i);	
	std::cout << l.size() << std::endl;
	
	l.clear();//��� 
	std::cout << l.size() << std::endl;
	
	for(int i=1;i<=10;i++)
		it.insert(i);
	
	it = l.end();
	do{
		it--;
		std::cout << *it << " ";
	}while(it != l.begin());//������� 
	std::cout << std::endl;
	std::cout << l.size() << std::endl << std::endl;
	
	it = l.end();
	it--;
	for(int i=1;i<=5;i++){
		~it;//ɾ�� 
	}
	l.display();
	std::cout << std::endl;
	it--;
	it.insert(998244343);//���� 
	l.display();
	return 0;
}
