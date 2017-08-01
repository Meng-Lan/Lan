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

const int maxn=1e3+10;
int l[maxn],r[maxn],gap[maxn],d[maxn][maxn*5],n,sum,suml,sumr;

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	scanf("%d",&n);
	FOR(i,0,n) { scanf("%d%d",l+i,r+i);suml+=l[i];sumr+=r[i]; }
	if (suml>sumr) {
		std::swap(suml,sumr);
		FOR(i,0,n) std::swap(l[i],r[i]);
	}
	FOR(i,0,n) gap[i]=r[i]-l[i];
	std::sort(gap,gap+n);std::reverse(gap,gap+n);
	//FOR(i,0,n) printf("#%d l:%d r:%d gap:%d\n",i,l[i],r[i],gap[i]);
	memset(d,0x3f,sizeof(d));d[0][0]=0;
	For(i,1,n) {
		FOR(j,0,maxn*5) d[i][j]=d[i-1][j];
		FOR(j,0,maxn*5-5) if (j>=-gap[i-1]) d[i][j+gap[i-1]]=std::min(d[i-1][j]+1,d[i][j+gap[i-1]]);
	}

	sum=(suml+sumr)/2-suml;
	int tmp=0,ans=maxn;
	FOR(j,0,maxn*5-5) if (std::abs(sum-j)<tmp&&d[n][j]<maxn||std::abs(sum-j)==tmp&&d[n][j]<ans) { tmp=std::abs(sum-j);ans=d[n][j]; }
	printf("%d\n",ans);

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}