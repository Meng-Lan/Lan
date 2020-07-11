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

const int maxn=2e4+10,maxm=5e4+10;
std::vector<int> G[maxn];
int pre[maxn],lowlink[maxn],sccno[maxn],dfs_clock,scc_cnt,n,m,in0[maxn],out0[maxn];
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
		scc_cnt++;
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

		For(i,1,scc_cnt) in0[i]=out0[i]=1;
		FOR(u,0,n) for(auto &v:G[u]) {
			if(sccno[u]!=sccno[v]) in0[sccno[v]]=out0[sccno[u]]=0;
		}
		int a=0,b=0;
		For(i,1,scc_cnt) {
			if(in0[i]) ++a;
			if(out0[i]) ++b;
		}
		int ans=std::max(a,b);
		if(scc_cnt==1) ans=0;
		printf("%d\n",ans);
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}