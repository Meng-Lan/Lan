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
const int maxq=maxn<<2;
int in[maxq],n,q,sum[maxq<<2],addv[maxq<<2];
P inv[maxq];
struct Event {
	int t,l,r;
	void input() { scanf("%d%d%d",&t,&l,&r); }
	Event(int t,int l,int r) :t(t),l(l),r(r) {}
	Event() :Event(0,0,0) {}
}evt[maxn];

void maintain(int o,int L,int R) {
	if (addv[o]) sum[o]=addv[o]*(inv[R].second-inv[L].first+1);
	else if (L < R) sum[o]=sum[o<<1]+sum[o<<1|1];
}

void pushdown(int o) {
	if (addv[o]) { addv[o<<1]=addv[o<<1|1]=addv[o]; addv[o]=0; }
}

int L,R;
void update(int o,int l,int r) {
	if (inv[l].first>=L&&inv[r].second<=R) addv[o]=1;
	else {
		int m=l+(r-l)/2;
		pushdown(o);
		if (L<=inv[m].second) update(o<<1,l,m); else maintain(o<<1,l,m);
		if (R > inv[m].second) update(o<<1|1,m+1,r); else maintain(o<<1|1,m+1,r);
	}
	maintain(o,l,r);
	//printf("L:%d R:%d sum:%d add:%d\n", inv[l].first, inv[r].second, sum[o], addv[o]);
}

int query(int o,int l,int r) {
	if (addv[o]) return std::min(R,inv[r].second)-std::max(L,inv[l].first)+1;
	if (inv[l].first>=L&&inv[r].second<=R) return sum[o];
	int m=l+(r-l)/2;
	int _sum=0;
	if (L<=inv[m].second) _sum+=query(o<<1,l,m);
	if (R > inv[m].second) _sum+=query(o<<1|1,m+1,r);
	//printf("L:%d R:%d sum:%d\n", inv[l].first, inv[r].second, _sum);
	return _sum;
}

void print(int o,int l,int r) {
	if (l==r) printf("L:%d R:%d sum:%d add:%d\n",inv[l].first,inv[r].second,sum[o],addv[o]);
	else {
		int m=l+(r-l)/2;
		print(o<<1,l,m);
		print(o<<1|1,m+1,r);
		printf("L:%d R:%d sum:%d add:%d\n",inv[l].first,inv[r].second,sum[o],addv[o]);
	}
}

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	scanf("%d%d",&n,&q);
	int cnt=0; in[cnt++]=1; in[cnt++]=n;
	FOR(i,0,q) {
		evt[i].input();
		in[cnt++]=evt[i].l; in[cnt++]=evt[i].r;
	}
	std::sort(in,in+cnt);
	cnt=std::unique(in,in+cnt)-in;
	int tot=0; inv[tot++]=P(in[0],in[0]);
	FOR(i,1,cnt) {
		if (in[i]-in[i-1] > 1) inv[tot++]=P(in[i-1]+1,in[i]-1);
		inv[tot++]=P(in[i],in[i]);
	}
	//FOR(i, 0, tot) printf("inv[%d].f:%d .s:%d\n", i, inv[i].first, inv[i].second);
	FOR(i,0,q) {
		if (evt[i].t==1) { L=evt[i].l; R=evt[i].r; update(1,0,tot-1); }
		else { L=evt[i].l; R=evt[i].r; printf("%d\n",(R-L+1)-query(1,0,tot-1)); }
		//printf("in enevt[%d]:\n", i);
		//print(1, 0, tot - 1);
	}


#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}