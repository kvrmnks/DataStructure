#include <windows.h>
#include <iostream>
#include <vector>
#include <list>
#include <windowsx.h>
#include <algorithm>
#include <set>
#include <cassert>

using namespace std;
const int MY_TIMER = 1024;

vector<int> verX,verY;
struct Point{
    int x,y;
    bool operator < (const Point &yy)const{
        if(x == yy.x)return y < yy.y;
        return x < yy.x;
    }
    bool operator == (const Point &yy)const{
        return x == yy.x && y == yy.y;
    }
};
struct Line{
    Point x,y;
    Line(Point a,Point b){
        x = a;
        y = b;
    }
};
vector<Line> lines;

struct Vertex{
    Point p;
    vector<Line> beginLines, endLines;
};
int curX, curY;
vector<Vertex> scanVector;

struct MoveLine{
    Point x,y;
    double curX, curY;
    MoveLine(Line x){
        this->x = x.x;
        this->y = x.y;
    }
    MoveLine(Point a,Point b, int _curX, int _curY){
        x = a;
        y = b;
        curX = _curX;
        curY = _curY;
    }
    bool operator == (const Line b)const{
        return x.x == b.x.x && x.y == b.x.y && y.x == b.y.x && y.y == b.y.y;
    }
    bool operator == (const MoveLine &yy)const{
        return x == yy.x && y == yy.y;
    }
    bool operator < (const MoveLine &yy)const{
        return (this->curX) < (yy.curX);
    }

};
multiset<MoveLine> scanList;

void buildScanLine(HWND hwnd){
    if(verX.empty()){
        KillTimer(hwnd, MY_TIMER);
        return;
    }
    for(int i=0;i<(int)verX.size();i++){
        Vertex tmp;
        tmp.p = {verX[i], verY[i]};
        tmp.beginLines.clear();
        tmp.endLines.clear();
        scanVector.push_back(tmp);
    }
    for(int i=0;i<(int)verX.size()-1;i++){
        Point a = {verX[i], verY[i]};
        Point b = {verX[i+1], verY[i+1]};
        if(a.y > b.y){
            scanVector[i+1].beginLines.emplace_back(b,a);
            scanVector[i].endLines.emplace_back(b,a);
        }else{
            scanVector[i].beginLines.emplace_back(a,b);
            scanVector[i+1].endLines.emplace_back(a,b);
        }
    }
    Point a = {verX[0], verY[0]};
    Point b = {verX[(int)verX.size()-1], verY[(int)verX.size()-1]};
    if(a.y > b.y){
        scanVector[(int)verX.size()-1].beginLines.emplace_back(b,a);
        scanVector[0].endLines.emplace_back(b,a);
    }else{
        scanVector[0].beginLines.emplace_back(a,b);
        scanVector[(int)verX.size()-1].endLines.emplace_back(a,b);
    }
    sort(scanVector.begin(), scanVector.end(), [](const Vertex& a, const Vertex& b)->int{
        return a.p.y < b.p.y;
    });
    for(auto x:scanVector[0].beginLines){
        scanList.insert(MoveLine(x.x, x.y, x.x.x, x.x.y));
    }
    curX = 1;
    curY = scanVector[0].p.y;

    for(auto &x : scanVector){
        cout << "new node\n";
        cout << x.p.x << " " << x.p.y << endl;
        cout << "beginLines" << endl;
        for(auto &y : x.beginLines){
            cout << y.x.x << " " << y.x.y << " " << y.y.x << " " << y.y.y << endl;
        }
        cout << "endLines" << endl;
        for(auto &y : x.endLines){
            cout << y.x.x << " " << y.x.y << " " << y.y.x << " " << y.y.y << endl;
        }
        cout << "end node\n";
    }
}
void CALLBACK fillOneStep(HWND hwnd, UINT message, UINT iTimerID, DWORD dwTime){

    if(curX >= scanVector.size()){ KillTimer(hwnd, MY_TIMER); cout << "killed\n";}
    curY += 1;

    //update
    multiset<MoveLine> newSet;
    for(auto &it : scanList){
        MoveLine tmp = it;
        tmp.curX += (double)(it.x.x - it.y.x)/(it.x.y - it.y.y);
        tmp.curY += 1;
        newSet.insert(tmp);
    }

    int cnt =0;
    for(auto it = scanList.begin(); it != scanList.end(); it++){
        cnt ++;
        auto pit = it;
        it++;
        lines.emplace_back((Point){(int)pit->curX,(int)pit->curY}, (Point){(int)it->curX, (int)it->curY});
    }

    //flush panel
    InvalidateRect(hwnd, nullptr, true);

    if(curX < scanVector.size() && scanVector[curX].p.y == curY){
        for(auto x : scanVector[curX].endLines){
            MoveLine tmp(x);
            tmp.curX = x.y.x - 1;
            tmp.curY = x.y.y;
            auto it = newSet.lower_bound(tmp);
            while(it!=newSet.end() && (!((*it) == (const MoveLine)tmp))){it++;}
            assert(it != newSet.end());
            newSet.erase(it);
        }

        if(!scanVector[curX].beginLines.empty()){
            for(auto y:scanVector[curX].beginLines) {
                newSet.insert(MoveLine(y.x, y.y, y.x.x, y.x.y));
            }
        }
        curX += 1;
    }
    if(curX >= scanVector.size()){ KillTimer(hwnd, MY_TIMER); cout << "killed\n";}
    scanList = newSet;
}

void DrawLines(PAINTSTRUCT &ps){
    if(lines.empty())return;
    for(auto & line : lines){
        MoveToEx(ps.hdc, line.x.x, line.x.y, nullptr);
        LineTo(ps.hdc, line.y.x, line.y.y);
    }
}

void DrawHull(PAINTSTRUCT &ps){
    if((int)verX.size() < 1)return ;
    MoveToEx(ps.hdc, verX[0], verY[0], nullptr);
    for(int i=1;i<(int)verX.size();i++){
        LineTo(ps.hdc, verX[i], verY[i]);
    }
    LineTo(ps.hdc, verX[0], verY[0]);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
//	HDC hdc;
    PAINTSTRUCT ps;
    switch (Message) {
        case WM_CREATE:{
            CreateWindow(TEXT("Button"), TEXT("flush"),
                         WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                         30, 30, 50, 40,
                         hwnd, (HMENU)1,
                         ((LPCREATESTRUCT)lParam)->hInstance, nullptr);
            CreateWindow(TEXT("Button"), TEXT("fill"),
                         WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                         30, 70, 50, 40,
                         hwnd, (HMENU)2,
                         ((LPCREATESTRUCT)lParam)->hInstance, nullptr);
            return 0;
        }
        case WM_DESTROY: {
            PostQuitMessage(0);
            break;
        }
        case WM_TIMER:{

            break;
        }
        case WM_PAINT:{
            BeginPaint(hwnd, &ps);
            SelectObject(ps.hdc, GetStockObject(GRAY_BRUSH));
            DrawHull(ps);
            DrawLines(ps);
            EndPaint(hwnd, &ps);
            break;
        }
        case WM_LBUTTONDOWN:{
            int xPos = GET_X_LPARAM(lParam);
            int yPos = GET_Y_LPARAM(lParam);
            verX.push_back(xPos);
            verY.push_back(yPos);
            InvalidateRect(hwnd, nullptr, true);
            break;
        }
        case WM_COMMAND:{
            switch(LOWORD(wParam)){
                case 1:{
                    verX = vector<int>();
                    verY = vector<int>();
                    lines = vector<Line>();
                    scanVector.clear();
                    scanList.clear();
                    InvalidateRect(hwnd, nullptr, true);
                    break;
                }
                case 2:{
                    buildScanLine(hwnd);
                    SetTimer(hwnd, MY_TIMER, 50, fillOneStep);
                    break;
                }
            }
        }
        case WM_MOUSEMOVE:{
            break;
        }
        default:
            return DefWindowProc(hwnd, Message, wParam, lParam);
    }return DefWindowProc(hwnd, Message, wParam, lParam);

}
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    memset(&wc,0,sizeof(wc));
    wc.cbSize		 = sizeof(WNDCLASSEX);
    wc.lpfnWndProc	 =WndProc; /* insert window procedure function here */
    wc.hInstance	 = hInstance;
    wc.hCursor		 = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszClassName = "WindowClass";
    wc.hIcon		 = LoadIcon(nullptr, IDI_APPLICATION); /* use "A" as icon name when you want to use the project icon */
    wc.hIconSm		 = LoadIcon(nullptr, IDI_APPLICATION); /* as above */

    if(!RegisterClassEx(&wc)) {
        MessageBox(nullptr, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","Scan Fill",WS_VISIBLE|WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,640,480,NULL,NULL,hInstance,NULL);
    if(hwnd == nullptr) {
        MessageBox(nullptr, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
        return 0;
    }

    while(GetMessage(&Msg, nullptr, 0, 0) > 0) {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}

