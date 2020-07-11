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
const int maxn=8e4+10;
struct Edge {
	int from,to,dist;
	Edge(int from,int to,int dist) :from(from),to(to),dist(dist) {}
};
struct HeapNode {
	int u,d;
	HeapNode(int d,int u) :d(d),u(u) {}
	bool operator<(const HeapNode &rhs)const { return d>rhs.d; }
};
struct Dijkstra {
	int n,m;
	std::vector<Edge> edges;
	std::vector<int> G[maxn];
	int d[maxn],p[maxn];
	bool done[maxn];

	void init(int n) {
		this->n=n;
		FOR(i,0,n) G[i].clear();
		edges.clear();
	}

	void AddEdge(int u,int v,int c) {
		edges.push_back({ u,v,c });
		m=edges.size();
		G[u].push_back(m-1);
	}

	void dijkstra(int s) {
		std::priority_queue<HeapNode> q;
		memset(done,0,sizeof(done));
		FOR(i,0,n) d[i]=INF;
		d[s]=0;q.push({ 0,s });
		while(!q.empty()) {
			auto x=q.top();q.pop();
			int u=x.u;
			if(done[u]) continue;
			done[u]=true;
			for(auto &i:G[u]) {
				Edge &e=edges[i];
				if(d[e.to]>d[u]+e.dist) {
					d[e.to]=d[u]+e.dist;
					p[e.to]=i;
					q.push({ d[e.to],e.to });
				}
			}
		}
	}
}solver;

enum Lan { UP,LEFT,DOWN,RIGHT };
const int inv[]={ 2,3,0,1 };
const int dr[]={ -1,0,1,0 };
const int dc[]={ 0,-1,0,1 };
const int maxr=105,maxc=105;
int grid[maxr][maxc][4];
int n,id[maxr][maxc][4][2];

inline int ID(int r,int c,int dir,int doubled) {
	int &x=id[r][c][dir][doubled];
	if(!x) x=++n;
	return x;
}

inline int readint() {
	static int x;scanf("%d",&x);return x;
}

int R,C;
bool cango(int r,int c,int dir) {
	if(r<0||r>=R||c<0||c>=C) return false;
	return grid[r][c][dir]>0;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	int r1,r2,c1,c2,kase=0;
	while(scanf("%d%d%d%d%d%d",&R,&C,&r1,&c1,&r2,&c2)==6&&R){
		--r1,--r2,--c1,--c2;
		FOR(r,0,R) {
			FOR(c,0,C-1) grid[r][c][RIGHT]=grid[r][c+1][LEFT]=readint();
			if(r!=R-1) FOR(c,0,C)grid[r][c][DOWN]=grid[r+1][c][UP]=readint();
		}

		solver.init(R*C*8+1);
		n=0;
		memset(id,0,sizeof(id));

		FOR(dir,0,4) if(cango(r1,c1,dir))
			solver.AddEdge(0,ID(r1+dr[dir],c1+dc[dir],dir,1),grid[r1][c1][dir]*2);

		FOR(r,0,R) FOR(c,0,C) FOR(dir,0,4) if(cango(r,c,inv[dir])) {
			FOR(newdir,0,4) if(cango(r,c,newdir)) {
				FOR(doubled,0,2) {
					int newr=r+dr[newdir];
					int newc=c+dc[newdir];
					int v=grid[r][c][newdir],newdoubled=0;
					if(dir!=newdir) {
						if(!doubled) v+=grid[r][c][inv[dir]];
						newdoubled=1;v+=grid[r][c][newdir];
					}
					solver.AddEdge(ID(r,c,dir,doubled),ID(newr,newc,newdir,newdoubled),v);
				}
			}
		}

		solver.dijkstra(0);

		int ans=INF;
		FOR(dir,0,4) if(cango(r2,c2,inv[dir])) FOR(doubled,0,2) {
			int v=solver.d[ID(r2,c2,dir,doubled)];
			if(!doubled) v+=grid[r2][c2][inv[dir]];
			ans=std::min(ans,v);
		}
		
		printf("Case %d: ",++kase);
		if(ans==INF) printf("Impossible\n");else printf("%d\n",ans);
	}


#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}