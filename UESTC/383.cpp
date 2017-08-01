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

const int maxn=1e4+10;
const int maxk=1e6+10;
int n,m,k;
int c[maxn];
struct Edge {
	int u,v;
	void input() { scanf("%d%d",&u,&v); }
	bool operator<(const Edge &rhs)const { return u<rhs.u||u==rhs.u&&v<rhs.v; }
}edges[maxk];

inline int lowbit(int x) { return x&-x; }

void add(int x) {
	while (x<=m) {
		c[x]++;x+=lowbit(x);
	}
}

int sum(int x) {
	int res=0;
	while (x) {
		res+=c[x];x-=lowbit(x);
	}
	return res;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	int T;scanf("%d",&T);
	For(kase,1,T) {
		scanf("%d%d%d",&n,&m,&k);
		FOR(i,0,k) edges[i].input();
		std::sort(edges,edges+k);
		ll ans=0;memset(c,0,sizeof(c));
		//FOR(i,0,k) printf("#%d u:%d v:%d\n",i,edges[i].u,edges[i].v);
		FOR(i,0,k) {
			ans+=sum(m)-sum(edges[i].v);
			add(edges[i].v);
		}
		printf("Test case %d: %lld\n",kase,ans);
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}