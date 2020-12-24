#include<bits/stdc++.h>
using namespace std;
const int MAXN = 300000;
#define RED 0
#define BLACK 1
int ch[MAXN][2], fa[MAXN], color[MAXN], key[MAXN], sz[MAXN], tot, root;
int createNode(int v){
	++tot; key[tot]=v; sz[tot] = 1;
	return tot;
}

void update(int x){
	sz[x] = 1 + sz[ch[x][0]] + sz[ch[x][1]];
}

void rotate(int x){
	int y=fa[x], z=fa[y];
	if(y == root) root = x;
	ch[z][ch[z][1] == y] = x;
	int t = (ch[y][1] == x);
	fa[x] = z; fa[y] = x;
	fa[ch[x][t^1]] = y;
	ch[y][t] = ch[x][t^1];
	ch[x][t^1] = y;
	update(y); update(x);
}

void insertFixup(int x){
	int y=fa[x],z=fa[y];
	while(color[y]==RED &&root!=y){
		int w=ch[z][ch[z][0]==y];
		if(color[w]==RED){
			color[y] = color[w] = BLACK;
			color[z] = RED;
			x = z;
		}else if((ch[z][1]==y) ^ (ch[y][1]==x)){
			rotate(x);
			swap(x,y);
		}else{
			swap(color[y],color[z]);
			rotate(y);
		}
		y = fa[x];z=fa[y];
	}
	color[root] = BLACK;
}

void insert(int x,int v){
	int y=0;
	while(x!=0){
		y=x;
		if(v>key[x])x=ch[x][1];
		else x=ch[x][0];
	}
	v=createNode(v);
	fa[v]=y;
	if(y==0){root = v;}
	else if(key[v]>key[y]){ch[y][1]=v; fa[v]=y;}
	else{ch[y][0]=v; fa[v]=y;}
	while(y!=0){update(y);y=fa[y];}
	insertFixup(v);
}

void transplant(int x,int y){
	int z=fa[x];
	ch[z][ch[z][1]==x]=y;
	if(x==root)root=y;
	fa[y]=fa[x];
}

int minimum(int x){
	int y=0;
	while(x!=0){y=x;x=ch[x][0];}
	return y;
}
int cnt=0,n;
void dfs(int x){
	if(x==0)return;
	dfs(ch[x][0]);
	cnt++;
	if(cnt != n){printf("%d ",key[x]);}
	else{printf("%d",key[x]);}
//	cout << x <<" "<< key[x] <<" "<< ch[x][0] <<" "<< ch[x][1] << endl; 
	dfs(ch[x][1]);
}
void removeFixup(int x){
	int y;
	while(color[x]==BLACK && x!=root){
		y=fa[x];
		int t = (ch[y][1]==x);
		int w=ch[y][t^1];
		if(color[w]==RED){
			swap(color[w],color[y]);
			rotate(w);
		}else if(color[w]==BLACK && color[ch[w][t]]==BLACK && color[ch[w][t^1]]==BLACK){
			color[w]=RED;
			x=y;
		}else if(color[w]==BLACK && color[ch[w][t]]==RED && color[ch[w][t^1]]==BLACK){
			swap(color[w], color[ch[w][t]]);
			rotate(ch[w][t]);
		}else{
			swap(color[y],color[w]);
			color[ch[w][t^1]]=BLACK;
			rotate(w);
			x = root;
		}
	}
	color[x] = BLACK;
}

void remove(int x,int v){
	while(x!=0){
		if(key[x]==v)break;
		else if(v>key[x])x=ch[x][1];
		else x=ch[x][0];
	}	
	if(x==0)return;
	int ocolor = color[x];
	if(ch[x][0]==0 && ch[x][1]==0){
		if(ocolor==BLACK)removeFixup(x);
		transplant(x,0);
//		while(y!=0){update(y);y=fa[y];}
	}else if(ch[x][1]==0 || ch[x][0]==0){
		int t=(ch[x][0]==0);
		transplant(x, ch[x][t]);
		if(ocolor==BLACK)removeFixup(ch[x][t]);
	}else{
		int z=minimum(ch[x][1]), e=ch[z][1];
		ocolor = color[z]; color[z]=color[x];
		bool flag = (e==0);
		if(flag){e=++tot; color[e]=BLACK; ch[z][1]=e; fa[e]=z;}
		if(z==ch[x][1]){
			transplant(x, z); ch[z][0]=ch[x][0]; fa[ch[z][0]] = z;
		}else{
			transplant(z, e); transplant(x, z);
			ch[z][0]=ch[x][0]; ch[z][1]=ch[x][1];
			fa[ch[z][0]] = fa[ch[z][1]] = z;
		}
		if(ocolor==BLACK) removeFixup(e);
		if(flag){transplant(e,0); tot--;}
	}
	
}

int main(){
	color[0] = BLACK;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int x;
		scanf("%d",&x);
		insert(root, x);
	}
//	dfs(root);
	for(int i=1;i<n;i++){
		int v = minimum(root);
		printf("%d ",key[v]);
		remove(root, key[v]);
	}
	printf("%d",key[minimum(root)]);
	return 0;
}
