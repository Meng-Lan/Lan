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

//using namespace std;
const int maxn=10000+10;
const int INF=1000000000;

typedef long long LL;

struct Edge {
	int from,to,cap,flow,cost;
};

struct MCMF {
	int n,m,s,t;
	std::vector<Edge> edges;
	std::vector<int> G[maxn];
	int inq[maxn];         // 是否在队列中
	int d[maxn];           // Bellman-Ford
	int p[maxn];           // 上一条弧
	int a[maxn];           // 可改进量

	void init(int n) {
		this->n=n;
		for(int i=0; i < n; i++) G[i].clear();
		edges.clear();
	}

	void AddEdge(int from,int to,int cap,int cost) {
		edges.push_back({ from,to,cap,0,cost });
		edges.push_back({ to,from,0,0,-cost });
		m=edges.size();
		G[from].push_back(m-2);
		G[to].push_back(m-1);
	}

	bool BellmanFord(int s,int t,LL& ans,int &flow) {
		for(int i=0; i < n; i++) d[i]=INF;
		memset(inq,0,sizeof(inq));
		d[s]=0; inq[s]=1; p[s]=0; a[s]=INF;

		std::queue<int> Q;
		Q.push(s);
		while(!Q.empty()) {
			int u=Q.front(); Q.pop();
			inq[u]=0;
			for(int i=0; i < G[u].size(); i++) {
				Edge& e=edges[G[u][i]];
				if(e.cap > e.flow && d[e.to] > d[u]+e.cost) {
					d[e.to]=d[u]+e.cost;
					p[e.to]=G[u][i];
					a[e.to]=std::min(a[u],e.cap-e.flow);
					if(!inq[e.to]) { Q.push(e.to); inq[e.to]=1; }
				}
			}
		}
		if(d[t]==INF) return false;
		ans+=(LL)d[t]*(LL)a[t];
		flow+=a[t];
		int u=t;
		while(u!=s) {
			edges[p[u]].flow+=a[t];
			edges[p[u]^1].flow-=a[t];
			u=edges[p[u]].from;
		}
		return true;
	}

	// 需要保证初始网络中没有负权圈
	int Mincost(int s,int t,LL &cost) {
		cost=0;
		int flow=0;
		while(BellmanFord(s,t,cost,flow));
		return flow;
	}

}g;

std::map<std::string,int> id;
int no;
int ID(std::string s) {
	if(id.count(s)) return id[s];
	id[s]=no++;
	return id[s];
}
int m;
typedef std::pair<P,int> PI;
PI in[maxn];

const std::string dl="Dalian",sh="Shanghai",xa="Xian";

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	int T;cin>>T;
	while(T--) {
		cin>>m;
		id.clear();no=0;
		int bgn=ID(dl),mid=ID(sh),end=ID(xa);
		//printf("# %d %d %d\n",bgn,mid,end);
		FOR(i,0,m) {
			std::string s,t;
			int u,v,cost;
			cin>>s>>t>>cost;
			u=ID(s);v=ID(t);
			in[i]=PI(P(u,v),cost);
		}
		//printf("no:%d\n",no);
		//printf("sum:%lld\n",sum);
		g.init(no*2+2);
		FOR(i,0,m) {
			g.AddEdge(in[i].first.first+no,in[i].first.second,1,in[i].second);
			g.AddEdge(in[i].first.second+no,in[i].first.first,1,in[i].second);
		}
		FOR(i,0,no) if(i!=mid) g.AddEdge(i,i+no,1,0);else g.AddEdge(mid,mid+no,2,0);
		int s=2*no,t=2*no+1;
		g.AddEdge(s,bgn,1,0);
		g.AddEdge(s,end,1,0);
		g.AddEdge(mid,t,2,0);
		ll ans;
		int flow=g.Mincost(s,t,ans);
		if(flow==2) printf("%lld\n",ans);
		else puts("-1");
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}