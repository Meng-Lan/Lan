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

const int maxn=5e5+10;
const int bit=2;
int ch[maxn*32][bit],val[maxn*32],sz;
int in[maxn],n;
int sum[maxn][33][bit];
ll ssum[maxn*33];
ll ans;

void init() { sz=1;memset(ch[0],0,sizeof(ch[0])); ssum[0]=0;}

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	int T;scanf("%d",&T);
	while(T--) {
		scanf("%d",&n);
		For(i,1,n) scanf("%d",in+i);
		memset(sum[0],0,sizeof(sum[0]));init();
		For(i,1,n) For(j,0,29) { For(k,0,1) sum[i][j][k]=sum[i-1][j][k];sum[i][j][((in[i]>>j)&1)]++; }
		ans=0;
		for(int i=n;i>=1;--i) {
			int u=0;
			for(int j=29;j>=0;--j) {
				int c=(in[i]>>j)&1;
				if(ch[u][c^1]) ans+=ssum[ch[u][c^1]]-(ll)val[ch[u][c^1]]*sum[i][j][c];
				if(!ch[u][c]) break;
				u=ch[u][c];
			}
			u=0;
			for(int j=29;j>=0;--j) {
				int c=(in[i]>>j)&1;
				if(!ch[u][c]) {
					memset(ch[sz],0,sizeof(ch[sz]));
					val[sz]=0;ssum[sz]=0;
					ch[u][c]=sz++;
				}
				u=ch[u][c];
				ssum[u]+=sum[i-1][j][c^1];
				++val[u];
			}
		}
		printf("%lld\n",ans);
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}