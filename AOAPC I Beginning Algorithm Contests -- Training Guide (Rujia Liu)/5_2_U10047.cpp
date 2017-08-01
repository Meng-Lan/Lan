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
#define mp std::make_pair
ll Factorial(ll i) { return i > 1?i*Factorial(i-1):1; }
ll Combination(ll n,ll r) {
	if(n-r < r) r=n-r;
	ll ansn=1,ansr=1;
	for(ll i=n-r+1; i<=n; ++i) ansn*=i;
	for(ll j=1; j<=r; ++j) ansr*=j;
	return ansn/ansr;
}
ll gcd(ll a,ll b) { return b?gcd(b,a%b):a; }
ll lcm(ll a,ll b) { return a/gcd(a,b)*b; }
std::vector<int> Eratosthenes(const int len,int *vis) {
	memset(vis,0,sizeof(int)*len);
	std::vector<int> prime;
	int m=(int)sqrt(len+0.5);
	For(i,2,m) if(!vis[i]) for(int j=i*i; j < len; j+=i) vis[j]=1;
	FOR(i,2,len) if(!vis[i]) prime.push_back(i);
	return prime;
}
void phi_table(int n,int *phi) {
	For(i,2,n) phi[i]=0;
	phi[1]=1;
	For(i,2,n) if(!phi[i])
		for(int j=i; j<=n; j+=i) {
			if(!phi[j]) phi[j]=j;
			phi[j]=phi[j]/i*(i-1);
		}
}

const int maxn=25+5;
int n,m,vis[maxn][maxn][5][4];
char s[maxn][maxn];

const int dx[]={ -1,0,1,0 };
const int dy[]={ 0,1,0,-1 };

struct Node {
	int x,y,d,c,s;
	Node(int x=0,int y=0,int d=0,int c=0,int s=0) :x(x),y(y),d(d),c(c),s(s) {}
};

inline int& sta(const Node &u) { return vis[u.x][u.y][u.c][u.d]; }

bool check(int x,int y) { return x>=0&&x<m&&y>=0&&y<n; }

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	int kase=0;
	while(scanf("%d%d",&m,&n)==2&&n&&m) {
		if(kase) puts("");
		FOR(i,0,m) scanf("%s",s+i);
		++kase;
		std::queue<Node> q;
		FOR(i,0,m) FOR(j,0,n) if(s[i][j]=='S') { q.push(Node(i,j));sta(Node(i,j))=kase; }
		int ans=-1;
		while(!q.empty()) {
			Node u=q.front();q.pop();
			if(s[u.x][u.y]=='T'&&u.c==0) { ans=u.s;break; }
			For(i,-1,1) if(i) {
				Node v=u;v.d=(v.d+i+4)%4;v.s++;
				if(sta(v)!=kase) { sta(v)=kase;q.push(v); }
			}
			Node v(u.x+dx[u.d],u.y+dy[u.d],u.d,(u.c+1)%5,u.s+1);
			if(check(v.x,v.y)&&s[v.x][v.y]!='#'&&sta(v)!=kase) { sta(v)=kase;q.push(v); }
		}
		if(ans!=-1) printf("Case #%d\nminimum time = %d sec\n",kase,ans);
		else printf("Case #%d\ndestination not reachable\n",kase);
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}