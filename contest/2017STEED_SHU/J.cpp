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

const int MOD=1000000007;
const int maxn=1e4+10;
int n,vis[maxn];
std::vector<int> pri=Eratosthenes(maxn,vis);

int phi(int x) {
	ll ans=x,tx=x;
	for(auto &i:pri) if (x%i==0) {
		ans=ans/i*(i-1);
		while (x%i==0) x/=i;
	}
	if(x>1) ans=ans/x*(x-1);
	return (ll)ans*(n/tx)%MOD;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	//FOR(i,0,10) cout<<pri[i]<<endl;
	int T;scanf("%d",&T);
	while (T--) {
		scanf("%d",&n);
		ll ans=(ll)n*(n+1)/2%MOD;
		FOR(i,1,233) ans=(ans-phi(i)+MOD)%MOD;
		For(i,n-233+1,n) ans=(ans-phi(i)+MOD)%MOD;
		cout<<ans<<'\n';
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}