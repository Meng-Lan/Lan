#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<sstream>
#include<fstream>
#include<vector>
#include<list>
#include<deque>
#include<stack>
#include<queue>
#include<map>
#include<set>
#include<cmath>
#include<utility>
#include<numeric>
#include<iterator>
#include<algorithm>
#include<functional>
#include<ctime>
#include<cassert>
using namespace std;
const int maxn=200+5;
int n;
char buf[maxn][maxn];
void dfs(int r,int c){
    printf("%c(",buf[r][c]);
    if(r+1<n && buf[r+1][c]=='|'){
        int i=c;
        while(i-1>=0 && buf[r+2][i-1]=='-') i--;
        while(buf[r+2][i]=='-'&&buf[r+3][i]!='\0'&&buf[r+3][i]!='#'){
            if(!isspace(buf[r+3][i]))dfs(r+3,i);
            i++;
        }
    }
    printf(")");
}
void solve(){
    n=0;
    for(;;){
        fgets(buf[n],maxn,stdin);
        if(buf[n][0]=='#') break;
        else n++;
    }
    printf("(");
    if(n){
        for(int i=0;i<strlen(buf[0]);i++){
            if(buf[0][i]!=' ') { dfs(0,i);break;}
        }
    }
    printf(")\n");
}
int main(){
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	freopen("out","w",stdout);
#endif // MengLan
    int t;
    fgets(buf[0],maxn,stdin);
    sscanf(buf[0],"%d",&t);
    while(t--) solve();
#ifdef MengLan
	//printf("Time: %d\n",clock()-Beginning);
    //system("pause");
#endif // MengLan
    return 0;
}
