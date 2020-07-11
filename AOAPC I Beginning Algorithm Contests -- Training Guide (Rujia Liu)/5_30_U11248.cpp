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

const int maxn=105;
const int INF=1e9;
struct Edge { int from,to,cap,flow; };
bool operator<(const Edge &l,const Edge &r) {
	return l.from<r.from||l.from==r.from&&l.to<r.to;
}
struct Dinic {
	int n,m,s,t;
	std::vector<int> G[maxn];
	std::vector<Edge> edges;
	bool vis[maxn];
	int d[maxn],cur[maxn];

	void init(int n) {
		this->n=n;
		FOR(i,0,n) G[i].clear();
		edges.clear();
	}

	void ClearFlow() {
		for(auto &e:edges) e.flow=0;
	}

	void AddEdge(int from,int to,int cap) {
		edges.push_back({ from,to,cap, 0 });
		edges.push_back({ to,from,0,0 });
		m=edges.size();
		G[from].push_back(m-2);
		G[to].push_back(m-1);
	}

	bool BFS() {
		memset(vis,0,sizeof(vis));
		std::queue<int> q;
		d[s]=0;vis[s]=true;q.push(s);
		while(!q.empty()) {
			int x=q.front();q.pop();
			for(auto &i:G[x]) {
				Edge &e=edges[i];
				if(!vis[e.to]&&e.cap>e.flow) {
					d[e.to]=d[x]+1;
					vis[e.to]=1;
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
			if(d[x]+1==d[e.to]&&(f=DFS(e.to,std::min(a,e.cap-e.flow)))>0) {
				e.flow+=f;
				edges[G[x][i]^1].flow-=f;
				flow+=f;
				a-=f;
				if(a==0) return flow;
			}
		}
		return flow;
	}

	int Maxflow(int s,int t) {
		this->s=s;this->t=t;
		int flow=0;
		while(BFS()) {
			memset(cur,0,sizeof(cur));
			flow+=DFS(s,INF);
		}
		return flow;
	}

	std::vector<int> Mincut() {
		std::vector<int> ans;
		FOR(i,0,edges.size()) {
			Edge &e=edges[i];
			if(vis[e.from]&&!vis[e.to]&&e.cap>0) ans.push_back(i);
		}
		return ans;
	}

	void Reduce() {
		for(auto &e:edges) e.cap-=e.flow;
	}
}g;

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	int n,e,c,kase=0;
	while(scanf("%d%d%d",&n,&e,&c)==3&&n) {
		g.init(n);
		while(e--) {
			int b1,b2,fp;scanf("%d%d%d",&b1,&b2,&fp);
			g.AddEdge(b1-1,b2-1,fp);
		}
		int flow=g.Maxflow(0,n-1);
		printf("Case %d: ",++kase);
		if(flow>=c) puts("possible");
		else {
			std::vector<int> cut=g.Mincut();
			g.Reduce();
			std::vector<Edge> ans;
			for(auto &i:cut) {
				Edge &e=g.edges[i];
				e.cap=c;
				g.ClearFlow();
				if(flow+g.Maxflow(0,n-1)>=c) ans.push_back(e);
				e.cap=0;
			}
			if(ans.empty()) puts("not possible");
			else {
				std::sort(ans.begin(),ans.end());
				printf("possible option:(%d,%d)",ans[0].from+1,ans[0].to+1);
				for(int i=1; i<ans.size(); i++)
					printf(",(%d,%d)",ans[i].from+1,ans[i].to+1);
				printf("\n");
			}
		}
	}


#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}