#ifndef __LINKEDLIST__
#define __LINKEDLIST__
#include<iostream>
template<typename T>
class LinkedList{
private:
	struct Node{
		Node *next, *previous;
		T data;
	};
	Node *head, *tail;
	Node *createEmptyNode(){
		Node *ptr = new Node();
		ptr->next = ptr->previous = nullptr;
		return ptr;
	}
	Node *createNode(T data){
		Node *ptr = new Node();
		ptr->next = ptr->previous = nullptr;
		ptr->data = data;
		return ptr;
	}
public:
	class Item{
	private:
		Node *currentNode;
		LinkedList<T> *list;
	public:
		Item(Node *x, LinkedList<T> *_l){
			currentNode = x;
			list = _l;
//			list->_tail = _l;
		}	
		Item& advance(){
			if(currentNode == nullptr)
				return *this;
			if(currentNode -> next != nullptr){
				currentNode = currentNode -> next;
			}
			return *this;
		}	
		
		Item& backward(){
			if(currentNode == nullptr)
				return *this;
			if(currentNode -> previous != nullptr){
				currentNode = currentNode -> previous;
			}
			return *this;
		}
		
		// forward
		Item& operator++(){
			this->advance();
			return *this;
		}
		Item& operator++(int){
			Item &tmp = *this;
			this->advance();
			return tmp;
		}
		// backward 
		Item& operator--(){
			this->backward();
			return *this;
		}
		
		Item& operator--(int){
			Item& tmp = *this;
			this->backward();
			return tmp;
		}
		
		// get the data
		T operator*(){
			return currentNode -> data;
		}
		
		// add the data into this place
		Item& insert(T data){
			(*(list->_size)) ++;
			if(currentNode == list->head){
				list -> head = list->createNode(data);
				list -> head -> next = currentNode;
				currentNode -> previous = list->head;
			}else{
				Node *pre = currentNode -> previous;
				pre -> next = list -> createNode(data);
				pre -> next -> previous = pre;
				pre -> next -> next = currentNode;
				currentNode -> previous = pre -> next;  
			}
			return *this;
		}
		
		// jump to the previous node after erasing
		Item& erase(){
			if(currentNode == list->tail) return *this;
			(*(list->_size)) --;
			if(currentNode == list->head){
				Node *tmp = currentNode -> next;
				delete list->head;
				list -> head = currentNode = tmp;
			}else{
				Node *pre = currentNode -> previous;
				Node *nx = currentNode -> next;
				delete currentNode;
				currentNode = pre;
				pre -> next = nx;
				nx -> previous = pre;
			}
			return *this;
		}
		
		Item &operator ~(){
			return this->erase();
		}
		
		bool operator == (Item &b){
			return this->currentNode == b.currentNode;
		}
		
		bool operator != (Item b)const{
			return this->currentNode != b.currentNode;
		}
		
		~Item(){
		}
	};
	int *_size;

	LinkedList(){
		head = tail = createEmptyNode();
		_size = new int;
		*_size = 0;
	}
	
	void clear(){
		Node *nx = head -> next;
		while(head != tail){
			nx = head -> next;
			delete head;
			head = nx;
		}
		*_size = 0;
	}
	
	int size()const{
		return *_size;
	}
	
	bool isEmpty()const {
		return head == tail;
	}

	Item begin(){
		return Item(head, this);
	}
	
	Item end(){
		return Item(tail, this);
	}
	void display(){
		for(LinkedList<int>::Item it=this->begin();it!=this->end();it++){
			std::cout << *it << std::endl;
		}
	}
	
	void pushBack(T data){
		this->end().insert(data);
	}
	
	void pushFront(T data){
		this->begin().insert(data);
	}
	
	void popBack(){
		~(this->end()--);
	}
	
	void popFront(){
		~(this->begin());
	}
	
	bool operator == (LinkedList b){
		if(this->size() != b.size()) return false;
		LinkedList<T>::Item it1 = this->begin();
		LinkedList<T>::Item it2 = b.begin();
		while(it1!=this->end() && it2!=b.end()){
			if(*it1 != *it2) return false;
			it1++;
			it2++;
		}
		return true;
	}
	
	LinkedList& operator = (LinkedList &b){
		if(b == *this) return *this;
		this->clear();
		(*(this->_size)) = (b.size());
		for(LinkedList<T>::Item it=b.begin();it!=b.end();it++){
			this->pushBack(*it);
		}
		return *this;
	}
	
	LinkedList(LinkedList &b){
		head = tail = createEmptyNode();
		_size = new int;
		(*_size) = (b.size());
		for(LinkedList<T>::Item it=b.begin();it!=b.end();it++){
			this->pushBack(*it);
		}
	}
	
	~LinkedList(){
		clear();
		delete _size;
	}
};
#endif
