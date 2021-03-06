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
const int mod=1e9+7;
int n,m,a[maxn],b[maxn];
int ra[maxn],rb[maxn];
int va[maxn],vb[maxn];
int kase=0;

int bfs(int *a,int *vis,int u,int v) {
	vis[u]=kase;
	return a[u]==v?1:bfs(a,vis,a[u],v)+1;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	while(scanf("%d%d",&n,&m)==2) {
		FOR(i,0,n) scanf("%d",a+i);
		FOR(j,0,m) scanf("%d",b+j);
		memset(ra,0,sizeof(ra));memset(rb,0,sizeof(rb));++kase;
		FOR(i,0,n) if(va[i]!=kase) {
			int len=bfs(a,va,a[i],a[i]);
			ra[len]++;
		}
		FOR(i,0,m) if(vb[i]!=kase) {
			int len=bfs(b,vb,b[i],b[i]);
			rb[len]++;
		}
		ll ans=1;
		For(i,1,n) {
			while(ra[i]--) {
				ll sum=0;
				for(ll j=1;j*j<=i;++j) {
					if(i%j==0) {
						if(j*j==i) { sum+=(ll)rb[j]*j;sum%=mod; }
						else {
							sum+=(ll)rb[j]*j;sum%=mod;
							sum+=(ll)rb[i/j]*(i/j);sum%=mod;
						}
					}
				}
				ans*=sum;ans%=mod;
			}
		}
		printf("Case #%d: %lld\n",kase,ans);
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}