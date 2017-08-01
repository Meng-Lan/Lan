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
const int maxm=1e5+10;
struct Lan {
	int u,v,c;
	Lan(int u,int v,int c) :u(u),v(v),c(c) {}
	Lan() :Lan(0,0,0) {}
	void input() { scanf("%d%d%d",&u,&v,&c); }
	bool operator<(const Lan &rhs)const { return c<rhs.c; }
}edges[maxm];
int fa[maxn],n,m;

int find(int x) { return fa[x]=x==fa[x]?x:find(fa[x]); }

bool MST(int &ans) {
	std::sort(edges,edges+m);
	int cnt=0;
	FOR(i,0,m) {
		if (cnt==n-1) break;
		Lan &e=edges[i];
		int x=find(e.u),y=find(e.v);
		if (x!=y) { ++cnt;fa[x]=y; ans=e.c; }
	}
	return cnt==n-1;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	scanf("%d%d",&n,&m);For(i,1,n) fa[i]=i;
	FOR(i,0,m) edges[i].input();
	int ans=0;
	if(MST(ans)) printf("%d\n",ans);
	else puts("-1");


#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}