#ifndef __HEAP__
#define __HEAP__

#include"Algorithm.h"
#include<vector>
namespace yyx{

template<typename T>
class Heap{
	private:
		std::vector<T> *heap;
		
		//maintain up
		void pushup(int loc){
			int father = 0;
			while(loc != 0){
				father = (loc&1) ? loc/2 : loc/2-1;
				if((*heap)[father] < (*heap)[loc]){
					yyx::swap((*heap)[father], (*heap)[loc]);
				}
				loc = father;
			}
		}
		
		//maintain down
		void pushdown(){
			int loc = 0, flag = -1;
			do{
				flag = -1;
				int left_son = loc * 2 + 1;
				int right_son = loc * 2 + 2;
				T cur = (*heap)[loc];
				if(left_son < size() && cur < (*heap)[left_son]){
					cur = (*heap)[left_son];
					flag = 0;
				}
				if(right_son < size() && cur < (*heap)[right_son]){
					cur = (*heap)[right_son];
					flag = 1;
				}
				if(flag == 0){
					yyx::swap((*heap)[loc], (*heap)[left_son]);
					loc = left_son;
				}else if(flag == 1){
					yyx::swap((*heap)[loc], (*heap)[right_son]);
					loc = right_son;
				}
			}while(flag != -1);
		}
		
	public:
		
		Heap(){
			heap = new std::vector<T>;
		}
		
		~Heap(){
			delete heap;
			heap = nullptr;
		}
		
		Heap(Heap &b){
			if(b == *this)
				return;
			if(heap != nullptr)
				delete[] heap;
			heap = new std::vector<T>(*b.heap);
		}
		
		Heap& operator=(Heap &b){
			if(*this == b)
				return *this;
			if(heap != nullptr)
				delete[] heap;
			heap = new std::vector<T>(*b.heap);
		}
		
		int size(){
			return heap->size();
		}
		
		T& top(){
			return heap->front();
		}
		
		void push(T x){
			this->heap->push_back(x);
			pushup(size()-1);
		}
		
		void pop(){
			T x = this->heap->back();
			this->heap->pop_back();
			(*this->heap)[0] = x;
			pushdown();
		}
	};
};
#endif
