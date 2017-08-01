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

const int maxn=4e5+10;
int fa[maxn],n,m,k,in[maxn],vis[maxn],ans[maxn];
std::vector<int> G[maxn];
P edges[maxn];

int find(int x) { return fa[x]=x==fa[x]?x:find(fa[x]); }

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	scanf("%d%d",&n,&m);
	FOR(i,0,n) fa[i]=i;
	FOR(i,0,m) {
		scanf("%d%d",&edges[i].first,&edges[i].second);
		G[edges[i].first].push_back(i);
		G[edges[i].second].push_back(i);
	}
	scanf("%d",&k);
	FOR(i,0,k) {
		scanf("%d",in+i);vis[in[i]]=1;
	}
	FOR(i,0,m) {
		P &e=edges[i];
		if (!vis[e.first]&&!vis[e.second]) {
			int u=find(e.first),v=find(e.second);
			fa[u]=v;
		}
	}
	FOR(i,0,n) if(!vis[i]&&find(i)==i) ++ans[k];
	for (int i=k-1;i>=0;--i) {
		int x=0;vis[in[i]]=0;
		for (auto &t:G[in[i]]) {
			P &e=edges[t];
			if (!vis[e.first]&&!vis[e.second]) {
				int u=find(e.first),v=find(e.second);
				if (u!=v) { fa[u]=v;++x; }
			}
		}
		ans[i]=ans[i+1]-x+1;
	}
	For(i,0,k) printf("%d\n",ans[i]);


#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}