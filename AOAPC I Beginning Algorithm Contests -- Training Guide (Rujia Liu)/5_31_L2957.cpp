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

const int maxn=5e3;
const int INF=1e9;
struct Edge { int from,to,cap,flow; };
struct Dinic {
	int n,m,s,t;
	std::vector<int> G[maxn];
	std::vector<Edge> edges;
	bool vis[maxn];
	int cur[maxn],d[maxn];

	void init() { edges.clear(); }

	void ClearNode(int begin,int end) {
		For(i,begin,end) G[i].clear();
	}

	void AddEdge(int from,int to,int cap) {
		edges.push_back({ from,to,cap,0 });
		edges.push_back({ to,from,0,0 });
		m=edges.size();
		G[from].push_back(m-2);
		G[to].push_back(m-1);
	}

	bool BFS() {
		memset(vis,0,sizeof(vis));
		std::queue<int> q;
		d[s]=0;q.push(s);vis[s]=true;
		while(!q.empty()) {
			int x=q.front();q.pop();
			for(auto &i:G[x]) {
				Edge &e=edges[i];
				if(!vis[e.to]&&e.cap>e.flow) {
					d[e.to]=d[x]+1;
					vis[e.to]=true;
					q.push(e.to);
				}
			}
		}
		return vis[t];
	}

	int DFS(int x,int a) {
		if(x==t||a==0) return a;
		int flow=0,f;
		for(int &i=cur[x];i<G[x].size();++i) {
			Edge &e=edges[G[x][i]];
			if(d[e.to]==d[x]+1&&(f=DFS(e.to,std::min(a,e.cap-e.flow)))>0) {
				e.flow+=f;
				edges[G[x][i]^1].flow-=f;
				flow+=f;
				a-=f;
				if(a==0) break;
			}
		}
		return flow;
	}

	int Maxflow(int s,int t,int need) {
		this->s=s;this->t=t;
		int flow=0;
		while(BFS()) {
			memset(cur,0,sizeof(cur));
			flow+=DFS(s,need-flow);
			if(flow==need) return flow;
		}
		return flow;
	}
}g;

const int maxm=210;
int n,m,k,s,t;
int u[maxm],v[maxm];

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	while(scanf("%d%d%d%d%d",&n,&m,&k,&s,&t)==5) {
		FOR(i,0,m) scanf("%d%d",u+i,v+i);
		g.init();
		int day=1;
		g.ClearNode(0,n-1);
		int flow=0;
		for(;;) {
			g.ClearNode(day*n,day*n+n-1);
			FOR(i,0,n) g.AddEdge((day-1)*n+i,day*n+i,INF);
			FOR(i,0,m) {
				g.AddEdge((day-1)*n+u[i]-1,day*n+v[i]-1,1);
				g.AddEdge((day-1)*n+v[i]-1,day*n+u[i]-1,1);
			}
			flow+=g.Maxflow(s-1,day*n+t-1,k-flow);
			if(flow==k) break;
			day++;
		}

		printf("%d\n",day);
		int idx=0;
		std::vector<int> location(k,s);
		For(d,1,day) {
			idx+=n*2;
			std::vector<int> moved(k,0),a,b;
			FOR(i,0,m) {
				int f1=g.edges[idx].flow;idx+=2;
				int f2=g.edges[idx].flow;idx+=2;
				if(f1==1&&f2==0) { a.push_back(u[i]);b.push_back(v[i]); }
				if(f1==0&&f2==1) { a.push_back(v[i]);b.push_back(u[i]); }
			}
			printf("%d",a.size());
			FOR(i,0,a.size()) {
				FOR(j,0,k) if(!moved[j]&&location[j]==a[i]) {
					printf(" %d %d",j+1,b[i]);
					moved[j]=1;
					location[j]=b[i];
					break;
				}
			}
			puts("");
		}
	}




#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}