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
while(isalnum(c=IO::getchar())) { in*=10;in+=c-'0'; }
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

const int maxn=2e6+10;
const int INF=1e9;
struct Edge {
	int to,dist,next;
	Edge(int to=0,int dist=0,int next=0) :to(to),dist(dist),next(next) {}
};
struct HeapNode {
	int d,u;
	HeapNode(int d,int u) :d(d),u(u) {}
	bool operator<(const HeapNode &rhs)const { return d>rhs.d; }
};
struct Dijkstra {
	int n,m;
	//std::vector<Edge> edges;
	//std::vector<int> G[maxn];
	Edge edges[maxn*3];
	int head[maxn];
	int d[maxn];
	bool done[maxn];

	void init(int n) {
		this->n=n;
		m=0;
		FOR(i,0,n) head[i]=-1;
	}

	void AddEdge(int from,int to,int dist) {
		edges[m].to=to;
		edges[m].dist=dist;
		edges[m].next=head[from];
		head[from]=m++;
	}

	void dijkstra(int s) {
		memset(done,0,sizeof(done));
		FOR(i,0,n) d[i]=INF;
		std::priority_queue<HeapNode> q;
		d[s]=0;q.push(HeapNode(0,s));
		while(!q.empty()) {
			HeapNode x=q.top();q.pop();
			int u=x.u;
			if(done[u]) continue;
			done[u]=true;
			for(int i=head[u];~i;i=edges[i].next) {
				Edge &e=edges[i];
				if(d[e.to]>d[u]+e.dist) {
					d[e.to]=d[u]+e.dist;
					q.push(HeapNode(d[e.to],e.to));
				}
			}
		}
	}
}solver;

const int maxsz=1000;
int n,m,cost[maxsz][maxsz][3];

int ID(int r,int c,int half) { return half*n*m+r*m+c+1; }

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	int kase=0;
	scanf("%d%d",&n,&m);
	if(n==1||m==1) {
		if(n > m) std::swap(n,m);
		int ans=INF;
		for(int i=1; i < m; ++i) {
			int x;
			scanf("%d",&x);
			if(x < ans) ans=x;
		}
		printf("%d\n",ans);
		exit(0);
	}
	FOR(i,0,n) FOR(j,0,m-1) scanf("%d",cost[i][j]);
	FOR(i,0,n-1) FOR(j,0,m) scanf("%d",cost[i][j]+1);
	FOR(i,0,n-1) FOR(j,0,m-1) scanf("%d",cost[i][j]+2);
	solver.init(2*n*m+2);
	FOR(i,0,n-1) FOR(j,0,m-1) {
		int id1=ID(i,j,0);
		if(j>0) solver.AddEdge(id1,ID(i,j-1,1),cost[i][j][1]);
		if(i<n-1) solver.AddEdge(id1,ID(i+1,j,1),cost[i+1][j][0]);
		int id2=ID(i,j,1);
		if(i>0) solver.AddEdge(id2,ID(i-1,j,0),cost[i][j][0]);
		if(j<m-1) solver.AddEdge(id2,ID(i,j+1,0),cost[i][j+1][1]);
		solver.AddEdge(id1,id2,cost[i][j][2]);
		solver.AddEdge(id2,id1,cost[i][j][2]);
	}
	FOR(i,0,n-1) solver.AddEdge(0,ID(i,0,0),cost[i][0][1]);
	FOR(i,0,m-1) solver.AddEdge(0,ID(n-2,i,0),cost[n-1][i][0]);
	FOR(i,0,n-1) solver.AddEdge(ID(i,m-2,1),2*n*m+1,cost[i][m-1][1]);
	FOR(i,0,m-1) solver.AddEdge(ID(0,i,1),2*n*m+1,cost[0][i][0]);
	solver.dijkstra(0);
	printf("%d\n",solver.d[2*n*m+1]);
	//printf("Case %d: Minimum = %d\n",++kase,solver.d[2*n*m+1]);


#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}