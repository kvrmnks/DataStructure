#include<bits/stdc++.h>
using namespace std;
typedef double db;
const db EPS = 1e-9;

struct Point{
	db x,y;
	Point(){}
	Point(db a,db b){
		x = a;
		y = b;
	}
	void display(){
		cout << "x = " << x << "y = "<< y<<endl;
	}
};
typedef Point Vector;
Vector operator - (Point a, Point b){	
	return Vector(a.x-b.x, a.y-b.y);
}
Vector operator + (Vector a, Vector b){
	return Vector(a.x+b.x, a.y+b.y);
}
Vector operator * (db x, Vector a){
	return Vector(a.x*x, a.y*x);
}
db operator ^ (Vector x, Vector y){
	return x.x*y.y - x.y*y.x;
}
struct Line{
	Point p;
	Vector v;
	db arg;
	Line(){}
	Line(Point a, Vector b){
		p = a;
		v = b;
		arg = atan2(v.y, v.x);
	}
	bool operator < (Line b)const{
		if(fabs(this->arg - b.arg) < EPS){
			return (this->v ^ (b.p - this->p)) < 0;
		}
			
		return this->arg < b.arg;
	}
};
const int MAXN = 10000;
int T,n;
Point data[MAXN], NQ[MAXN];
Line l[MAXN], Q[MAXN];
Point line_intersection(Line a, Line b){
	Point tmp = a.p - b.p;
	db t = (tmp ^ b.v)/(a.v ^ b.v);
//	cout << "fsfsd " << a.arg << " " << b.arg << " " << t << (a.v ^ b.v) << " " << a.v.x << " " << a.v.x << " " << b.v.x << " " << b.v.y << endl;
	return a.p - t * a.v;
}
bool on_right(Line a,Line b,Line c){
	Point p = line_intersection(b,c);
	return ((p-a.p) ^ a.v) > 0;
}
void half_plane_intersection(){
	int L=0,R=0;
	for(int i=1;i<=n;i++){
		if(i>1 && fabs(l[i].arg - l[i-1].arg) < EPS)continue;
		while(R-L>=2 && on_right(l[i], Q[R-1], Q[R-2])) R--;
		while(R-L>=2 && on_right(l[i], Q[L], Q[L+1])) L++;
		Q[R++] = l[i];
	}
	while(R-L>=2 && on_right(Q[L], Q[R-1], Q[R-2])) R--;
	while(R-L>=2 && on_right(Q[R-1], Q[L], Q[L+1])) L++;
//	cout << L << " " << R << endl << endl;
//	for(int i=L;i<R;i++){
//		Point s = Q[i].p;
//		Point t = s + Q[i].v;
//		cout << "line i=" << i << " " << s.x << " " << s.y << " " << t.x << " " << t.y << endl;
//	}
	int tot = 0;
	db ans = 0;
	for(int i=L+1;i<R;i++){
		NQ[++tot] = line_intersection(Q[i], Q[i-1]);
//		cout << NQ[tot].x << " " << NQ[tot].y << endl;
	}
	NQ[++tot] = line_intersection(Q[R-1], Q[L]);
	for(int i=3;i<=tot;i++){
		ans += ((NQ[i] - NQ[1]) ^ (NQ[i-1] - NQ[1])) / 2;
	}
	printf("%.3lf\n", fabs(ans));
}
void solve(){
	sort(l+1,l+1+n);
	half_plane_intersection();
}
int main(){
	scanf("%d",&T);
	while(T--){
		//solve();
		int tmp;
		scanf("%d",&tmp);
		for(int i=1;i<=tmp;i++){
			db x,y;
			scanf("%lf%lf",&x,&y);
			data[n+i] = Point(x,y);
		}
		for(int i=2;i<=tmp;i++){
			l[n+i] = Line(data[n+i-1], data[n+i] - data[n+i-1]);
		}
		l[n+1] = Line(data[n+tmp], data[n+1] - data[n+tmp]);
		n += tmp;
	}
	solve();
	return 0;
}
