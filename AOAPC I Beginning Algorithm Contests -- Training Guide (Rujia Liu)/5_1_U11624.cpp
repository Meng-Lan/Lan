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

const int maxn=1e3+10;
char s[maxn][maxn];
int vis[maxn][maxn],t[maxn][maxn],n,m,cnt;

const int dx[]={ 1,0,-1,0 };
const int dy[]={ 0,1,0,-1 };

struct Node {
	int x,y,t;
	Node(int x=0,int y=0,int t=0) :x(x),y(y),t(t) {}
};

inline bool check(int x,int y) { return x>=1&&x<=n&&y>=1&&y<=m; }

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	int T;scanf("%d",&T);
	while(T--) {
		memset(t,0x3f,sizeof(t));
		scanf("%d%d",&n,&m);
		For(i,1,n) scanf("%s",s[i]+1);
		std::queue<Node> q;++cnt;
		For(i,1,n) For(j,1,m) if(s[i][j]=='F') { q.push(Node(i,j,0));vis[i][j]=cnt; }
		while(!q.empty()) {
			Node u=q.front();q.pop();
			if(!check(u.x,u.y)) continue;
			t[u.x][u.y]=u.t;
			FOR(i,0,4) {
				int x=u.x+dx[i],y=u.y+dy[i];
				if(check(x,y)&&vis[x][y]!=cnt&&s[x][y]!='#') {
					q.push(Node(x,y,u.t+1));vis[x][y]=cnt;
				}
			}
		}
		++cnt;
		For(i,1,n) For(j,1,m) if(s[i][j]=='J') { q.push(Node(i,j,0));vis[i][j]=cnt; }
		int ans=-1;
		while(!q.empty()) {
			Node u=q.front();q.pop();
			if(!check(u.x,u.y)) { ans=u.t;break; }
			FOR(i,0,4) {
				int x=u.x+dx[i],y=u.y+dy[i];
				if(vis[x][y]!=cnt&&s[x][y]!='#'&&u.t+1<t[x][y]) {
					q.push(Node(x,y,u.t+1));vis[x][y]=cnt;
				}
			}
		}
		if(ans!=-1) printf("%d\n",ans);
		else puts("IMPOSSIBLE");
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}