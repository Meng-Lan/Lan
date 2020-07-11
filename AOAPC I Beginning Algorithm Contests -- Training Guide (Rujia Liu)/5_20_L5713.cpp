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
int n;
struct Coordinate {
	int x,y,p;
	void input() { scanf("%d%d%d",&x,&y,&p); }
	double sqr(double x)const { return x*x; }
	double operator-(const Coordinate &rhs)const {
		return sqrt(sqr(x-rhs.x)+sqr(y-rhs.y));
	}
}in[maxn];

int fa[maxn];
int find(int x) { return fa[x]=fa[x]==x?x:find(fa[x]); }
struct Edge {
	int u,v;
	double c;
	Edge(int u,int v,double c) :u(u),v(v),c(c) {}
	Edge() :Edge(0,0,0) {}
	bool operator<(const Edge &e)const {
		return c<e.c;
	}
};
std::vector<Edge> e;
std::vector<int> G[maxn];
double MST() {
	FOR(i,0,n) fa[i]=i;
	std::sort(e.begin(),e.end());
	FOR(i,0,n) G[i].clear();
	int cnt=0;
	double cost=0;
	FOR(i,0,e.size()) {
		int u=find(e[i].u),v=find(e[i].v);
		if(u!=v) {
			//printf("mst: u:%d v:%d c:%f\n",e[i].u,e[i].v,e[i].c);
			fa[u]=v;cost+=e[i].c;
			G[e[i].u].push_back(i);
			G[e[i].v].push_back(i);
			if(++cnt==n-1) break;
		}
	}
	return cost;
}

double maxcost[maxn][maxn];
std::vector<int> set;
void dfs(int u,int fa,double facost) {
	//printf("u:%d fa:%d\n",u,fa);
	for(auto &v:set) maxcost[u][v]=maxcost[v][u]=std::max(maxcost[fa][v],facost);
	set.push_back(u);
	for(auto &i:G[u]) {
		int v=e[i].u==u?e[i].v:e[i].u;
		if(v!=fa) dfs(v,u,e[i].c);
	}
}

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	int T;scanf("%d",&T);
	while(T--) {
		scanf("%d",&n);
		FOR(i,0,n) in[i].input();
		e.clear();
		FOR(i,0,n) FOR(j,i+1,n) e.push_back(Edge(i,j,in[i]-in[j]));
		//for(auto &edge:e) printf("u:%d v:%d c:%f\n",edge.u,edge.v,edge.c);
		double cost=MST();
		memset(maxcost,0x00,sizeof(maxcost));
		set.clear();
		//FOR(u,0,n) for(auto &i:G[u]) { printf("u:%d v:%d U:%d\n",e[i].u,e[i].v,u); }
		dfs(0,-1,0);
		//FOR(u,0,n) FOR(v,0,n) printf("u:%d v:%d mc:%f\n",u,v,maxcost[u][v]);
		double ans=0;
		FOR(u,0,n) FOR(v,u+1,n) ans=std::max(ans,(double)(in[u].p+in[v].p)/(cost-maxcost[u][v]));
		printf("%.2f\n",ans);
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}