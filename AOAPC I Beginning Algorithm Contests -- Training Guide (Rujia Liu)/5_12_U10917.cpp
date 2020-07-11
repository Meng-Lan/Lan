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

const int maxn=1e3+10;
const int INF=1e9;
struct Edge {
	int from,to,dist;
	Edge(int from=0,int to=0,int dist=0) :from(from),to(to),dist(dist) {}
};
struct HeapNode {
	int d,u;
	HeapNode(int d=0,int u=0) :d(d),u(u) {}
	bool operator<(const HeapNode &rhs)const { return d>rhs.d; }
};
struct Dijkstra {
	int n,m;
	std::vector<Edge> edges;
	std::vector<int> G[maxn];
	int done[maxn],p[maxn],d[maxn];

	void init(int n) {
		this->n=n;
		FOR(i,0,n) G[i].clear();
		edges.clear();
	}

	void AddEdge(int from,int to,int dist) {
		edges.push_back(Edge(from,to,dist));
		m=edges.size();
		G[from].push_back(m-1);
	}

	void dijkstra(int s) {
		memset(done,0,sizeof(done));
		FOR(i,0,n) d[i]=INF;
		d[s]=0;
		std::priority_queue<HeapNode> q;
		q.push({ 0,s });
		while(!q.empty()) {
			HeapNode x=q.top();q.pop();
			int u=x.u;
			if(done[u]) continue;
			done[u]=1;
			for(auto &i:G[u]) {
				Edge &e=edges[i];
				if(d[e.to]>d[e.from]+e.dist) {
					d[e.to]=d[e.from]+e.dist;
					p[e.to]=i;
					q.push(HeapNode(d[e.to],e.to));
				}
			}
		}
	}
}solver;

int d[maxn],n,m;

int dp(int u) {
	if(u==1) return 1;
	int &ans=d[u];
	if(ans>=0) return ans;
	ans=0;
	for(auto &i:solver.G[u]) {
		int v=solver.edges[i].to;
		if(solver.d[v]<solver.d[u]) ans+=dp(v);
	}
	return ans;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	while(scanf("%d%d",&n,&m)==2) {
		solver.init(n);
		FOR(i,0,m) {
			int u,v,c;
			scanf("%d%d%d",&u,&v,&c);--u;--v;
			solver.AddEdge(u,v,c);
			solver.AddEdge(v,u,c);
		}
		solver.dijkstra(1);
		memset(d,-1,sizeof(d));
		printf("%d\n",dp(0));
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}