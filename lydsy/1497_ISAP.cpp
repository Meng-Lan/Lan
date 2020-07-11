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

const int INF=1e9;
const int maxn=5e3+5e4+10;
//const int maxm=5e4+10;
struct Edge {
	int from,to,cap,flow;
	Edge(int from,int to,int cap,int flow) :from(from),to(to),cap(cap),flow(flow) {}
	Edge() :from(0),to(0),cap(0),flow(0) {}
};
bool operator < (const Edge& a,const Edge& b) {
	return a.from < b.from||(a.from==b.from && a.to < b.to);
}

struct ISAP {
	int n,m,s,t;
	std::vector<Edge> edges;
	std::vector<int> G[maxn];   // 邻接表，G[i][j]表示结点i的第j条边在e数组中的序号
	bool vis[maxn];        // BFS使用
	int d[maxn];           // 从起点到i的距离
	int cur[maxn];        // 当前弧指针
	int p[maxn];          // 可增广路上的上一条弧
	int num[maxn];        // 距离标号计数

	void AddEdge(int from,int to,int cap) {
		edges.push_back(Edge(from,to,cap,0));
		edges.push_back(Edge(to,from,0,0));
		m=edges.size();
		G[from].push_back(m-2);
		G[to].push_back(m-1);
	}

	bool BFS() {
		memset(vis,0,sizeof(vis));
		std::queue<int> Q;
		Q.push(t);
		vis[t]=1;
		d[t]=0;
		while(!Q.empty()) {
			int x=Q.front(); Q.pop();
			for(int i=0; i < G[x].size(); i++) {
				Edge& e=edges[G[x][i]^1];
				if(!vis[e.from]&&e.cap > e.flow) {
					vis[e.from]=1;
					d[e.from]=d[x]+1;
					Q.push(e.from);
				}
			}
		}
		return vis[s];
	}

	void ClearAll(int n) {
		this->n=n;
		for(int i=0; i < n; i++) G[i].clear();
		edges.clear();
	}

	void ClearFlow() {
		for(int i=0; i < edges.size(); i++) edges[i].flow=0;
	}

	int Augment() {
		int x=t,a=INF;
		while(x!=s) {
			Edge& e=edges[p[x]];
			a=std::min(a,e.cap-e.flow);
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
		this->s=s; this->t=t;
		int flow=0;
		BFS();
		memset(num,0,sizeof(num));
		for(int i=0; i < n; i++) num[d[i]]++;
		int x=s;
		memset(cur,0,sizeof(cur));
		while(d[s] < n) {
			if(x==t) {
				flow+=Augment();
				if(flow>=need) return flow;
				x=s;
			}
			int ok=0;
			for(int i=cur[x]; i < G[x].size(); i++) {
				Edge& e=edges[G[x][i]];
				if(e.cap > e.flow && d[x]==d[e.to]+1) { // Advance
					ok=1;
					p[e.to]=G[x][i];
					cur[x]=i; // 注意
					x=e.to;
					break;
				}
			}
			if(!ok) { // Retreat
				int m=n-1; // 初值注意
				for(int i=0; i < G[x].size(); i++) {
					Edge& e=edges[G[x][i]];
					if(e.cap > e.flow) m=std::min(m,d[e.to]);
				}
				if(--num[d[x]]==0) break;
				num[d[x]=m+1]++;
				cur[x]=0; // 注意
				if(x!=s) x=edges[p[x]].from;
			}
		}
		return flow;
	}

	std::vector<int> Mincut() { // call this after maxflow
		BFS();
		std::vector<int> ans;
		for(int i=0; i < edges.size(); i++) {
			Edge& e=edges[i];
			if(!vis[e.from]&&vis[e.to]&&e.cap > 0) ans.push_back(i);
		}
		return ans;
	}

	void Reduce() {
		for(int i=0; i < edges.size(); i++) edges[i].cap-=edges[i].flow;
	}

	void print() {
		printf("Graph:\n");
		for(int i=0; i < edges.size(); i++)
			printf("%d->%d, %d, %d\n",edges[i].from,edges[i].to,edges[i].cap,edges[i].flow);
	}
}g;

int n,m;

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	scanf("%d%d",&n,&m);
	g.ClearAll(n+m+2);
	int s=0,t=n+m+1;
	For(i,1,n) { int x;scanf("%d",&x);g.AddEdge(i,t,x); }
	int sigma=0;
	For(i,n+1,m+n) {
		int u,v,c;scanf("%d%d%d",&u,&v,&c);
		g.AddEdge(s,i,c);
		g.AddEdge(i,u,INF);
		g.AddEdge(i,v,INF);
		sigma+=c;
	}
	printf("%d\n",sigma-g.Maxflow(s,t,INF));

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}