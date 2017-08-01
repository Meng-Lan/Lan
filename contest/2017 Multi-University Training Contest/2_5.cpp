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

const int maxn=3e3+10;
int min[maxn][maxn],max[maxn][maxn],f[maxn][maxn],last[maxn];
int in[maxn],n;

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	int T;scanf("%d",&T);
	while(T--) {
		scanf("%d",&n);
		For(i,1,n) { scanf("%d",in+i);min[i][i]=max[i][i]=in[i];f[i][i]=1;last[i]=i; }
		For(i,1,n) For(j,i+1,n) { min[i][j]=std::min(min[i][j-1],in[j]);max[i][j]=std::max(max[i][j-1],in[j]); }
		For(k,2,n) For(i,1,n-k+1) {
			int j=i+k-1;
			if(max[i][j]-min[i][j]+1!=k) f[i][j]=0;
			else {
				if(min[i][j]<min[i][last[i]]) f[i][j]=1;
				else f[i][j]=f[i][last[i]]+f[last[i]+1][j];
				last[i]=j;
			}
		}
		int ans=std::max(1,f[1][n]);
		For(i,1,n) For(j,i,n) if(f[i][j]&&(i==1||f[1][i-1]&&min[1][i-1]==1)) {
			int k=min[i][j],l=max[i][j];
			if(l==n||f[l+1][n]&&max[l+1][n]==n) {
				for(int m=j+1;m<=l;++m) if(min[m][l]==i&&f[m][l])
					ans=std::max(ans,f[1][i-1]+f[j+1][m-1]+f[l+1][n]+2);
			}
		}
		printf("%d\n",ans);
	}


#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}