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

const int maxn=1e5+10;
struct Lan {
	int l,r,add;
}tree[maxn<<2];
int n,q,in[maxn];

inline void pushdowm(int rt) {
	Lan &now=tree[rt],&l=tree[rt<<1],&r=tree[rt<<1|1];
	l.l=std::min(l.l,l.add+now.l);r.l=std::min(r.l,r.add+now.l);now.l=0;
	l.r=std::max(l.r,l.add+now.r);r.r=std::max(r.r,r.add+now.r);now.r=0;
	l.add+=now.add;r.add+=now.add;now.add=0;
}

int L,R,x;
void update(int rt,int l,int r) {	
	if (L<=l&&r<=R) { Lan &now=tree[rt];now.add+=x;now.l=std::min(now.l,now.add);now.r=std::max(now.r,now.add);return; }
	pushdowm(rt);
	int m=l+(r-l)/2;
	if(L<=m) update(rt<<1,l,m);
	if(R>m) update(rt<<1|1,m+1,r);
}

void query(int rt,int l,int r) {
	if (l==r) { L=tree[rt].l;R=tree[rt].r;return; }
	pushdowm(rt);
	int m=l+(r-l)/2;
	if(x<=m) query(rt<<1,l,m);
	else query(rt<<1|1,m+1,r);
}

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	int T;scanf("%d",&T);
	while (T--) {
		scanf("%d%d",&n,&q);
		memset(tree,0,sizeof(tree));
		For(i,1,n) scanf("%d",in+i);
		FOR(i,0,q) {
			int op;scanf("%d",&op);
			if (op==1) {scanf("%d%d%d",&L,&R,&x);update(1,1,n);}
			else {scanf("%d",&x);query(1,1,n);printf("%d\n",std::max(std::abs(L+in[x]),std::abs(R+in[x])));}
		}
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}