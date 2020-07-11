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

const int maxn=110;
const int INF=1e9;
struct Edge {
	int from,to,dist;
	Edge(int from=0,int to=0,int dist=0) :from(from),to(to),dist(dist) {}
};
struct HeapNode {
	int d,u;
	HeapNode(int d,int u) :d(d),u(u) {}
	bool operator<(const HeapNode &rhs)const { return d<rhs.d; }
};
struct Dijkstra {
	int n,m;
	std::vector<int> G[maxn];
	std::vector<Edge> edges;
	bool done[maxn];
	int d[maxn],p[maxn];

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

	void dijkstra(int s) {
		std::priority_queue<HeapNode> q;
		memset(done,0,sizeof(done));
		FOR(i,0,n) d[i]=INF;
		d[s]=0;
		q.push({ 0,s });
		while(!q.empty()) {
			HeapNode x=q.top();q.pop();
			int u=x.u;
			if(done[u]) continue;
			done[u]=true;
			for(auto &i:G[u]) {
				Edge &e=edges[i];
				if(e.dist>0&&d[e.to]>d[u]+e.dist) {
					d[e.to]=d[u]+e.dist;
					p[e.to]=i;
					q.push({ d[e.to],e.to });
				}
			}
		}
	}
}solver;

int n,m,L;
std::vector<int> gr[maxn][maxn];
int used[maxn][maxn][maxn];
int idx[maxn][maxn];
int sum_sigle[maxn];

int compute_c() {
	int ans=0;
	memset(used,0,sizeof(used));
	FOR(src,0,n) {
		solver.dijkstra(src);
		sum_sigle[src]=0;
		FOR(i,0,n) {
			if(i!=src) {
				int fa=solver.edges[solver.p[i]].from;
				used[src][fa][i]=used[src][i][fa]=1;
			}
			sum_sigle[src]+=solver.d[i]==INF?L:solver.d[i];
		}
		ans+=sum_sigle[src];
	}
	return ans;
}

int compute_newc(int a,int b) {
	int ans=0;
	FOR(src,0,n) {
		if(!used[src][a][b]) ans+=sum_sigle[src];
		else {
			solver.dijkstra(src);
			FOR(i,0,n) ans+=solver.d[i]==INF?L:solver.d[i];
		}
	}
	return ans;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	while(scanf("%d%d%d",&n,&m,&L)==3) {
		solver.init(n);
		FOR(i,0,n) FOR(j,0,n) gr[i][j].clear();
		FOR(i,0,n) {
			int a,b,c;
			scanf("%d%d%d",&a,&b,&c);
			gr[a][b].push_back(c);
			gr[b][a].push_back(c);
		}

		FOR(i,0,n) FOR(j,0,n) if(!gr[i][j].empty()) {
			std::sort(gr[i][j].begin(),gr[i][j].end());
			solver.AddEdge(i,j,gr[i][j][0]);
			idx[i][j]=solver.m-1;
			solver.AddEdge(j,i,gr[i][j][0]);
			idx[j][i]=solver.m-1;
		}
		int c=compute_c();
		int c2=-1;
		FOR(i,0,n) {
			FOR(j,i+1,n) if(!gr[i][j].empty()) {
				int &e1=solver.edges[idx[i][j]].dist;
				int &e2=solver.edges[idx[i][j]].dist;
				if(gr[i][j].size()==1) e1=e2=-1;
				else e1=e2=gr[i][j][1];
				c2=std::max(c2,compute_newc(i,j));
				e1=e2=gr[i][j][0];
			}
		}
		printf("%d %d\n",c,c2);
	}


#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}