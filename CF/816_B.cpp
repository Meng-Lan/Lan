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

const int maxn=2e5+10;
const int N=2e5;
int add[maxn<<2],sum[maxn<<2],cnt[maxn<<2],n,k,q;

void maintain(int rt,int l,int r) {
	if (l==r) { cnt[rt]+=add[rt];add[rt]=0;sum[rt]=cnt[rt]>=k; }
	else {
		int m=l+(r-l)/2;
		sum[rt]=(add[rt]+cnt[rt<<1])>=k?(m-l+1):sum[rt<<1];
		sum[rt]+=(add[rt]+cnt[rt<<1|1])>=k?r-m:sum[rt<<1|1];
		cnt[rt]=std::min(cnt[rt<<1],cnt[rt<<1|1])+add[rt];
	}
}

void pushdowm(int rt) {
	add[rt<<1]+=add[rt];add[rt<<1|1]+=add[rt];add[rt]=0;
}

int L,R;
void update(int rt,int l,int r) {
	if (L<=l&&r<=R) add[rt]+=1;
	else {
		int m=l+(r-l)/2;
		pushdowm(rt);
		if (L<=m) update(rt<<1,l,m);else maintain(rt<<1,l,m);
		if (R>m) update(rt<<1|1,m+1,r);else maintain(rt<<1|1,m+1,r);
	}
	maintain(rt,l,r);
}

int query(int rt,int l,int r) {
	if (L<=l&&r<=R) return sum[rt];
	else {
		int m=l+(r-l)/2,res=0;
		pushdowm(rt);
		maintain(rt<<1,l,m);maintain(rt<<1|1,m+1,r);maintain(rt,l,r);
		if (L<=m) res+=query(rt<<1,l,m);
		if (R>m) res+=query(rt<<1|1,m+1,r);
		return res;
	}
}

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	scanf("%d%d%d",&n,&k,&q);
	FOR(i,0,n) { scanf("%d%d",&L,&R);update(1,1,N); }
	FOR(i,0,q) { scanf("%d%d",&L,&R);printf("%d\n",query(1,1,N)); }

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}