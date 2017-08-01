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
int m=10;
int xyz[15][15][15],n,q;
ll len[maxn];

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	int T;scanf("%d",&T);
	while (T--) {
		scanf("%d%d",&n,&q);
		memset(xyz,0,sizeof(xyz));
		int x,y,z;
		FOR(i,0,n) { scanf("%d%d%d",&x,&y,&z);xyz[x][y][z]++; }
		memset(len,0,sizeof(len));
		For(i,0,m) For(j,0,m) For(k,0,m) For(l,0,m) For(q,0,m) For(w,0,m) {
			int t=std::abs(i-l)+std::abs(j-q)+std::abs(k-w);
			if (t==0) len[t]+=1ll*xyz[i][j][k]*(xyz[l][q][w]-1);
			else len[t]+=1ll*xyz[i][j][k]*xyz[l][q][w];
		}
		FOR(i,1,maxn) len[i]+=len[i-1];
		FOR(i,0,q) {
			int t;scanf("%d",&t);
			if (t>=maxn) printf("%lld\n",len[maxn-1]/2);
			else printf("%lld\n",len[t]/2);
		}
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}