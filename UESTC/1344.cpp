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

const int mod=772002+233;
const int maxn=1e6+10;
ll head[maxn<<2],add[maxn<<2];
int in[maxn],n,q;

int L,R,y;

inline void pushdown(int rt,int l,int r) {
	if (head[rt]||add[rt]) {
		head[rt<<1]+=head[rt];add[rt<<1]+=add[rt];
		head[rt<<1|1]+=head[rt]+add[rt]*((r-l)/2+1);add[rt<<1|1]+=add[rt];
		head[rt]=add[rt]=0;
	}
}

void update(int rt,int l,int r) {
	if (l>=L&&r<=R) {
		head[rt]+=y+L-l;
		add[rt]+=-1;
	}
	else {
		pushdown(rt,l,r);
		int m=l+(r-l)/2;
		if (L<=m) update(rt<<1,l,m);
		if (R>m) update(rt<<1|1,m+1,r);
	}
}

int x;
ll query(int rt,int l,int r) {
	if (l==r) return head[rt];
	else {
		pushdown(rt,l,r);
		int m=l+(r-l)/2;
		if (x<=m) return query(rt<<1,l,m);
		else return query(rt<<1|1,m+1,r);
	}
}

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	scanf("%d%d",&n,&q);
	For(i,1,n) scanf("%d",in+i);
	int op;
	FOR(i,0,q) {
		scanf("%d%d",&op,&x);
		if (op==1) {
			scanf("%d",&y);
			L=x;R=std::min(n,L+y-1);
			//printf("L:%d R:%d y:%d\n",L,R,y);
			update(1,1,n);
			//For(i,1,n) { x=i;printf("ans[%d]=%lld\n",i,query(1,1,n)); }
		}
		else {
			//printf("q:%lld in:%d\n",query(1,1,n),in[x]);
			printf("%lld\n",(query(1,1,n)+in[x])%mod);
		}
	}


#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}