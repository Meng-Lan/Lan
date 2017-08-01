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

const int maxn=2e4+10;
int n,m,in[maxn];
std::vector<int> G[maxn];

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	std::vector<int> v={ 0,0,1,2,3,4,5 };
	int T;scanf("%d",&T);
	while (T--) {
		scanf("%d%d",&n,&m);
		FOR(i,0,n) scanf("%d",in+i);
		FOR(i,0,n) G[i].clear();
		FOR(k,1,n) {
			int t=0;
			while (t<n) { G[k].push_back(in[t]);t+=k; }
			std::sort(G[k].begin(),G[k].end());
			//G[k].resize(std::unique(G[k].begin(),G[k].end())-G[k].begin());
			std::reverse(G[k].begin(),G[k].end());
		}
		FOR(i,0,m) {
			int K,S;scanf("%d%d",&K,&S);
			if (K>=n&&S!=1||K<n&&G[K].size()<S) puts("-1");
			else if(K>=n&&S==1) printf("%d\n",in[0]);
			else printf("%d\n",G[K][S-1]);
		}
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}