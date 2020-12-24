#include<bits/stdc++.h>
using namespace std;
struct Point{
    double x, y;
    int id;
	Point operator - (Point b){
		return {this->x - b.x, this->y - b.y};
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
struct Segment{
    Point p[2];
    double m, n;
    Segment(){}
    Segment(Point x1, Point x2){
        p[0] = x1;
        p[1] = x2;
        m = (x1.x - x2.x) / (x1.y - x2.y);
        n = (x1.y * x2.x - x2.y * x1.x) / (x1.y - x2.y);
    }
    double eval(double y)const{
        return m * y + n;
    }
    
	bool operator == (const Segment y)const{
		return this->p[0] == y.p[0] && this->p[1] == y.p[1];
	}
};
int CurY;
struct Rect{
    Segment l,r;
    int helper;
    bool operator < (const Rect &y)const{
        return this->r.eval(CurY) < y.r.eval(CurY);
    }
    Rect(){}
    Rect(Segment x, Segment y,int he){
		l = x;
		r = y;
		helper = he;
	}
};

enum TYPE{START, END, REGULAR, MERGE, SPLIT};
Segment previousSegment(vector<Point> &data, int id){
	return  Segment(data[id], data[(id-1+data.size()) % data.size()]);
}

Segment nextSegment(vector<Point> &data, int id){
	return Segment(data[(id+1)%data.size()], data[id]);
}

Vector previousVector(vector<Point> &data, int id){
	return data[id] - data[(id-1+data.size()) % data.size()];
}

Vector nextVector(vector<Point> &data, int id){
	return data[(id + 1) % data.size()] - data[id];
}

Point currentPoint(vector<Point> &data, int id){
	return data[id];
}

Point previousPoint(vector<Point> &data, int id){
	return data[(id - 1 + data.size()) % data.size()];
}

Point nextPoint(vector<Point> &data, int id){
	return data[(id + 1) % data.size()];
}
int getType(vector<Point> &data, int id){
	Vector pr = previousVector(data, id);
	Vector nx = nextVector(data, id);
	Point curP = currentPoint(data, id);
	Point prP = previousPoint(data, id);
	Point nxP = nextPoint(data, id);
	if((pr ^ nx) < 0){
		if(curP.y < prP.y && curP.y < nxP.y){return MERGE;}
		else if(curP.y > prP.y && curP.y > nxP.y){return SPLIT;}
		else {return REGULAR;}
	}else{
		if(curP.y < prP.y && curP.y < nxP.y){return END;}
		else if(curP.y > prP.y && curP.y > nxP.y){return START;}
		else {return REGULAR;}
	}
} 
set<Rect>::iterator findIterator(set<Rect> &tree, vector<Point> &data, int id){
//	cout << "find " << id << endl;
//	for(auto x : tree){
//		cout << x.l.p[0].id << " " << x.l.p[1].id << endl;
//        cout << x.r.p[0].id << " " << x.r.p[1].id << " " << x.r.m << " " << x.r.n << endl;
//        cout << x.l.eval(CurY) << " " << x.r.eval(CurY) << endl;
//	}
//	cout << "end show\n";
	Rect tmp;
	tmp.r.n = data[id].x - 1;
	tmp.r.m = 0;
	auto it =  tree.lower_bound(tmp);
//	cout << (it != tree.end()) << endl;
	while(it != tree.end() && (data[id].x > it->r.eval(CurY)) &&((*it).l.p[0] != data[id] && (*it).l.p[1] != data[id]) && ((*it).r.p[0] != data[id] && (*it).r.p[1] != data[id])){
		it ++;
	}
    assert(it != tree.end());
	return it;
}
void handleStart(set<Rect> &tree, vector<Point> &data, int id){
	if(id == 0)
		tree.insert(Rect(previousSegment(data, id), nextSegment(data, id), id));
	else
		tree.insert(Rect(nextSegment(data, id), previousSegment(data, id), id));
}

void handleEnd(set<Rect> &tree, vector<Point> &data, int id){
	auto it = findIterator(tree, data, id);
	assert(it != tree.end());
	tree.erase(it);
}

void handleMerge(set<Rect> &tree, vector<Point> &data, int id){
	auto it = findIterator(tree, data, id);
	auto v = (*it);
	it = tree.erase(it);
	auto v2 = (*it);
	tree.erase(it);
	v.r = v2.r;
	cout << id << " " << v.helper << endl;
	v.helper = id;
	tree.insert(v);
}

void handleSplit(set<Rect> &tree, vector<Point> &data, int id){
	auto it = findIterator(tree, data, id);
	Segment prS = previousSegment(data, id);
	Segment nxS = nextSegment(data ,id);
	
	Rect v = (*it);
	tree.erase(it);
	Rect v2 = v;
	cout << id << " " << v.helper << endl;
	v.r = prS;
	v.helper = id;
	
	v2.l = nxS;
	v2.helper = id;
	
	tree.insert(v);
	tree.insert(v2);
}

void handleRegular(set<Rect> &tree, vector<Point> &data, int id){
	auto it = findIterator(tree, data, id);
	Rect v = (*it);
	tree.erase(it);
    Segment nxS = nextSegment(data, id);
	Segment prS = previousSegment(data, id);
	if(v.l == nxS || v.l == prS){
		v.l = (v.l == nxS) ? prS : nxS;
	}else{
		v.r = (v.r == nxS) ? prS : nxS;
	}
	cout << id << " " << v.helper << endl;
//   printf("link %d\n", id);
	
	v.helper = id;
	tree.insert(v);
}


vector<vector<Point>> monopo(vector<Point> &data){
    vector<vector<int>> e(data.size());

	vector<Point> event = data;
    sort(event.begin(), event.end(), [](auto &a, auto &b)->bool{
        if(a.y != b.y)return a.y > b.y;
        return a.x < b.x;
    });

    set<Rect> tree;
	CurY = event[0].y;
	handleStart(tree, data, event[0].id);
    
	for(int i=1;i<(int)event.size();i++){
        
		auto &cur = event[i];
		CurY = cur.y;
		int type = getType(data, cur.id);
		if(type == START){handleStart(tree, data, cur.id);}
		else if(type == END){handleEnd(tree, data, cur.id);}
		else if(type == MERGE){handleMerge(tree, data, cur.id);}
		else if(type == SPLIT){handleSplit(tree, data, cur.id);}
		else if(type == REGULAR){handleRegular(tree, data, cur.id);}
		
	}
    return {};
}
int main(){
	freopen("data.in", "r", stdin);
	freopen("rectOut.out", "w", stdout);
    int n;
    scanf("%d",&n);
    vector<Point> data;
    for(int i=1;i<=n;i++){
        double t1, t2;
        scanf("%lf %lf", &t1, &t2);
        Point t = {t1, t2, i-1};
        data.push_back(t);
    }
    auto out = monopo(data);
    return 0;
}

/*
6
1 4
3 3
2 1
6 2
4 5
5 6
1 4

7
0 0
1 1
2 0.5
3.5 0
4 3
3 2
-1 5
0 0

*/


