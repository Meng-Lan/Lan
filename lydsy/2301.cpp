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
ll mu[maxn],pri[maxn],tot;
bool vis[maxn];
int a,b,c,d,k;

void init() {
	mu[1]=1;
	FOR(i,2,maxn) {
		if (!vis[i]) { pri[tot++]=i;mu[i]=-1; }
		for (int j=0;j<tot&&i*pri[j]<maxn;++j) {
			vis[i*pri[j]]=true;
			if (i%pri[j]==0) { mu[i*pri[j]]=0;break; }
			mu[i*pri[j]]=mu[i]*-1;
		}
	}
	FOR(i,1,maxn) mu[i]+=mu[i-1];
}

ll cal(int n,int m,int k) {
	ll ans=0;
	if(n>m) std::swap(n,m);
	n/=k;m/=k;
	int last;
	for (int i=1;i<=n;i=last+1) {
		last=std::min(n/(n/i),m/(m/i));
		ans+=(mu[last]-mu[i-1])*(n/i)*(m/i);
	}
	return ans;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	init();
	int T;scanf("%d",&T);
	while (T--) {
		scanf("%d%d%d%d%d",&a,&b,&c,&d,&k);
		printf("%lld\n",cal(b,d,k)-cal(a-1,d,k)-cal(b,c-1,k)+cal(a-1,c-1,k));
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}