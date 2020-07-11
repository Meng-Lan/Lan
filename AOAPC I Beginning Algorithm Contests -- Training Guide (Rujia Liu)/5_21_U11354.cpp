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
const int maxn=5e4+10,maxm=1e5+10;
struct Edge {
	int u,v,d;
	Edge(int u,int v,int d) :u(u),v(v),d(d) {}
	Edge() :Edge(0,0,0) {}
	bool operator<(const Edge &rhs)const { return d<rhs.d; }
};
std::vector<Edge> edges,G[maxn];
int n,m,q;

int pa[maxn];
int find(int x) { return pa[x]=pa[x]==x?x:find(pa[x]); }
void MST() {
	FOR(i,0,n) { G[i].clear();pa[i]=i; }
	std::sort(edges.begin(),edges.end());
	int cnt=0;
	for(auto &e:edges) {
		int u=find(e.u),v=find(e.v);
		if(u!=v) {
			pa[u]=v;
			//printf("u:%d v:%d d:%d\n",e.u,e.v,e.d);
			G[e.u].push_back(e);
			G[e.v].push_back(e);
			if(++cnt==n-1) return;
		}
	}
}

int fa[maxn],cost[maxn],L[maxn];
void dfs(int u,int f,int deep) {
	L[u]=deep;
	for(auto &e:G[u]) {
		int v=e.u==u?e.v:e.u;
		if(v!=f) {
			fa[v]=u;
			cost[v]=e.d;
			dfs(v,u,deep+1);
		}
	}
}

int anc[maxn][16],maxcost[maxn][16];
void preprocess() {
	FOR(i,0,n) {
		anc[i][0]=fa[i];maxcost[i][0]=cost[i];
		for(int j=1;(1<<j)<n;++j) anc[i][j]=-1;
	}
	for(int j=1;(1<<j)<n;++j) FOR(i,0,n)
		if(anc[i][j-1]!=-1) {
			int a=anc[i][j-1];
			anc[i][j]=anc[a][j-1];
			maxcost[i][j]=std::max(maxcost[i][j-1],maxcost[a][j-1]);
		}
}

int query(int p,int q) {
	int tmp,log;
	if(L[p]<L[q]) std::swap(p,q);
	for(log=1;(1<<log)<=L[p];++log);--log;

	int ans=-INF;
	for(int i=log;i>=0;--i)
		if(L[p]-(1<<i)>=L[q]) { ans=std::max(ans,maxcost[p][i]);p=anc[p][i]; }

	if(p==q) return ans;

	for(int i=log;i>=0;--i)
		if(anc[p][i]!=-1&&anc[p][i]!=anc[q][i]) {
			ans=std::max(ans,maxcost[p][i]);p=anc[p][i];
			ans=std::max(ans,maxcost[q][i]);q=anc[q][i];
		}
	ans=std::max(ans,cost[p]);
	ans=std::max(ans,cost[q]);
	return ans;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	int kase=0;
	while(scanf("%d%d",&n,&m)==2&&n&&m) {
		edges.clear();
		FOR(i,0,m) { int u,v,d;scanf("%d%d%d",&u,&v,&d);--u;--v;edges.push_back(Edge(u,v,d)); }
		MST();
		dfs(0,-1,0);
		//FOR(u,0,n) printf("u:%d fa:%d L:%d cost:%d\n",u,fa[u],L[u],cost[u]);
		preprocess();
		if(kase++) puts("");
		scanf("%d",&q);
		while(q--) {
			int u,v;scanf("%d%d",&u,&v);--u;--v;
			printf("%d\n",query(u,v));
		}
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}