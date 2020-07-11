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
const int maxn=410;
struct Edge { int from,to,cap,flow,cost; };
struct MCMF {
	int n,m,s,t;
	std::vector<int> G[maxn];
	std::vector<Edge> edges;
	bool inq[maxn];
	int d[maxn],p[maxn],a[maxn];

	void init(int n) {
		this->n=n;
		FOR(i,0,n) G[i].clear();
		edges.clear();
	}

	void AddEdge(int from,int to,int cap,int cost) {
		edges.push_back({ from,to,cap,0,cost });
		edges.push_back({ to,from,0,0,-cost });
		m=edges.size();
		G[from].push_back(m-2);
		G[to].push_back(m-1);
	}

	bool BellmanFord(int s,int t,int &flow,int &cost) {
		FOR(i,0,n) d[i]=INF;
		memset(inq,0,sizeof(inq));
		d[s]=0;inq[s]=true;p[s]=0;a[s]=INF;

		std::queue<int> q;
		q.push(s);
		while(!q.empty()) {
			int u=q.front();q.pop();
			inq[u]=false;
			for(auto &v:G[u]) {
				Edge &e=edges[v];
				if(e.cap>e.flow&&d[e.to]>d[u]+e.cost) {
					d[e.to]=d[u]+e.cost;
					p[e.to]=v;
					a[e.to]=std::min(a[u],e.cap-e.flow);
					if(!inq[e.to]) { q.push(e.to);inq[e.to]=true; }
				}
			}
		}
		if(d[t]>0) return false;
		//FOR(i,0,n) printf("d[%d]=%d\n",i,d[i]);
		flow+=a[t];
		cost+=d[t]*a[t];
		std::vector<int> ans;
		//int tn=(n-2)/2;
		for(int u=t;u!=s;u=edges[p[u]].from) {
			edges[p[u]].flow+=a[t];
			edges[p[u]^1].flow-=a[t];
			//if(u!=t) ans.push_back(u>tn?u-tn:u);
		}
		/*std::sort(ans.begin(),ans.end());
		ans.erase(std::unique(ans.begin(),ans.end()),ans.end());
		for(auto &v:ans) printf("%d ",v);puts("");*/
		return true;
	}

	int MincostMaxflow(int s,int t,int &cost) {
		this->s=s;this->t=t;
		int flow=0;cost=0;
		while(BellmanFord(s,t,flow,cost));
		return flow;
	}

	void print() {
		for(auto &e:edges) printf("from:%d to:%d cap:%d flow:%d cost:%d\n",e.from,e.to,e.cap,e.flow,e.cost);
	}

	void print(int u,int no) {
		if(u<=no) printf("%d ",u);
		for(auto &v:G[u]) {
			Edge &e=edges[v];
			if(e.flow>0) print(e.to,no);
		}
	}
}solver;

int n,m;

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	scanf("%d%d",&n,&m);
	solver.init(n*2+2);
	int s=0,t=n*2+1;
	For(i,1,n) {
		solver.AddEdge(s,i,1,0);
		solver.AddEdge(i,i+n,1,0);
		solver.AddEdge(i+n,t,1,0);
	}
	FOR(i,0,m) {
		int u,v;scanf("%d%d",&u,&v);
		solver.AddEdge(u+n,v,1,-1);
	}
	//solver.print();
	int cost=0;
	int flow=solver.MincostMaxflow(s,t,cost);
	for(auto &v:solver.G[s]) {
		Edge &e=solver.edges[v];
		if(e.flow>0) { solver.print(e.to,n);puts(""); }
	}
	printf("%d\n",flow);
	//solver.print();


#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}