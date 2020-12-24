#include<bits/stdc++.h>
using namespace std;
const char *RAW = "data.in";
const char *RECT = "rectOut.out";
const char *SPLIT  = "split.out";
const char *TRIANGULAR = "triangular.out";

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

vector<Point> data;
int n;
vector<vector<int>> monotone;
int cnt;
int checkType(int x, int y, int mod){
	// y for x
	if((x + 1)%mod == y)return 1;
	if(((x - 1 + mod) % mod) == y) return -1;
	return 0;
}
void solveSingleMonotone(vector<int> &v){
	vector<pair<int, int>> event;
	for(int i=0;i<(int)v.size();i++){
		event.push_back(make_pair(v[i], i));		
	}
	sort(event.begin(), event.end(), [&](pair<int, int> &x, pair<int, int> &y)->bool{
		return data[x.first].y > data[y.first].y;
	});
	
	stack<pair<int, int>> sta;
//	cout << event.size() << endl;
//	for(auto curPoint : event){
//		cout << curPoint.first << " " << curPoint.second << endl;
//	}
//	cout << "end show\n";
	int facet = checkType(event[0].second, event[1].second, (int)v.size());
	
	for(auto curPoint : event){
//		cout << "hereh\n";
		if(sta.empty()){
			sta.push(curPoint);
			continue;
		}
//		cout << "here";
		auto topPoint = sta.top();
		bool flag = false;
		if(((topPoint.second + 1) % v.size()) == curPoint.second || ((topPoint.second - 1 + v.size()) % v.size()) == curPoint.second)
			flag = true;
		if(flag){
			// same 
			while(sta.size() > 1){
				topPoint = sta.top();	
				sta.pop();
				auto subTopPoint = sta.top();
//				int type = checkType(subTopPoint);
				Vector previous = data[topPoint.first] - data[subTopPoint.first];
				Vector nx = data[curPoint.first] - data[topPoint.first];
				if((previous ^ nx)*facet < 0){
					sta.push(topPoint);
					break;
				}else{
					cout << curPoint.first << " " << topPoint.first << endl;
					cout << curPoint.first << " " << subTopPoint.first << endl;
					continue;
				}
			}
		}else{
			// opposite
			facet *= -1;
			auto tmp = topPoint;
			while(!sta.empty()){
				topPoint = sta.top();
				sta.pop();
				cout << curPoint.first << " " << topPoint.first << endl;
			}
			sta.push(tmp);
		}
		sta.push(curPoint);
	}
}

void readData(){
	ifstream raw(RAW, ios::in);
	raw >> n;
	for(int i=1;i<=n;i++){
		Point tmp;
		raw >> tmp.x >> tmp.y;
		tmp.id = i-1;
		data.push_back(tmp);
	}
//	cout << n << endl;
	ifstream split(SPLIT, ios::in);
	while(!split.eof()){
		string s;
		getline(split, s);
		if(s == "")continue;
		stringstream ss(s);
		monotone.push_back({});
		int tmp, curTem = 0;
		while(ss >> tmp){
			monotone[cnt].push_back(tmp);
			curTem ++;
		}
//		cout << curTem << endl;
		if(curTem)
			cnt ++;
	}
	split.close();
	raw.close();
}

int main(){
	freopen(TRIANGULAR, "w", stdout);
	readData();
	for(auto &x : monotone){
		solveSingleMonotone(x);
//		cout << "finish\n";
	}
	return 0;
}
