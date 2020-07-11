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
struct Edge { int from,to,dist; };
struct HeapNode {
	int u;
	ll d;
	bool operator<(const HeapNode &rhs)const { return d>rhs.d; }
};
struct Dijkstra {
	int n,m;
	std::vector<int> G[maxn];
	std::vector<Edge> edges;
	bool done[maxn];
	ll d[maxn];

	void init(int n) {
		this->n=n;
		FOR(i,0,n) G[i].clear();
		edges.clear();
	}

	void AddEdge(int from,int to,int dist) {
		edges.push_back({ from,to,dist });
		m=edges.size();
		G[from].push_back(m-1);
	}

	ll dijkstra(int s,int t) {
		memset(done,0,sizeof(done));
		FOR(i,0,n) d[i]=INF;
		std::priority_queue<HeapNode> q;
		d[s]=0;q.push({ s,d[s] });
		while(!q.empty()) {
			HeapNode x=q.top();q.pop();
			int u=x.u;
			if(done[u]) continue;
			if(u==t) return d[u];
			done[u]=true;
			for(auto &i:G[u]) {
				Edge &e=edges[i];
				if(d[e.to]>d[u]+e.dist) {
					d[e.to]=d[u]+e.dist;
					//printf("u:%d -> v:%d d:%d\n",u,e.to,d[e.to]);
					q.push({ e.to,d[e.to] });
				}
			}
		}
		return d[t];
	}
}solver;

int n,m,u[maxn],v[maxn],c[maxn],k,s[maxn];

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	int T;scanf("%d",&T);
	For(kase,1,T) {
		scanf("%d%d",&n,&m);
		FOR(i,0,m) scanf("%d%d%d",u+i,v+i,c+i);
		scanf("%d",&k);
		FOR(i,0,k) scanf("%d",s+i);
		int S=0,T=n+1;
		ll ans=INF;
		FOR(i,0,20) {
			solver.init(n+2);
			FOR(i,0,m) solver.AddEdge(u[i],v[i],c[i]);
			int bit=1<<i;
			//printf("bit:%d\n",bit);
			FOR(i,0,k) {
				if(s[i]&bit) {
					solver.AddEdge(S,s[i],0);
					//printf("S:%d s[%d]:%d\n",S,i,s[i]);
				}
				else {
					solver.AddEdge(s[i],T,0);
					//printf("s[%d]:%d T:%d\n",i,s[i],T);
				}
			}
			ans=std::min(ans,solver.dijkstra(S,T));
			//printf("ans:%lld\n",ans);
			solver.init(n+2);
			FOR(i,0,m) solver.AddEdge(u[i],v[i],c[i]);
			FOR(i,0,k) {
				if((s[i]&bit)==0) solver.AddEdge(S,s[i],0);
				else solver.AddEdge(s[i],T,0);
			}
			ans=std::min(ans,solver.dijkstra(S,T));
			//printf("ans:%lld\n",ans);
		}
		printf("Case #%d: %lld\n",kase,ans);
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}