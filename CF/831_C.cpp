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
#include<bitset>
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

const int maxn=2e3+5;
int a[maxn],b[maxn],n,k,vis[maxn*maxn*4],kase;
std::bitset<maxn*maxn*4> ans;

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	++kase;
	scanf("%d%d",&k,&n);
	FOR(i,0,k) { scanf("%d",a+i);if (i) a[i]+=a[i-1]; }
	FOR(i,0,n) { scanf("%d",b+i);b[i]+=maxn*maxn*2;vis[b[i]]=kase; }
	FOR(i,0,k-n+1) FOR(j,0,n) {
		int init=b[j]-a[i];
		//printf("i:%d j:%d init:%d\n",i,j,init);
		if (!ans[init]) {
			int l=i,cnt=0;++kase;int *p=vis+init+a[l];//printf("init+a[l]:%d *p:%d kase:%d bool:%d %d %d n:%d\n",init+a[l],*p,kase,l<n,(*p)>0,(*p)!=kase,n);
			while (l<k) { if ((*p)>0&&(*p)!=kase) { ++cnt;(*p)=kase; }++l;if (l<k)p=vis+init+a[l]; }
			//printf("cnt:%d l:%d\n",cnt,l);
			if (cnt==n) { ans[init]=1; }
		}
	}
	printf("%d\n",ans.count());


#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}