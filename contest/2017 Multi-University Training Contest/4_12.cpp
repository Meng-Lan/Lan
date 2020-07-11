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

const int MOD=998244353;
const int maxn=2e3+10;
int a[maxn],b[maxn],g[maxn][maxn][2],h[maxn][maxn][2],n,m,ans;

inline void up(int &x,int y) { x=x+y<MOD?x+y:x+y-MOD; }

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	int T;scanf("%d",&T);
	while(T--) {
		scanf("%d%d",&n,&m);
		For(i,1,n) scanf("%d",a+i);
		For(i,1,m) scanf("%d",b+i);
		For(i,0,n) For(j,0,m) For(k,0,1) g[i][j][k]=h[i][j][k]=0;
		ans=0;
		For(i,1,n) For(j,1,m) For(k,0,1) {
			if(a[i]==b[j]) {
				int t=h[i][j][k^1];
				if(!k) up(t,1);
				up(g[i+1][j][k],t);
				up(ans,t);
			}
			if(g[i][j][k]) {
				up(g[i+1][j][k],g[i][j][k]);
				if(!k) { if(a[i]>b[j]) up(h[i][j+1][k],g[i][j][k]); }
				else { if(a[i]<b[j]) up(h[i][j+1][k],g[i][j][k]); }
			}
			up(h[i][j+1][k],h[i][j][k]);
		}
		printf("%d\n",ans);
	}


#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}