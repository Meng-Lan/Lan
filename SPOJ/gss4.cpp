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

const int maxn=1e5+10;
ll in[maxn],sum[maxn<<2],n,q;

void build(int rt,int l,int r) {
	if(l==r) { sum[rt]=in[l];return; }
	int m=l+(r-l)/2;
	build(rt<<1,l,m);
	build(rt<<1|1,m+1,r);
	sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}

void update(int rt,int l,int r,int x,int y) {
	if(sum[rt]==r-l+1) return;
	if(l==r) { sum[rt]=sqrt(sum[rt]);return; }
	int m=l+(r-l)/2;
	if(x<=m) update(rt<<1,l,m,x,y);
	if(y>m) update(rt<<1|1,m+1,r,x,y);
	sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}

ll query(int rt,int l,int r,int x,int y) {
	if(x<=l&&r<=y) return sum[rt];
	int m=l+(r-l)/2;
	ll ls,rs;
	if(x<=m) ls=query(rt<<1,l,m,x,y);
	if(y>m) rs=query(rt<<1|1,m+1,r,x,y);
	if(x<=m&&m<y) return ls+rs;
	if(x<=m)  return ls;
	if(y>m) return rs;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	int kase=0;
	while(scanf("%lld",&n)==1&&n) {
		printf("Case #%d:\n",++kase);
		For(i,1,n) scanf("%lld",in+i);
		build(1,1,n);
		scanf("%lld",&q);
		FOR(i,0,q) {
			int op,x,y;
			scanf("%d%d%d",&op,&x,&y);
			if(x>y) std::swap(x,y);
			if(op==0) update(1,1,n,x,y);
			else printf("%lld\n",query(1,1,n,x,y));
		}
		puts("");
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}