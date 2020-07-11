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
int in[maxn][maxn],n,m;
std::vector<int> G[maxn];
struct Edge {
	int u,v;
	Edge(int u,int v) :u(u),v(v) {}
	Edge() :Edge(0,0) {}
};

int pre[maxn],iscut[maxn],bccno[maxn],dfs_clock,bcc_cnt;
std::stack<Edge> S;
std::vector<int> bcc[maxn];
int dfs(int u,int fa) {
	int lowu=pre[u]=++dfs_clock;
	int child=0;
	for(const auto &v:G[u]) {
		Edge e(u,v);
		if(!pre[v]) {
			S.push(e);
			++child;
			int lowv=dfs(v,u);
			lowu=std::min(lowu,lowv);
			if(lowv>=pre[u]) {
				iscut[u]=true;
				bcc_cnt++;
				bcc[bcc_cnt].clear();
				for(;;) {
					assert(!S.empty());
					Edge x=S.top();S.pop();
					if(bccno[x.u]!=bcc_cnt) { bcc[bcc_cnt].push_back(x.u);bccno[x.u]=bcc_cnt; }
					if(bccno[x.v]!=bcc_cnt) { bcc[bcc_cnt].push_back(x.v);bccno[x.v]=bcc_cnt; }
					if(x.u==u&&x.v==v) break;
				}
			}
		}
		else if(pre[v]<pre[u]&&v!=fa) {
			S.push(e);
			lowu=std::min(lowu,pre[v]);
		}
	}
	if(fa<0&&child==1) iscut[u]=false;
	return lowu;
}

void find_bcc(int n) {
	memset(pre,0,sizeof(pre));
	memset(iscut,0,sizeof(iscut));
	memset(bccno,0,sizeof(bccno));
	dfs_clock=bcc_cnt=0;
	FOR(i,0,n) if(!pre[i]) dfs(i,-1);
}

int odd[maxn],color[maxn];
bool bipartite(int u,int b) {
	for(const auto &v:G[u]) {
		if(bccno[v]!=b) continue;
		if(color[u]==color[v]) return false;
		if(!color[v]) {
			color[v]=3-color[u];
			if(!bipartite(v,b)) return false;
		}
	}
	return true;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	while(scanf("%d%d",&n,&m)==2&&n&&m) {
		memset(in,0,sizeof(in));
		For(i,0,n) G[i].clear();
		FOR(i,0,m) { int u,v;scanf("%d%d",&u,&v);--u;--v;in[u][v]=in[v][u]=1; }
		FOR(u,0,n) FOR(v,u+1,n) if(!in[u][v]) {
			G[u].push_back(v);G[v].push_back(u);
		}

		find_bcc(n);

		memset(odd,0,sizeof(odd));
		For(i,1,bcc_cnt) {
			memset(color,0,sizeof(color));
			for(const auto &j:bcc[i]) bccno[j]=i;
			assert(!bcc[i].empty());
			int u=bcc[i][0];
			color[u]=1;
			if(!bipartite(u,i)) {
				for(const auto &j:bcc[i]) odd[j]=1;
			}
		}
		int ans=n;
		FOR(i,0,n) if(odd[i]) --ans;
		printf("%d\n",ans);
	}


#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}