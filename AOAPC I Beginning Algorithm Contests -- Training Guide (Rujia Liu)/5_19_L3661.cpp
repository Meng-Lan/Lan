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
namespace IO {
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
inline int read() { static int x;read(x);return x; }
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

const int maxn=3e6+10;
const int INF=1e9;
struct Edge {
	int from,to,dist;
	Edge(int from=0,int to=0,int dist=0) :from(from),to(to),dist(dist) {}
};
struct HeapNode {
	int d,u;
	HeapNode(int d,int u) :d(d),u(u) {}
	bool operator<(const HeapNode &rhs)const { return d>rhs.d; }
};
struct Dijkstra {
	int n,m;
	std::vector<Edge> edges;
	std::vector<int> G[maxn];
	int d[maxn];
	//int p[maxn];
	bool done[maxn];

	void init(int n) {
		this->n=n;
		FOR(i,0,n) G[i].clear();
		edges.clear();
	}

	void AddEdge(int from,int to,int dist) {
		edges.push_back(Edge(from,to,dist ));
		m=edges.size();
		G[from].push_back(m-1);
	}

	void dijkstra(int s) {
		memset(done,0,sizeof(done));
		FOR(i,0,n) d[i]=INF;
		std::priority_queue<HeapNode> q;
		d[s]=0;q.push(HeapNode(0,s ));
		while(!q.empty()) {
			HeapNode x=q.top();q.pop();
			int u=x.u;
			if(done[u]) continue;
			done[u]=true;
			FOR(i,0,G[u].size()) {
				Edge &e=edges[G[u][i]];
				if(d[e.to]>d[u]+e.dist) {
					d[e.to]=d[u]+e.dist;
					q.push(HeapNode(d[e.to],e.to ));
				}
			}
		}
	}
}solver;

const int maxsize=1000;
int n,m,cost[maxsize][maxsize][3];

int ID(int r,int c,int type) { return type*n*m+r*m+c+1; }

void AddTriangleEdges(int *s1,int *s2,int *s3) {
	int *edges[3]={ s1,s2,s3 };
	FOR(i,0,3) FOR(j,0,3) if(i!=j) {
		int id1=ID(edges[i][0],edges[i][1],edges[i][2]);
		int id2=ID(edges[j][0],edges[j][1],edges[j][2]);
		int c=cost[edges[j][0]][edges[j][1]][edges[j][2]];
		solver.AddEdge(id1,id2,c);
	}
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	int kase=0;
	while(scanf("%d%d",&n,&m)==2&&n) {
		FOR(i,0,n) FOR(j,0,m-1) scanf("%d",cost[i][j]);
		FOR(i,0,n-1) FOR(j,0,m) scanf("%d",cost[i][j]+1);
		FOR(i,0,n-1) FOR(j,0,m-1) scanf("%d",cost[i][j]+2);
		solver.init(n*m*3+1);
		FOR(i,0,n-1) FOR(j,0,m-1) {
			int top[]={ i,j,0 };
			int bottom[]={ i+1,j,0 };
			int left[]={ i,j,1 };
			int right[]={ i,j+1,1 };
			int slash[]={ i,j,2 };
			AddTriangleEdges(top,slash,right);
			AddTriangleEdges(left,slash,bottom);
		}
		FOR(i,0,n-1) solver.AddEdge(0,ID(i,0,1),cost[i][0][1]);
		FOR(i,0,m-1) solver.AddEdge(0,ID(n-1,i,0),cost[n-1][i][0]);
		solver.dijkstra(0);
		int ans=2*INF;
		FOR(i,0,n-1) ans=std::min(ans,solver.d[ID(i,m-1,1)]);
		FOR(i,0,m-1) ans=std::min(ans,solver.d[ID(0,i,0)]);
		//printf("Case %d: Minimum = %d\n",++kase,ans);
		printf("%d\n",ans);
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}