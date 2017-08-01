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
const int maxn=14;
int n,adj[maxn],rej[maxn],c[1<<maxn];
struct Lan {
	int adj,c;
	Lan(int adj,int c) :adj(adj),c(c) {}
	Lan() :Lan(0,INF) {}
	bool operator<(const Lan &rhs)const { return c<rhs.c; }
}d[1<<maxn];

inline int getcost(int s1,int s2) {
	int i=0,cnt=0,t=std::max(c[s1],c[s2]);
	while (s1) { cnt+=(s1&1)*c[rej[i]&s2]; s1>>=1;++i;}
	return cnt*t;
}

inline Lan join(int s1,int s2) {
	if (d[s1].adj&s2) {
		Lan &l=d[s1],&r=d[s2];
		//int cost=c[((l.rej|s1)^s1)&s2]*std::max(c[s1],c[s2]);
		return Lan(l.adj|r.adj,l.c+r.c+getcost(s1,s2));
	}
	else return Lan();
}

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	FOR(s,1,1<<maxn) if(s&(s-1)) c[s]=c[s^(s&(s-1))]+c[s&(s-1)];else c[s]=1;
	//FOR(i,1,1<<4) printf("#%d %d\n",i,c[i]);
	int T;scanf("%d",&T);
	while (T--) {
		scanf("%d",&n);
		FOR(i,0,n) { adj[i]=0;FOR(j,0,n) { int x;scanf("%d",&x);adj[i]|=x<<j; } }
		FOR(i,0,n) { rej[i]=0;FOR(j,0,n) { int x;scanf("%d",&x);rej[i]|=x<<j; } }
		FOR(i,0,1<<n) d[i]=Lan();
		FOR(i,0,n) d[1<<i]=Lan(adj[i],0);
		FOR(s,1,1<<n) {
			for (int s0=s&(s-1);s0;s0=(s0-1)&s) d[s]=std::min(d[s],join(s0,s-s0));
		}
		printf("%d\n",d[(1<<n)-1].c);
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}