#ifndef __VECTOR__
#define __VECTOR__
#include<cstring>
#include<cstdio>
namespace yyx{
	template<typename T>
	class Vector{
		private:
			int m_size, m_capacity;
			T *data;
			void maintain(){
				if(m_size >= m_capacity){
					m_capacity <<= 1;
					T *tmp = new T[m_capacity];
					memcpy(tmp, data, m_capacity * sizeof(T));
					delete[] data;
					data = tmp;
				}	
			}
		public:
			Vector(int size = 10){
				this->m_size = 0;
				m_capacity = 1;
				while(m_capacity < size){
					m_capacity <<= 1;
				}
				data = new T[m_capacity];
			}
			
			~Vector(){
				if(data != nullptr){
					delete[] data;
				}	
				m_size = m_capacity = 0;
			}	
			
			Vector(Vector &b){
				if(*this == b) return;
				if(data != nullptr){
					delete[] data;
				}
				data = new T[b.m_capacity * sizeof(T)];
				m_size = b.m_size;
				m_capacity = b.m_capacity;
				memcpy(data, b.data, m_size * sizeof(T));
			}
			
			Vector& operator = (Vector &b){
				if(*this == b) return *this;
				if(data != nullptr){
					delete[] data;
				}	
				data = new T[b.m_capacity * sizeof(T)];
				m_size = b.m_size;
				m_capacity = b.m_capacity;
				memcpy(data, b.data, m_size * sizeof(T));
			}
			
			T& operator[] (int x){
				return data[x];
			}

			T& back(){
				return data[m_size-1];
			}
			
			T& front(){
				return data[0];
			}

			void pop_back(){
				m_size --;
			}

			int size()const{
				return m_size;
			}
			
			int capacity()const{
				return m_capacity;
			}
			
			void push_back(T x){
				m_size ++;
				maintain();
				data[m_size-1] = x;
			}
	};
}
int main(){
	using namespace yyx;
	Vector<int> a;
	for(int i=0;i<100;i++){
		a.push_back(i);
	}
	for(int i=0;i<a.size();i++){
		printf("%d %d\n", a[i], a.capacity());
	}
	return 0;

}

#endif
