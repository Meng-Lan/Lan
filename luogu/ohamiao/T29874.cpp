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
using std::cin;
using std::cout;
using std::endl;
typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<int,int> P;
#define FOR(i,init,len) for(int i=(init);i<(len);++i)
#define For(i,init,len) for(int i=(init);i<=(len);++i)
#define fi first
#define se second
#define pb push_back
#define is insert
namespace IO {
	inline char getchar() {
		static const int BUFSIZE=5201314;
		static char buf[BUFSIZE],*begin,*end;
		if(begin==end) {
			begin=buf;
			end=buf+fread(buf,1,BUFSIZE,stdin);
			if(begin==end) return -1;
		}
		return *begin++;
	}
}
inline void read(int &in) {
	int c,symbol=1;
	while(isspace(c=IO::getchar()));
	if(c=='-') { in=0;symbol=-1; }
	else in=c-'0';
	while(isdigit(c=IO::getchar())) { in*=10;in+=c-'0'; }
	in*=symbol;
}
inline int read() { static int x;read(x);return x; }
ll gcd(ll a,ll b) { return b?gcd(b,a%b):a; }
ll lcm(ll a,ll b) { return a/gcd(a,b)*b; }
#define PA(name,init,len) cout<<#name"["<<(len-init)<<"]=";FOR(_,init,len) cout<<name[_]<<" \n"[_==(len-1)];
#define Pa(name,init,len) cout<<#name"["<<(len-init+1)<<"]=";For(_,init,len) cout<<name[_]<<" \n"[_==(len)];
#define PV(name) cout<<#name"="<<name<<'\n';

const int maxn=55;
int n,m;
int dist[maxn][maxn];
bool vis[maxn][maxn];
char s[maxn][maxn];

const int dx[]={0,1,0,-1};
const int dy[]={1,0,-1,0};

struct Node{
    int x,y,time;
    Node(int x=0,int y=0,int time=0):x(x),y(y),time(time){}
};

//主要检查坐标是否越界和是否来过
inline bool check(int x,int y){return x>=1&&x<=n&&y>=1&&y<=m&&!vis[x][y];}

//bfs求洪水在什么时候淹没(x,y)，那么我必须在洪水淹没之前抵达这里，否则我将不能抵达这里
void flood_bfs(){
    std::queue<Node> q;
    For(i,1,n) For(j,1,m) if(s[i][j]=='*') q.push(Node(i,j,0)),vis[i][j]=true;
    memset(dist,0x3f,sizeof(dist));//初始距离赋值为最大值，按字节赋值0x3f，结果为dist[i][j]=0x3f3f3f3f=1061109567
    while(!q.empty()){
        Node t=q.front();q.pop();
        dist[t.x][t.y]=t.time;
        FOR(i,0,4){
            int x=t.x+dx[i],y=t.y+dy[i];
            if(check(x,y)&&s[x][y]!='X'&&s[x][y]!='D') q.push(Node(x,y,t.time+1)),vis[x][y]=true;
        }
    }
}

//bfs求我抵达城堡的最短时间，如果不能抵达，返回-1
int bfs(){
    std::queue<Node> q;
    memset(vis,0,sizeof(vis));
    For(i,1,n) For(j,1,m) if(s[i][j]=='S') q.push(Node(i,j,0)),vis[i][j]=true;
    while(!q.empty()){
        Node t=q.front();q.pop();
        if(s[t.x][t.y]=='D') return t.time;
        FOR(i,0,4){
            int x=t.x+dx[i],y=t.y+dy[i];
            if(check(x,y)&&s[x][y]!='X'&&t.time+1<dist[x][y]) q.push(Node(x,y,t.time+1)),vis[x][y]=true;
        }
    }
    return -1;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    scanf("%d%d",&n,&m);
    For(i,1,n) scanf("%s",s[i]+1);
    flood_bfs();
    int ans=bfs();
    if(ans==-1) puts("ORZ hzwer!!!");
    else printf("%d\n",ans);

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
