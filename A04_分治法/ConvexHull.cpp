#include<cstdio>
#include<vector>
#include<algorithm>
#include<cmath>
#include<iostream>
#include<stack>
struct Point{
	double x,y;
	Point(){x = y = 0;}
	Point(double a,double b){x = a;y = b;}
};
typedef Point Vector;
Vector operator - (Point a,Point b){
	return Vector(a.x-b.x,a.y-b.y);
}
double operator ^ (Vector a,Vector b){
	return a.x*b.y - a.y*b.x;
}
double len(Vector a){
	return sqrt(a.x*a.x+a.y*a.y);
}
bool operator < (Vector a,Vector b){
	if(a.x == b.x)
		return a.y < b.y;
	return a.x < b.x;
}
const int MAXN = 10000;
int n;
Point p[MAXN];
bool is_tangent(std::vector<Point> &left_part, std::vector<Point> &right_part, int left_pos, int right_pos,int flag){
	Vector line = right_part[right_pos] - left_part[left_pos];
	if(left_pos > 0){
		Vector cur = left_part[left_pos - 1] - left_part[left_pos];
		if((line ^ cur) * flag < 0)
			return false;
	}
	if(left_pos < (int)left_part.size() - 1){
		Vector cur = left_part[left_pos + 1] - left_part[left_pos];
		if((line ^ cur) * flag < 0)
			return false;
	}
	return true;
}
std::vector<Point> ConvexHull(int l,int r){
	//border case
	if(r-l+1<=5){
		std::stack<Point> s;
		s.push(p[l]);
		for(int i=1;i<=r-l;i++){
			while(s.size()>1){
				Point pre = s.top();
				s.pop();
				Point root = s.top();
				Vector current = p[l+i] - root;
				Vector init = pre - root;
				double xor_value = current ^ init;
				if(xor_value > 0 || (xor_value == 0 && len(current)>=len(init))){;}
				else{
					s.push(pre);
					break;
				}
			}
			s.push(p[l+i]);
		}
		std::vector<Point> v;
		while(s.size()>0){
			v.push_back(s.top());
			s.pop();
		}
		reverse(v.begin(),v.end());
		return v;
	}
	int mid=(l+r)>>1;
	//divide
	std::vector<Point> left_part = ConvexHull(l,mid);
	std::vector<Point> right_part = ConvexHull(mid+1,r);
	
	//merge
	int left_pos = (int)left_part.size() - 1;
	int right_pos = 0;
	bool change_left = (!is_tangent(left_part, right_part, left_pos, right_pos, 1));
	bool change_right = (!is_tangent(right_part, left_part, right_pos, left_pos, -1));
	while(change_left || change_right){
		if(change_left && left_pos > 0)
			left_pos --;
		else if(change_right && right_pos < (int)right_part.size()-1)
			right_pos ++;
		change_left = (!is_tangent(left_part, right_part, left_pos, right_pos, 1));
		change_right = (!is_tangent(right_part, left_part, right_pos, left_pos, -1));		
	}
	std::vector<Point> v;
	for(int i=0;i<=left_pos;i++)
		v.push_back(left_part[i]);
	for(int i=right_pos;i<(int)right_part.size();i++)
		v.push_back(right_part[i]);
	return v;
}	
int main(){
	std::cin >> n;
	for(int i=1;i<=n;i++){
		double a,b;
		std::cin >> a >> b;
		p[i] = Point(a,b);
	}
	std::sort(p+1,p+1+n);
	std::vector<Point> p1 = ConvexHull(1,n);
	std::cout << "lower hull"<< std::endl;
	for(int i=0;i<(int)p1.size();i++){
		std::cout << p1[i].x << " " << p1[i].y << std::endl;
	}
	
	for(int i=1;i<=n;i++){
		p[i].y = -p[i].y;
	}
	std::sort(p+1,p+1+n);
	std::vector<Point> p2 = ConvexHull(1,n);
	std::cout << "upper hull" << std::endl;
	for(int i=0;i<(int)p2.size();i++){
		std::cout << p2[i].x << " " << -p2[i].y << std::endl;
	}	
	return 0;
}
