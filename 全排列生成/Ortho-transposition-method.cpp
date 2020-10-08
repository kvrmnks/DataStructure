#include<bits/stdc++.h>
using namespace std;
const int LEFT_ARROR = 0;
const int RIGHT_ARROR = 1;
struct Point{
	int number, arror;
};
int main(){
	int n;
	cin>>n;
	Point *data = new Point[n+1];
	for(int i=1;i<=n;i++){
		data[i] = (Point){i, LEFT_ARROR};
	}
	int cnt = 0;
	while(true){
		int pos_2 =1;
		for(int i=1;i<=n;i++){
			if(data[i].number == 2){
				pos_2 = i;
				break;
			}
		}
		assert(data[pos_2].arror != RIGHT_ARROR);
		cnt ++;
		cout << "******************\n";
		for(int i=1;i<=n;i++){
			cout << data[i].arror << " ";
		}
		cout << endl;
		for(int i=1;i<=n;i++){
			cout << data[i].number << " ";
		}
		cout << endl;
		int movable_pos = -1;
		for(int i=1;i<=n;i++){
			int point_pos = i + (data[i].arror == LEFT_ARROR ? -1 : 1);
			if(point_pos < 1 || point_pos > n) continue;
			if(data[i].number > data[point_pos].number){
				if(movable_pos == -1 || data[movable_pos].number < data[i].number){
					movable_pos = i;
				}
			}
		}
		if(movable_pos == -1)break;
		int point_pos = movable_pos + (data[movable_pos].arror == LEFT_ARROR ? -1 : 1);
		for(int i=1;i<=n;i++){
			if(data[i].number > data[movable_pos].number){
				data[i].arror ^= 1;
			}
		}
		swap(data[movable_pos], data[point_pos]);
		
	}
	cout << "there are totally " << cnt << " anss\n";
	system("pause");
	return 0;
}