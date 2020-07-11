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
/*namespace IO {
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
inline int read() { static int x;read(x);return x; }*/
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

const int maxn=1e5+10;
const ll INF=1ull<<60;
struct Edge { int to,dist; };
std::vector<Edge> G[maxn];
int n,m,vis[maxn];
struct Node { int u;ll dist; };
ll d[2][maxn];

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	int T;scanf("%d",&T);
	while(T--) {
		scanf("%d%d",&n,&m);
		For(i,0,n) G[i].clear();
		FOR(i,0,m) {
			int from,to,dist;scanf("%d%d%d",&from,&to,&dist);
			G[from].push_back({ to,dist });G[to].push_back({ from,dist });
		}
		std::queue<Node> q;
		int cnt=0;
		memset(vis,0,sizeof(vis));
		FOR(i,0,2) For(j,0,n) d[i][j]=INF;
		q.push({ 1,0 });vis[1]=1;d[0][1]=0;
		while(!q.empty()) {
			Node u=q.front();q.pop();
			//if(u.dist>=d[1][n]) break;
			for(auto &v:G[u.u]) {
				ll dist=u.dist+v.dist;
				if(dist<d[0][v.to]) {
					d[1][v.to]=std::min(d[1][v.to],d[0][v.to]);
					d[0][v.to]=dist;
					q.push({ v.to,dist });
				}
				else if(dist<=d[1][v.to]){
					d[1][v.to]=dist;
					if(dist<d[1][n]) q.push({ v.to,dist });
				}
			}
		}
		printf("%lld\n",d[1][n]);
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}