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

const int maxn=5e4+10;
int n,vis[maxn],mu[maxn],pri[maxn],tot;

void init() {
	mu[1]=1;
	FOR(i,2,maxn) {
		if (!vis[i]) { pri[tot++]=i;mu[i]=-1; }
		for (int j=0;j<tot&&pri[j]*i<maxn;++j) {
			vis[i*pri[j]]=1;
			if (i%pri[j]==0) { mu[i*pri[j]]=0;break; }
			else mu[i*pri[j]]=-mu[i];
		}
	}
}

bool check(ll m) {
	ll ans=0,len=floor(sqrt(m));
	For(i,1,len) ans+=m/(i*i)*mu[i];
	return ans>=n;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	init();
	//For(i,1,36) printf("mu[%d]=%d\n",i,mu[i]);
	int T;scanf("%d",&T);
	while (T--) {
		scanf("%d",&n);
		ll l=0,r=1ll*maxn*maxn;
		while (l<r) {
			ll m=l+(r-l)/2;
			if (check(m)) r=m;
			else l=m+1;
		}
		cout<<l<<endl;
	}


#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}