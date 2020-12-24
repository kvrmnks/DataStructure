#include<bits/stdc++.h>
using namespace std;
const int MAXN = 20000;
typedef double db;
const db EPS=1e-8;
int n;
int dcmp(db x){
	if(fabs(x)<EPS)
		return 0;
	return x>0?1:-1;
}
struct Point{db x,y;Point(){}Point(db a,db b){x=a;y=b;}};
typedef Point Vector;
Vector operator-(Point a,Point b){return Vector(a.x-b.x,a.y-b.y);}
Vector operator+(Vector a,Vector b){return Vector(a.x+b.x,a.y+b.y);}
db operator^(Vector a,Vector b){return a.x*b.y-a.y*b.x;}
Vector operator*(db x,Vector a){return Vector(a.x*x,a.y*x);}
struct Line{Point p,v;db ang;int id;Line(){}Line(Point a,Vector b){id=(int)1e9;p=a;v=b;ang=atan2(v.y,v.x);}};
void display(Line a){
	cout << a.p.x << " " << a.p.y << " " << a.v.x << " " << a.v.y << " " << a.id << endl;
}
bool operator<(Line a,Line b){
	if(!dcmp(a.ang-b.ang)){
		return (a.v^(b.p-a.p))<0;
	}
	return a.ang < b.ang;
}
Point line_intersection(Line a,Line b){
	Vector tmp=a.p-b.p;
	db t=(tmp^b.v)/(a.v^b.v);
	return a.p-t*a.v;
}
bool on_right(Line a,Line b,Line c){
	Point p=line_intersection(b,c);
	return (a.v^(p-a.p))<0;
}

Line l[MAXN],Q[MAXN],out[MAXN];
int tot;
void half_plane_intersection(){
	int L=0,R=0;
	for(int i=1;i<=n;i++){
		if(i>1 && dcmp(l[i].ang-l[i-1].ang)==0)continue;
		
		while(R-L>=2 && on_right(l[i],Q[R-1],Q[R-2]))R--;
		while(R-L>=2 && on_right(l[i],Q[L],Q[L+1]))L++;
		Q[R++]=l[i];
//		puts("********************");
//		for(int j=L;j<R;j++)
//			display(Q[j]);
	}
	while(R-L>=2 && on_right(Q[R-1],Q[L],Q[L+1]))L++;
	while(R-L>=2 && on_right(Q[L],Q[R-1],Q[R-2]))R--;
	for(int i=L;i<R;i++){
		out[++tot] = Q[i];
	}
//	cout << L << " " << R << endl; 
}
bool cmp(Line a,Line b){return a.id < b.id;}
int main(){
	static int k[MAXN],v[MAXN];
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",k+i);
	for(int i=1;i<=n;i++)scanf("%d",v+i);
	for(int i=1;i<=n;i++){
		l[i] = Line(Point(0,k[i]),Vector(1,v[i]));
		l[i].id=i;
	}
	l[++n] = Line(Point(0, 2e9), Vector(-1, 0));
	l[++n] = Line(Point(0, -2e9), Vector(1, 0));
	l[++n] = Line(Point(2e9, 2e9), Vector(0, 1));
	l[++n] = Line(Point(0, 0), Vector(0, -1));
	sort(l+1,l+1+n);
	half_plane_intersection();
	sort(out+1,out+1+tot,cmp);
	n = 0;
	for(int i=1;i<=tot;i++)
		n += (out[i].id < 998244353);
	printf("%d\n",n);
	for(int i=1;i<=tot;i++){
		if(out[i].id > 998244353) break;
		printf("%d ",out[i].id);
	}
	return 0;
}
