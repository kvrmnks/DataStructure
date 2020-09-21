#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<iostream>
using namespace std;
struct Vector{
	double x,y;
	Vector(){}
	Vector(double x0, double y0){
		x = x0;
		y = y0;
	}
};
Vector operator - (Vector a, Vector b){
	return Vector(a.x-b.x, a.y-b.y);
}
double operator ^ (Vector a, Vector b){
	return a.x*b.y - a.y*b.x;
}
double len(Vector a){
	return sqrt(a.x*a.x + a.y*a.y);
}
bool operator < (Vector a, Vector b){
	if(a.x < b.x)return true;
	if(a.x > b.x)return false;
	if(a.y < b.y)return true;
	return false;
}
const int MAXN = 2000;
int Q[MAXN],top,vis[MAXN];

int n,L;
Vector v[MAXN];
void gift_wrapping(){
	memset(Q, 0, sizeof Q);
	memset(vis, 0, sizeof vis);
	top=0;
	vis[1] = true;
	Q[++top]=1;
	while(true){
		int cur =-1;
		for(int i=1;i<=n;i++){
			if(!vis[i])cur = i;
		}
		if(cur == -1)break;
		for(int i=1;i<=n;i++){
			double arg = (v[i]-v[Q[top]])^(v[cur]-v[Q[top]]);
			double s1 = len(v[i]-v[Q[top]]);
			double s2 = len(v[cur]-v[Q[top]]);
			if(arg>0 || (arg==0 && s1>s2)){
				cur = i;
			}
		}
		if(vis[cur]!=0)break;
		vis[cur]=1;
		Q[++top]=cur;
	}
}
int main(){
	while(scanf("%d%d",&n,&L)!=EOF){
		for(int i=1;i<=n;i++){
			int a,b;
			scanf("%d%d",&a,&b);
			v[i] = Vector(a,b);
		}
		sort(v+1, v+1+n);
		gift_wrapping();
//		for(int i=1;i<=top;i++){
//			cout << v[Q[i]].x << " " << v[Q[i]].y << endl;
//		}
		double sum = 2*acos(-1)*L;
		for(int i=1;i<top;i++){
			sum += len(v[Q[i]] - v[Q[i+1]]);
		}
		sum += len(v[Q[1]]-v[Q[top]]);
		printf("%.f\n",sum);
	}
}
