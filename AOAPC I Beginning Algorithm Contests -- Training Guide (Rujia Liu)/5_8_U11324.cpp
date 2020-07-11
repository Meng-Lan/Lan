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

const int maxn=1e3+10,maxm=5e4+10;
int n,m;
std::vector<int> G[maxn];
int pre[maxn],sccno[maxn],lowlink[maxn],dfs_clock,scc_cnt;
std::stack<int> s;

void dfs(int u) {
	pre[u]=lowlink[u]=++dfs_clock;
	s.push(u);
	for(auto &v:G[u]) {
		if(!pre[v]) {
			dfs(v);
			lowlink[u]=std::min(lowlink[u],lowlink[v]);
		}
		else if(!sccno[v]) {
			lowlink[u]=std::min(lowlink[u],pre[v]);
		}
	}
	if(lowlink[u]==pre[u]) {
		++scc_cnt;
		for(;;) {
			int x=s.top();s.pop();
			sccno[x]=scc_cnt;
			if(x==u) break;
		}
	}
}

void find_scc(int n) {
	memset(pre,0,sizeof(pre));
	memset(sccno,0,sizeof(sccno));
	dfs_clock=scc_cnt=0;
	FOR(i,0,n) if(!pre[i]) dfs(i);
}

std::vector<int> G2[maxn];
int d[maxn],cnt[maxn];

int dp(int u) {
	if(d[u]>=0) return d[u];
	if(G2[u].empty()) return d[u]=cnt[u];
	int &ans=d[u];ans=0;
	for(auto &v:G2[u]) ans=std::max(ans,dp(v));
	return ans+=cnt[u];
}

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	int T;scanf("%d",&T);
	while(T--) {
		scanf("%d%d",&n,&m);
		For(i,0,n) G[i].clear();
		FOR(i,0,m) { int u,v;scanf("%d%d",&u,&v);--u;--v;G[u].push_back(v); }
		find_scc(n);
		For(i,0,scc_cnt) G2[i].clear();
		memset(d,-1,sizeof(d));
		memset(cnt,0,sizeof(cnt));
		FOR(u,0,n) {
			cnt[sccno[u]]++;
			for(auto &v:G[u]) {
				if(sccno[u]!=sccno[v]) { G2[sccno[u]].push_back(sccno[v]); }
			}
		}
		int ans=0;
		For(i,1,scc_cnt) ans=std::max(ans,dp(i));
		printf("%d\n",ans);
	}


#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}