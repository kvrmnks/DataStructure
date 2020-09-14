#include"LinkedList.h"
template<typename value_type>
class Queue{
	LinkedList<value_type> *list;
public:	
	Queue(){
		list = new LinkedList<value_type>();
	}
	Queue(Queue &b){
		list = new LinkedList<value_type>(*(b.list));
	}
	Queue& operator=(Queue &b){
		if(*(this->list) == *(b.list)) return *this;
		list = new LinkedList<value_type>(*(b.list));
		return *this;	
	}
	int size(){
		return list->size();	
	}
	value_type front(){
		return *(list->begin());
	}
	void push(value_type x){
		list->pushFront(x);			
	}
	
	void pop(){
		list->popFront();
	}
};


