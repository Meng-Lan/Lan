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
struct Edge {
	int u,v,vis;
	Edge(int u=0,int v=0,int vis=0) :u(u),v(v),vis(vis) {}
}edges[maxn];
std::vector<int> G[maxn];
int n;
std::vector<Edge> ans;

void euler(int u) {
	for(auto &e:G[u]) if(!edges[e].vis) {
		int v=edges[e].u==u?edges[e].v:edges[e].u;
		edges[e].vis=1;
		euler(v);
		ans.push_back(Edge(u,v));
	}
}

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	int T;scanf("%d",&T);
	For(kase,1,T) {
		if(kase>1) puts("");
		scanf("%d",&n);
		for(auto &t:G) t.clear();
		int start=-1;
		FOR(i,0,n) { int u,v;scanf("%d%d",&u,&v);edges[i]=Edge(u,v);G[u].push_back(i);G[v].push_back(i);start=u; }
		int solved=0;
		for(auto &t:G) if(t.size()&1) ++solved;
		ans.clear();
		if(!solved) {
			euler(start);
			if(ans.size()!=n||ans[0].v!=ans[ans.size()-1].u) solved++;
		}
		if(!solved) {
			printf("Case #%d\n",kase);
			for(int i=ans.size()-1;i>=0;--i) printf("%d %d\n",ans[i].u,ans[i].v);
		}
		else printf("Case #%d\nsome beads may be lost\n",kase);
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}