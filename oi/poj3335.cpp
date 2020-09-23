#include<cstdio>
#include<algorithm>
#include<cmath>
#include<iostream>
using namespace std;
typedef double db;
int T,n;
struct Point{
	db x,y;
	Point(){};
	Point(double a,double b):x(a),y(b){}
	void display(){
		cout << "x = "<< x << " y = " << y << endl;
	}
};
typedef Point Vector;
Vector operator - (Point a, Point b){
	return Vector(a.x - b.x , a.y - b.y);
}
Vector operator + (Vector a, Vector b){
	return Vector(a.x + b.x, a.y + b.y);
}
Vector operator * (db x, Vector a){
	return Vector(x*a.x, x*a.y);
}
db operator ^ (Vector a, Vector b){
	return a.x*b.y - a.y*b.x;
}
struct Line{
	Point p;
	Vector v;
	db arg;
	Line(){}
	Line(Point p0, Vector v0){
		p = p0;
		v = v0;
		arg = atan2(v.y, v.x);	
	}
	bool operator < (Line b)const{
		if(this->arg != b.arg)
			return this->arg < b.arg;
		else{
			return (this->v ^ (b.p - this->p)) <= 0;
		}
	}
};
const int MAXN = 200;

Point p[MAXN];
Line line[MAXN];
Line Q[MAXN];
Point line_intersection(Line &a, Line &b){
	Vector tmp = a.p - b.p;
	double t = (tmp ^ b.v)/(a.v ^ b.v);	
	return a.p + t*a.v;
}	
bool on_right(Line &a, Line &b, Line &c){
	Point y = line_intersection(b,c);
	return (a.v ^ (y - a.p)) < 0;
}
db area(){
	db ret = 0;
	for(int i=2;i<=n;i++){
		ret += (p[i-1] - p[1]) ^ (p[i] - p[1]);
	}
	return ret;
}
bool half_plane_intersection(){
	for(int i=1;i<=n;i++){
		puts("*************");
		Point e = line[i].p + line[i].v;
		Point s = line[i].p;
		cout << s.x << " " << s.y << " " << e.x << " " << e.y << endl;
	}
	cout << endl;
	int L=0,R=0;
	for(int i=1;i<=n;i++){
		if(i>1 && line[i].arg == line[i-1].arg){
			continue;	
		}
		while(R-L>=2 && on_right(line[i], Q[L], Q[L+1]))L++;
		while(R-L>=2 && on_right(line[i], Q[R-1], Q[R-2]))R--;
//		puts("***********************");
		Q[R++] = line[i];
//		for(int i=L;i<R;i++){
//			Point e = Q[i].p + Q[i].v;
//			cout << Q[i].p.x << " " << Q[i].p.y << " " << e.x << " " << e.y << endl;
//		}
	   	
	}
	while(R-L>=2 && on_right(Q[L],Q[R-1],Q[R-2]))R--;
	while(R-L>=2 && on_right(Q[R-1], Q[L], Q[L+1]))L++;
	return R-L>=3;
}
void solve(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		db x,y;
		scanf("%lf%lf",&x,&y);
		p[i] = Point(x,y);
	}
	if(area() < 0)
		reverse(p+1,p+1+n);
	for(int i=2;i<=n;i++){
		line[i] = Line(p[i], p[i] - p[i-1]);
		Vector tmp = p[i];
	}
	line[1] = Line(p[n], p[1] - p[n]);
	sort(line+1,line+1+n);
	
	puts(half_plane_intersection()?"YES":"NO");
}
int main(){
	scanf("%d",&T);
	while(T--){
		solve();		
	}
}
