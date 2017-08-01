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

const int INF=1e9;
const int maxn=105;
int in[maxn][maxn],r[maxn],c[maxn],n,m,in2[maxn][maxn],r2[maxn],c2[maxn];

int getall(int x,int rc,int in[][maxn]) {
	int min=INF;
	if (!rc) For(i,1,m) min=std::min(in[x][i],min);
	else For(i,1,n) min=std::min(in[i][x],min);
	return min;
}

void change(int x,int rc,int cnt,int in[][maxn]) {
	if (!rc) For(i,1,m) in[x][i]-=cnt;
	else For(i,1,n) in[i][x]-=cnt;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	scanf("%d%d",&n,&m);
	For(i,1,n) For(j,1,m) { scanf("%d",in[i]+j);in2[i][j]=in[i][j]; }
	For(i,1,n) { int x=getall(i,0,in);change(i,0,x,in);r[i]=x; }
	For(i,1,m) { int x=getall(i,1,in);change(i,1,x,in);c[i]=x; }
	For(i,1,m) { int x=getall(i,1,in2);change(i,1,x,in2);c2[i]=x; }
	For(i,1,n) { int x=getall(i,0,in2);change(i,0,x,in2);r2[i]=x; }
	bool ans=true;
	For(i,1,n) For(j,1,m) if (in[i][j]) ans=false;
	if (ans) {
		int res=0,re2=0;
		For(i,1,n) { res+=r[i];re2+=r2[i]; }For(i,1,m) { res+=c[i];re2+=c2[i]; }
		printf("%d\n",std::min(res,re2));
		if (res<=re2) {
			For(i,1,n) while (r[i]) { printf("row %d\n",i);--r[i]; }
			For(i,1,m) while (c[i]) { printf("col %d\n",i);--c[i]; }
		}
		else {
			For(i,1,n) while (r2[i]) { printf("row %d\n",i);--r2[i]; }
			For(i,1,m) while (c2[i]) { printf("col %d\n",i);--c2[i]; }
		}
	}
	else puts("-1");

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}