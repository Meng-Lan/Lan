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

const int maxn=25*25+25+10;
const int INF=1e9;
struct Edge { int from,to,cap,flow; };
struct ISAP {
	int n,m,s,t;
	std::vector<Edge> edges;
	std::vector<int> G[maxn];
	bool vis[maxn];
	int cur[maxn],d[maxn],p[maxn],num[maxn];

	void init(int n) {
		this->n=n;
		FOR(i,0,n) G[i].clear();
		edges.clear();
	}

	void ClearFlow() { for(auto &e:edges) e.flow=0; }

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
		d[t]=0;vis[t]=true;q.push(t);
		while(!q.empty()) {
			int x=q.front();q.pop();
			for(auto &i:G[x]) {
				Edge &e=edges[i^1];
				if(e.cap>e.flow&&!vis[e.from]) {
					d[e.from]=d[x]+1;
					vis[e.from]=true;
					q.push(e.from);
				}
			}
		}
		return vis[s];
	}

	int Augment() {
		int x=t,a=INF;
		while(x!=s) {
			a=std::min(a,edges[p[x]].cap-edges[p[x]].flow);
			x=edges[p[x]].from;
		}
		x=t;
		while(x!=s) {
			edges[p[x]].flow+=a;
			edges[p[x]^1].flow-=a;
			x=edges[p[x]].from;
		}
		return a;
	}

	int Maxflow(int s,int t,int need) {
		this->s=s;this->t=t;
		BFS();
		memset(num,0,sizeof(num));
		FOR(i,0,n) num[d[i]]++;
		int x=s,flow=0;
		memset(cur,0,sizeof(cur));
		while(d[s]<n) {
			if(x==t) {
				flow+=Augment();
				if(flow>=need) break;
				x=s;
			}
			int ok=0;
			for(int i=cur[x];i<G[x].size();++i) {
				Edge &e=edges[G[x][i]];
				if(d[e.to]+1==d[x]&&e.cap>e.flow) {
					ok=1;
					p[e.to]=G[x][i];
					cur[x]=i;
					x=e.to;
					break;
				}
			}
			if(!ok) {
				int m=n-1;
				for(auto &i:G[x]) {
					Edge &e=edges[i];
					if(e.cap>e.flow) m=std::min(m,d[e.to]);
				}
				if(--num[d[x]]==0) break;
				num[d[x]=m+1]++;
				cur[x]=0;
				if(x!=s) x=edges[p[x]].from;
			}
		}
		return flow;
	}
}g;

const int N=30;
int n,w[N],d[N],in[N][N];

inline int ID(int u,int v) { return u*n+v+1; }
inline int ID(int u) { return n*n+u+1; }

bool CanWin(int no) {
	int total=w[no];
	FOR(i,0,n) total+=in[no][i];
	FOR(i,0,n) if(w[i]>total) return false;
	g.init(n*n+n+2);
	int full=0;
	int s=0,t=n*n+n+1;
	FOR(u,0,n) {
		FOR(v,u+1,n) {
			if(in[u][v]>0) g.AddEdge(s,ID(u,v),in[u][v]);
			full+=in[u][v];
			g.AddEdge(ID(u,v),ID(u),INF);
			g.AddEdge(ID(u,v),ID(v),INF);
		}
		if(w[u]<total) g.AddEdge(ID(u),t,total-w[u]);
	}
	return g.Maxflow(s,t,INF)==full;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	int T;scanf("%d",&T);
	while(T--) {
		scanf("%d",&n);
		FOR(i,0,n) scanf("%d%d",w+i,d+i);
		FOR(i,0,n) FOR(j,0,n) scanf("%d",in[i]+j);
		bool first=true;
		FOR(i,0,n) {
			if(CanWin(i)) {
				if(first) first=false;else printf(" ");
				printf("%d",i+1);
			}
		}
		puts("");
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}