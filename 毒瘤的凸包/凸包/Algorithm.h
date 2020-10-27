#ifndef __ALGORITHM__
#define __ALGORITHM__
#include "Stack.h"
namespace yyx{
	// swap two pointer
	template<typename T>
	void swap(T *x, T *y){
		T tmp = *x;
		*x = *y;
		*y = tmp;
	}
	
	//swap two value
	template<typename T>
	void swap(T &x, T &y){
		T tmp = x;
		x = y;
		y = tmp;
	}
	
	//quick sort using recursive method
	template<typename T>
	void quick_sort_recursive(T *a, T *b){
		struct pair{
			T *L, *R;
			pair(T *x, T *y){
				L = x;
				R = y;
			}
			pair(){
				L = R = nullptr;
			}
		};
		Stack<pair> *stack = new Stack<pair>();
		stack->push(pair(a, b));
		while(stack->size()){
			T *l = stack->top().L;
			T *r = stack->top().R;
			stack->pop();
			if(l+1 >= r)
				continue;
			T *p = l + 1, *q = r-1;
			do{
				while(*p < *l && p < r) p++;
				while(*l < *q && q > l) q--;
				if(p <= q){
					swap(p, q);
					p++;
					q--;
				}
			}while(p <= q);
			swap(l, q);
			if(l < q) stack->push(pair(l, q));
			if(q+1 < r)stack->push(pair(q+1, r));
		}
	}
	
	//quick sort using recursive method with cmp functions
	template<typename T>
	void quick_sort_recursive(T *a, T *b, bool (*cmp)(const T&a,const T&b)){
		struct pair{
			T *L, *R;
			pair(T *x, T *y){
				L = x;
				R = y;
			}
			pair(){
				L = R = nullptr;
			}
		};
		Stack<pair> *stack = new Stack<pair>();
		stack->push(pair(a, b));
		while(stack->size()){
			T *l = stack->top().L;
			T *r = stack->top().R;
			stack->pop();
			if(l+1 >= r)
				continue;
			T *p = l + 1, *q = r-1;
			do{
				while((*cmp)(*p, *l) && p < r) p++;
				while((*cmp)(*l, *q) && q > l) q--;
				if(p <= q){
					swap(p, q);
					p++;
					q--;
				}
			}while(p <= q);
			swap(l, q);
			if(q+1 < r)stack->push(pair(q+1, r));
			if(l < q) stack->push(pair(l, q));
		}
	}
	
	//quick sort
	template<typename T>
	void quick_sort(T *l, T *r){
		if(l + 1 >= r)
			return;
		T *p = l+1, *q = r-1;
		do{
			while(*p < *l && p < r) p++;
			while(*l < *q && l < q) q--;
			if(p <= q){
				swap(p, q);
				p++;
				q--;
			}
		}while(p <= q);
		swap(l, q);
		if(l < q)quick_sort(l, q);
		if(q+1 < r)quick_sort(q+1, r);
	}
	
	//quick sort with cmp function
	template<typename T>
	void quick_sort(T *l, T *r, bool (*cmp)(const T &x,const T &y)){
		if(l + 1 >= r)
			return;
		T *p = l + 1, *q = r - 1;
		do{
			while((*cmp)(*p, *l) && p < r) p++;
			while((*cmp)(*l, *q) && l < q) q--;
			if(p <= q){
				swap(p, q);
				p ++;
				q --;
			}
		}while(p <= q);
		swap(l, q);
		if(l < q) quick_sort(l, q);
		if(q + 1 < r) quick_sort(q+1, r);
	}
}
#endif
