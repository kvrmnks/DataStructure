#include<iostream>
#include<windows.h>
#include<windowsx.h>
#include<algorithm>
#include<vector>
#include"Queue.h"
#include<cmath>
using namespace std;
struct Vector{
	int x,y;
	Vector(){}
	Vector(double x0,double y0){x=x0;y=y0;}
};
double operator ^ (Vector a, Vector b){
	return a.x*b.y - a.y*b.x;
}
Vector operator - (Vector a, Vector b){
	return Vector(a.x-b.x, a.y-b.y);
}
double norm2(Vector a){
	return sqrt(a.x*a.x + a.y*a.y);
}
bool cmp(Vector a, Vector b){
	if(a.x == b.x)
		return a.y < b.y;
	return a.x < b.x;
}

void giftWrapping(Queue<int> *q, vector<Vector> &v, int length){
	bool *is_choose = new bool[length+1];
	memset(is_choose, 0,(length+1)*sizeof(bool));
	q->clear();
	q->push(0);
	is_choose[0] = true;
	while(true){
		int cur = -1;
		for(int j=0;j<length;j++){
			if(!is_choose[j]){
				cur = j;
				break;
			}
		}
		if(cur == -1)break;
		for(int i=0;i<length;i++){
			int value = (v[i]-v[q->front()]) ^ (v[cur] - v[q->front()]);
			if(value>0 || (value==0 && norm2(v[i]-v[q->front()]) > norm2(v[cur] - v[q->front()]))){
				cur = i;
			}
		}
		if(is_choose[cur]){break;}
		q->push(cur);
		is_choose[cur] = true;
	}	
	delete is_choose;
}

Queue<int> *q;

vector<Vector> points;
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
//	HDC hdc;
	PAINTSTRUCT ps;
	switch(Message) {
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		case WM_PAINT: {
			BeginPaint(hwnd, &ps);
			SelectObject(ps.hdc, GetStockObject(GRAY_BRUSH));
			for(int i=0;i<(int)points.size();i++){
				Ellipse(ps.hdc, points[i].x-5, points[i].y-5, points[i].x+5, points[i].y+5);
			}
			if(points.size() >= 3){
				//q = new Queue<int>();
				sort(points.begin(), points.end(), cmp);
				giftWrapping(q, points, (int)points.size());
				vector<Vector> vec;
				while(q->size()){
					vec.push_back(Vector(points[q->front()].x, points[q->front()].y));
					q->pop();
				}
				MoveToEx(ps.hdc, vec[0].x, vec[0].y, 0);
				for(int i=1;i<(int)vec.size();i++){
					LineTo(ps.hdc, vec[i].x, vec[i].y);
				}
				LineTo(ps.hdc, vec[0].x, vec[0].y);
			}
			EndPaint(hwnd, &ps);
			break;
		}
		case WM_LBUTTONDOWN: {
			int xPos = GET_X_LPARAM(lParam); 
			int yPos = GET_Y_LPARAM(lParam);
			Vector a = Vector(xPos, yPos);
			points.push_back(a);
			//Invalidate();
			InvalidateRect(hwnd,NULL,true);
			break;					 
		}
		case WM_MOUSEMOVE: {
			break;
		}
		
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	q = new Queue<int>();
	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;

	memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 =WndProc; /* insert window procedure function here */
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszClassName = "WindowClass";
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION); /* use "A" as icon name when you want to use the project icon */
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION); /* as above */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","Convex Hull",WS_VISIBLE|WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,640,480,NULL,NULL,hInstance,NULL);
	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	while(GetMessage(&Msg, NULL, 0, 0) > 0) {
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}
