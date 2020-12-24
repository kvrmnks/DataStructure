#include<bits/stdc++.h>
using namespace std;
struct Point{
    double x, y;
    int id;
	Point operator - (Point b){
		return {this->x - b.x, this->y - b.y, this->id};
	}
	double operator ^ (Point b){
		return this->x * b.y - this->y * b.x;
	}
	bool operator == (const Point b)const {
		return this->id == b.id;
	}
	bool operator != (const Point b)const {
		return this->id != b.id;
	}	
};
typedef Point Vector;
const char *RAW = "./data.in";
const char *RECT = "./rectOut.out";
const char *SPLIT  = "./split.out";
map<int, set<int>> G, CG, RG;
map<pair<int, int>, bool> vis;
map<int, Point> P;
int n,m;

void subRoutine(int x, int y){
	cout << x << " ";
	int bg = x;
	while(y != bg){
		auto curPoint = P[y];
		cout << y << " ";
		vector<Point> pointList;
		for(auto t : CG[y]){
			pointList.push_back(P[t]);			
		}
		
		sort(pointList.begin(), pointList.end(), [&](Point &a, Point &b)->bool{
			Point x = a - curPoint;
			Point y = b - curPoint;
			
			double arg1 = atan2(x.y, x.x);
			double arg2 = atan2(y.y, y.x);
			return arg1 < arg2;
		});
		int loc = -1;
		for(int i=0;i<(int)pointList.size();i++){
			if(pointList[i].id == x){loc = i; break;}
			
		}
		x = y;
		y = pointList[(loc - 1 + pointList.size()) % pointList.size()].id;
	}	
	cout << endl;
}
void split(){
	for(auto x : G){
		for(auto y : x.second){
			int a = x.first, b = y;
			if(a > b)swap(a, b);
			if(vis[make_pair(a, b)] == false){
				vis[make_pair(a, b)] = true;
				subRoutine(x.first, y);
			}
		}
	}
	for(auto x : G){
		for(auto y : x.second){
			int a = x.first;
			int b = y;
			if(vis[make_pair(a, b)]  == false){
				vis[make_pair(a, b)] = true;
				subRoutine(a, b);
			}
		}
	}
}
void readData(){
	ifstream f1(RAW, ios::in), f2(RECT, ios::in);
	f1 >> n;
	for(int i=0;i<n;i++){
		double x,y;
		f1 >> x >> y;
		P[i] = {x, y, i};
		int nx = (i+1)%n;
//		G[nx].insert(i);
		G[i].insert(nx);
		CG[i].insert(nx);
		CG[nx].insert(i);
	}
//	CG = G;
	while(!f2.eof()){
		int a,b;
		f2 >> a >> b;
		CG[a].insert(b);
		CG[b].insert(a);
		RG[a].insert(b);
		RG[b].insert(a);
	}
	f1.close(); f2.close();
}

int main(){
	freopen(SPLIT, "w", stdout);
	readData();
	split();
	return 0;
}
