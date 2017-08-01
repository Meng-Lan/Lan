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
	if (n-r < r) r=n-r;
	ll ansn=1,ansr=1;
	for (ll i=n-r+1; i<=n; ++i) ansn*=i;
	for (ll j=1; j<=r; ++j) ansr*=j;
	return ansn/ansr;
}
ll gcd(ll a,ll b) { return b?gcd(b,a%b):a; }
ll lcm(ll a,ll b) { return a/gcd(a,b)*b; }
std::vector<int> Eratosthenes(const int len,int *vis) {
	memset(vis,0,sizeof(int)*len);
	std::vector<int> prime;
	int m=(int)sqrt(len+0.5);
	For(i,2,m) if (!vis[i]) for (int j=i*i; j < len; j+=i) vis[j]=1;
	FOR(i,2,len) if (!vis[i]) prime.push_back(i);
	return prime;
}
void phi_table(int n,int *phi) {
	For(i,2,n) phi[i]=0;
	phi[1]=1;
	For(i,2,n) if (!phi[i])
		for (int j=i; j<=n; j+=i) {
			if (!phi[j]) phi[j]=j;
			phi[j]=phi[j]/i*(i-1);
		}
}

const int maxn=1e5+10;
struct Edge { int v,next; }edges[maxn<<1];
int head[maxn],fa[maxn],tot,n;
ll ans;
std::map<int,int> S[maxn],*p[maxn];

inline void add(int u,int v) {
	edges[tot].v=v;edges[tot].next=head[u];head[u]=tot++;
}

inline void union_map(std::map<int,int> *&l,std::map<int,int> *&r) {
	if (l->size()>r->size()) std::swap(l,r);
	for (const auto &t:(*l)) {
		(*r)[t.first]+=t.second;
	}
	l->clear();
}

void dfs(int u,int val) {
	(*p[u])[val]++;
	for (int i=head[u];~i;i=edges[i].next) {
		int v=edges[i].v;
		if (v==fa[u]) continue;
		fa[v]=u;
		dfs(v,val^v);
		std::map<int,int>::iterator it=p[v]->begin();
		while(it!=p[v]->end()) {
			int s=it->first^u;
			if (p[u]->count(s)) ans+=(ll)it->second*(*p[u])[s];
			++it;
		}
		union_map(p[v],p[u]);
	}
}

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	memset(head,-1,sizeof(head));
	scanf("%d",&n);
	int u,v;
	FOR(i,1,n) {
		scanf("%d%d",&u,&v);
		add(u,v);add(v,u);
	}
	For(i,1,n) p[i]=S+i;
	dfs(1,1);
	printf("%lld\n",ans);

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}