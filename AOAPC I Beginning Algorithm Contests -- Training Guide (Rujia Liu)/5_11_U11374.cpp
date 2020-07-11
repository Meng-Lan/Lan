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
const int maxn=510;
struct HeapNode {
	int d,u;
	HeapNode(int d,int u) :d(d),u(u) {}
	bool operator<(const HeapNode &rhs)const { return d>rhs.d; }
};

struct Edge {
	int from,to,dist;
	Edge(int from,int to,int dist) :from(from),to(to),dist(dist) {}
	Edge() :Edge(0,0,0) {}
};

struct Dijkstra {
	int n,m;
	std::vector<Edge> edges;
	std::vector<int> G[maxn];
	int done[maxn],d[maxn],p[maxn];

	void init(int n) {
		this->n=n;
		for(int i=0; i < n; i++) G[i].clear();
		edges.clear();
	}

	void AddEdge(int from,int to,int dist) {
		edges.push_back(Edge(from,to,dist));
		m=edges.size();
		G[from].push_back(m-1);
	}

	void dijkstra(int s) {
		std::priority_queue<HeapNode> Q;
		for(int i=0; i<n; i++) d[i]=INF;
		d[s]=0;
		memset(done,0,sizeof(done));
		Q.push(HeapNode(0,s));
		while(!Q.empty()) {
			HeapNode x=Q.top(); Q.pop();
			int u=x.u;
			if(done[u]) continue;
			done[u]=true;
			for(int i=0; i<G[u].size(); i++) {
				Edge& e=edges[G[u][i]];
				if(d[e.to]>d[u]+e.dist) {
					d[e.to]=d[u]+e.dist;
					p[e.to]=G[u][i];
					Q.push(HeapNode(d[e.to],e.to));
				}
			}
		}
	}

	void GetShortestPaths(int s,int *dist,std::vector<int> *paths) {
		dijkstra(s);
		for(int i=0; i < n; i++) {
			dist[i]=d[i];
			if(d[i]==INF) continue;
			paths[i].clear();
			int t=i;
			paths[i].push_back(t);
			while(t!=s) {
				paths[i].push_back(edges[p[t]].from);
				t=edges[p[t]].from;
			}
			reverse(paths[i].begin(),paths[i].end());
		}
	}
}dij;
int n,s,e,m,k;
int d1[maxn],d2[maxn];
std::vector<int> paths1[maxn],paths2[maxn];
int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	int kase=0;
	while(scanf("%d%d%d",&n,&s,&e)==3) {
		scanf("%d",&m);
		dij.init(n);--s,--e;
		FOR(i,0,m) {
			int u,v,d;scanf("%d%d%d",&u,&v,&d);--u;--v;
			dij.AddEdge(u,v,d);dij.AddEdge(v,u,d);
		}
		dij.GetShortestPaths(s,d1,paths1);
		dij.GetShortestPaths(e,d2,paths2);
		scanf("%d",&k);
		int ans=d1[e];
		std::vector<int> path=paths1[e];
		//printf("path.szie():%u\n",path.size());
		int midpoint=-1;
		FOR(i,0,k) {
			int u,v,c;
			scanf("%d%d%d",&u,&v,&c);--u;--v;
			FOR(j,0,2) {
				if(d1[u]+d2[v]+c<ans) {
					ans=d1[u]+d2[v]+c;
					path=paths1[u];
					for(int j=paths2[v].size()-1;j>=0;--j) path.push_back(paths2[v][j]);
					midpoint=u;
				}
				std::swap(u,v);
			}
		}
		if(kase++) puts("");
		//printf("path.szie():%u\n",path.size());
		FOR(i,0,path.size()) printf("%d%c",path[i]+1,i!=path.size()-1?' ':'\n');
		if(~midpoint) printf("%d\n",midpoint+1);
		else printf("Ticket Not Used\n");
		printf("%d\n",ans);
	}

#ifdef MengLan
	//printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}