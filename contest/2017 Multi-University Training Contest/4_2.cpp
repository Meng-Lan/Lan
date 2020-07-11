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

const int maxn=5e4+10;
const int maxm=1e2+10;
int n,m,q,j,k;
int l,r;
char s[maxn],t[maxm];
int f[maxm],pre[maxn],suf[maxn][maxm],c[maxm][26],g[maxm][26],sum[maxn][maxm];
ll ans;

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	int T;scanf("%d",&T);
	while(T--) {
		scanf("%d%d%d%s%s",&n,&m,&q,s+1,t+1);
		For(i,1,n) s[i]-='a';For(i,1,m) t[i]-='a';
		f[0]=f[1]=0;j=0;
		For(i,2,m) {
			while(j&&t[i]!=t[j+1]) j=f[j];
			if(t[j+1]==t[i]) ++j;
			f[i]=j;
		}
		FOR(i,0,m) FOR(j,0,26) {
			c[i][j]=0;
			k=i;
			while(k&&t[k+1]!=j) k=f[k];
			if(t[k+1]==j) ++k;
			if(k==m) { c[i][j]=1;k=f[k]; }
			g[i][j]=k;
		}
		k=0;j=0;
		For(i,1,n) {
			k+=c[j][s[i]];
			j=g[j][s[i]];
			pre[i]=pre[i-1]+k;
			FOR(x,0,m) sum[i][x]=sum[i-1][x];
			sum[i][j]++;
		}
		FOR(i,0,m) suf[n+1][i]=0;
		for(int i=n;i;--i) FOR(j,0,m) suf[i][j]=c[j][s[i]]+suf[i+1][g[j][s[i]]];
		for(int i=n;i;--i) FOR(j,0,m) suf[i][j]+=suf[i+1][j];
		while(q--) {
			scanf("%d%d",&l,&r);
			ans=(ll)pre[l]*(n-r+1);
			FOR(i,0,m) ans+=(ll)suf[r][i]*sum[l][i];
			printf("%lld\n",ans);
		}
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}  