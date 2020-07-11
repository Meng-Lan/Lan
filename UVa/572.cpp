#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
const int maxn= 100+5;
int m,n;
char c[maxn][maxn];
int  a[maxn][maxn];
void dfs(int r,int y,int id){
    if(r<0||r>=m||y<0||y>=n) return;
    if(a[r][y]!=0||c[r][y]!='@') return ;
    a[r][y]=id;
    for(int x=-1;x<=1;x++){
        for(int dy=-1;dy<=1;dy++){
            if(x!=0||dy!=0) dfs( r+x,y+dy,id);
        }
    }
}
int main(){
    while(scanf("%d%d",&m,&n)==2&& m && n){
    for(int i=0;i<m;i++) scanf("%s",c[i]);
    memset(a,0,sizeof(a));
    int cnt=0;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(c[i][j]=='@'&&a[i][j]==0) dfs(i,j,++cnt);
        }
    }
    cout<<cnt<<endl;
    }        
    return 0;
}