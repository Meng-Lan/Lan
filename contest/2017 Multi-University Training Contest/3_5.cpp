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
#include<bitset>
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

const int maxn=1e6+10;
struct Edge {
	int u,v,c;
	void set(int _u,int _v,int _c) { u=_u;v=_v;c=_c; }
}edges[maxn<<1];
int n,k,cnt[maxn],sz;
ll ans;
std::vector<int> G[maxn];
struct Lan {
	int idx,ans;
	bool operator<(const Lan &rhs)const { return ans>rhs.ans; }
}node[maxn];

inline void addEdge(int u,int v,int c) {
	edges[sz].set(u,v,c);
	G[u].push_back(sz);
	++sz;
	edges[sz].set(v,u,c);
	G[v].push_back(sz);
	++sz;
}

ll dfs(int u,int f,int c) {
	cnt[u]=1;
	for(auto &t:G[u]) {
		Edge &e=edges[t];
		if(e.v!=f) cnt[u]+=dfs(e.v,u,e.c);
	}
	//printf("u:%d c:%d cnt:%d\n",u,c,cnt[u]);
	ans+=(ll)std::min(k,cnt[u])*c;
	return cnt[u];
}


int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	while(scanf("%d%d",&n,&k)==2) {
		For(i,1,n) { G[i].clear(); }
		sz=0,ans=0;
		FOR(i,1,n) {
			int u,v,c;scanf("%d%d%d",&u,&v,&c);
			addEdge(u,v,c);
		}
		dfs(1,-1,0);
		printf("%lld\n",ans);
	}


#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}