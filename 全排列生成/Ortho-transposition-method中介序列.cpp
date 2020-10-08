#include<bits/stdc++.h>
using namespace std;
const int MAXN = 50000;
const int LEFT = 0;
const int RIGHT = 1;

void getOrderList(int *in, int n, int *out){
    int *pos = new int[n+1];
    for(int i=0;i<=n;i++)out[i]=0;
    for(int i=1;i<=n;i++)pos[in[i]]=i;
    for(int i=2;i<=n;i++){
        int toward=0;
        if(i%2){toward=(out[i-1])%2;}
        else{toward=(out[i-1]+out[i-2])%2;}
        toward = toward ? RIGHT : LEFT;
        if(toward==RIGHT)for(int j=1;j<=pos[i];j++)out[i]+=(in[j]<i);
        else for(int j=pos[i];j<=n;j++)out[i]+=(in[j]<i);
    }
    delete[] pos;
}

void getRawList(int *in, int n, int *out){
    for(int i=1;i<=n;i++)out[i]=0;
    in[0] = in[1] = 0;
    for(int i=n;i>=2;i--){
        int toward = 0;
        if(i%2){toward=(in[i-1])%2;}
        else{toward=(in[i-1]+in[i-2])%2;}
        toward = toward ? RIGHT : LEFT;
        int tot = 0;
        if(toward == RIGHT){
            for(int j=1;j<=n;j++){
                if(out[j]==0)tot++;
                if(tot == in[i]+1){
                    out[j] = i;
                    break;
                }
            }
        }else{            
            for(int j=n;j>=1;j--){
                // cout << i << " " << j << endl;
                if(out[j]==0)tot++;
                if(tot == in[i]+1){
                    out[j] = i;
                    break;
                }
            }
        }
    }
    for(int i=1;i<=n;i++)if(out[i]==0)out[i]=1;
}

int data[MAXN], n, injection[MAXN], pos[MAXN], ans[MAXN];
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",data+i);
    getOrderList(data, n, injection);
    for(int i=2;i<=n;i++){
        cout << injection[i] << " ";
    }
    cout << endl;
    // system("pause");
    getRawList(injection, n, ans);
    for(int i=1;i<=n;i++){
        cout << ans[i] << " ";
    }
    cout << endl;
    // system("pause");
    return 0;
}