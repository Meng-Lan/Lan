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

const int maxn=2e5+10;
const int lgn=20;
int c[maxn],root[maxn],n,kase;
std::vector<int> G[maxn];
int ls[maxn*lgn],rs[maxn*lgn],sum[maxn*lgn],tot;

void insert(int &rt,int l,int r,int x,int y) {
	if(!rt) rt=++tot;
	if(l==r) { sum[rt]=y; return; }
	int m=l+(r-l)/2;
	if(x<=m) insert(ls[rt],l,m,x,y);
	else insert(rs[rt],m+1,r,x,y);
	sum[rt]=sum[ls[rt]]+sum[rs[rt]];
}

int query(int rt,int l,int r,int k) {
	if(!rt) return 0;
	if(l==r) return sum[rt];
	int m=l+(r-l)/2;
	if(k<=m) return query(ls[rt],l,m,k);
	else return query(rs[rt],m+1,r,k);
}

int merge(int u,int v) {
	if(!u||!v) return u|v;
	ls[u]=merge(ls[u],ls[v]);
	rs[u]=merge(rs[u],rs[v]);
	sum[u]+=sum[v];
	return u;
}

ll de;
int sz[maxn],vis[maxn];
void dfs(int u,int fa) {
	sz[u]=1;
	int step=0;
	for(auto &v:G[u]) {
		if(v!=fa) {
			dfs(v,u);
			sz[u]+=sz[v];
			int qr=query(root[v],1,n,c[u]);
			int tsz=sz[v]-qr;
			de+=(ll)tsz*(tsz-1)/2;
			step+=qr;
		}
	}
	insert(root[u],1,n,c[u],sz[u]-step);
	for(auto &v:G[u]) {
		if(v!=fa) {
			merge(root[u],root[v]);
		}
	}
}

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	while(scanf("%d",&n)==1&&n) {
		memset(root,0,sizeof(root));memset(ls,0,sizeof(ls));memset(rs,0,sizeof(rs));
		++kase;tot=0;de=0;
		For(i,0,n) G[i].clear();
		For(i,1,n) { scanf("%d",c+i);vis[c[i]]=kase; }
		FOR(i,1,n) { int u,v;scanf("%d%d",&u,&v);G[u].push_back(v);G[v].push_back(u); }
		dfs(1,0);
		For(i,1,n) if(vis[i]==kase&&i!=c[1]) {
			int qr=query(root[1],1,n,i);
			int tsz=n-qr;
			de+=(ll)tsz*(tsz-1)/2;
		}
		int cnt=0;
		For(i,1,n) if(vis[i]==kase) ++cnt;
		ll ans=(ll)cnt*n*(n-1)/2-de;
		printf("Case #%d: %lld\n",kase,ans);
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}