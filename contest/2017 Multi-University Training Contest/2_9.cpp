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
int a[maxn],sum[maxn],n,mu[maxn],vis[maxn],p[maxn],sz;

void init() {
	mu[1]=1;
	FOR(i,2,maxn) {
		if(!vis[i]) { p[sz++]=i;mu[i]=-1; }
		for(int j=0;j<sz&&p[j]*i<maxn;++j) {
			vis[i*p[j]]=true;
			if(i%p[j]==0) { mu[i*p[j]]=0;break; }
			mu[i*p[j]]=-mu[i];
		}
	}
}

long long qpow(long long x,long long y) {
	if(x<=1)return 1;
	long long res=1;
	while(y) {
		if(y&1)res=res*x%mod;
		y>>=1;
		x=x * x %mod;
	}return res;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	init();
	int T;scanf("%d",&T);
	For(kase,1,T) {
		memset(sum,0,sizeof(sum));
		scanf("%d",&n);
		int min=maxn,max=0;
		For(i,1,n) { scanf("%d",a+i);sum[a[i]]++; min=std::min(min,a[i]);max=std::max(max,a[i]); }
		For(i,1,max) sum[i]+=sum[i-1];
		ll ans=0;
		For(i,2,min) if(mu[i]) {
			ll cnt=-mu[i];
			//printf("i:%d cnt:%lld\n",i,cnt);
			int len=max/i;
			for(int j=1;j<=len;++j) {
				int l=i*j,r=std::min(max,i*j+i-1);
				//printf("l:%d r:%d j:%d count:%d\n",l,r,j,sum[r]-sum[l-1]);
				cnt=cnt*qpow(j,sum[r]-sum[l-1])%mod;
				//printf("cnt:%lld\n",cnt);
			}
			ans+=cnt;
		}
		printf("Case #%d: %lld\n",kase,(ans%mod+mod)%mod);
	}


#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}