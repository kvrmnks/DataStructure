#ifndef __STACK__
#define __STACK__
#include"LinkedList.h"
template<typename value_type>
class Stack{
	LinkedList<value_type> *list;
	public:
	Stack(){
		list = new LinkedList<value_type>();
	}
	
	void push(value_type data){
		 list->pushFront(data);
	//	 list->display();
	}
	value_type top(){
		return *(list->begin());
	}
	
	void pop(){
		list->popFront();
	}
	int size(){
		return list->size();
	}
	
	void clear(){
		list->clear();
	}
	~Stack(){
		delete list;
	}
	
	Stack & operator = (Stack &b){
		if(*(this->list) == (*b.list)) return *this;
		this->list = new LinkedList<value_type>(*b.list);
		return *this;
	}

	Stack(Stack& b){
		this->list = new LinkedList<value_type>(*b.list);

	}
};
#endif
