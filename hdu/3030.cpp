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

const int mod=1000000007;
const int maxn=5e5+10;
ll n,m,X,Y,Z,in[maxn],A[maxn],t[maxn];
ll c[maxn];

inline int lowbit(int x) { return x&-x; }

ll sum(int x) {
	ll res=0;
	while (x>0) {
		res+=c[x];x-=lowbit(x);
	}
	return res;
}

void add(int x,ll add) {
	while (x<=n) {
		c[x]=(c[x]+add)%mod;x+=lowbit(x);
	}
}

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	int T;scanf("%d",&T);
	For(kase,1,T) {
		scanf("%I64d%I64d%I64d%I64d%I64d",&n,&m,&X,&Y,&Z);
		FOR(i,0,m) scanf("%I64d",A+i);
		FOR(i,0,n) { t[i+1]=in[i]=A[i%m];A[i%m]=(X*A[i%m]%Z+Y*(i+1)%Z)%Z; }
		//FOR(i,0,n) { printf("#%d %d\n",i,in[i]); }
		std::sort(t+1,t+1+n);
		int len=std::unique(t+1,t+n+1)-(t+1);
		ll ans=0;
		memset(c,0,sizeof(c));
		FOR(i,0,n) {
			int f=std::lower_bound(t+1,t+1+n,in[i])-t;
			ans+=sum(f-1)+1;ans%=mod;
			add(f,sum(f-1)+1);
		}
		printf("Case #%d: %I64d\n",kase,ans);
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}