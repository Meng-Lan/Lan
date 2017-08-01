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
	if(n-r < r) r=n-r;
	ll ansn=1,ansr=1;
	for(ll i=n-r+1; i<=n; ++i) ansn*=i;
	for(ll j=1; j<=r; ++j) ansr*=j;
	return ansn/ansr;
}
ll gcd(ll a,ll b) { return b?gcd(b,a%b):a; }
ll lcm(ll a,ll b) { return a/gcd(a,b)*b; }
std::vector<int> Eratosthenes(const int len,int *vis) {
	memset(vis,0,sizeof(int)*len);
	std::vector<int> prime;
	int m=(int)sqrt(len+0.5);
	For(i,2,m) if(!vis[i]) for(int j=i*i; j < len; j+=i) vis[j]=1;
	FOR(i,2,len) if(!vis[i]) prime.push_back(i);
	return prime;
}
void phi_table(int n,int *phi) {
	For(i,2,n) phi[i]=0;
	phi[1]=1;
	For(i,2,n) if(!phi[i])
		for(int j=i; j<=n; j+=i) {
			if(!phi[j]) phi[j]=j;
			phi[j]=phi[j]/i*(i-1);
		}
}

const int maxn=1e7+10;
int n,m;
unsigned a[maxn];
struct Node {
	unsigned val,id;
	void read() { scanf("%u",&val); }
	bool operator<(const Node &rhs)const { return val>rhs.val||val==rhs.val&&id<rhs.id; }
}b[105];

unsigned x,y,z,A,B,C,ans[105];
unsigned rng61() {
	unsigned t;
	x^=x<<16;
	x^=x>>5;
	x^=x<<1;
	t=x;
	x=y;
	y=z;
	z=t ^ x ^ y;
	return z;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	int kase=0;
	while(scanf("%d%d%u%u%u",&n,&m,&A,&B,&C)==5) {
		FOR(i,0,m) { b[i].read();b[i].id=i; }
		std::sort(b,b+m);
		//FOR(i,0,m) printf("b[%d] v:%u id:%u\n",i,b[i].val,b[i].id);
		x=A,y=B,z=C;
		FOR(i,0,n) {//a[i]=rng61();
			unsigned t;
			x^=x<<16;
			x^=x>>5;
			x^=x<<1;
			t=x;
			x=y;
			y=z;
			a[i]=z=t ^ x ^ y;
		}
		//FOR(i,0,n) printf("%u ",a[i]);puts("");
		FOR(i,0,m) {
			if(i&&b[i].val==b[i-1].val) { ans[b[i].id]=ans[b[i-1].id];continue; }
			std::nth_element(a,a+b[i].val,a+n);
			ans[b[i].id]=a[b[i].val];
			n=b[i].val;
		}
		printf("Case #%d:",++kase);
		FOR(i,0,m) printf(" %u",ans[i]);puts("");
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}