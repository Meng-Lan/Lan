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

const int maxn=25;
int d[maxn][maxn],n,m,q;
struct Lan {
	int s,t,l,r;
	void input() { scanf("%d%d%d%d",&s,&t,&l,&r); }
	bool operator<(const Lan &rhs)const { return l<rhs.l||l==rhs.l&&r<rhs.r; }
}in[maxn],t[maxn];

int bitcount(int x) { return x?bitcount(x>>1)+(x&1):0; }

bool check(int bit) {
	int len=0;
	FOR(i,0,q) if(bit&(1<<i)) t[len++]=in[i];
	std::sort(t,t+len);
	do {
		int b=0,stop=1;
		bool ok=true;
		FOR(i,0,len) {
			b+=d[stop][t[i].s];
			if (b<t[i].l) b=t[i].l;
			b+=d[t[i].s][t[i].t];
			if (b>t[i].r) ok=false;
			stop=t[i].t;
		}
		if(ok) return ok;
	}while(std::next_permutation(t,t+len));
	return false;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	scanf("%d%d%d",&n,&m,&q);
	memset(d,0x3f,sizeof(d));
	For(i,1,n) d[i][i]=0;
	FOR(i,0,m) {
		int u,v,c;scanf("%d%d%d",&u,&v,&c);
		d[u][v]=std::min(d[u][v],c);
	}
	For(k,1,n) For(i,1,n) For(j,1,n) d[i][j]=std::min(d[i][j],d[i][k]+d[k][j]);
	FOR(i,0,q) in[i].input();
	int ans=0;
	FOR(i,1,(1<<q)) if (check(i)) {
		int len=0;FOR(j,0,q) if (i&(1<<j)) ++len;
		ans=std::max(ans,len);
	}
	cout<<ans<<endl;


#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}