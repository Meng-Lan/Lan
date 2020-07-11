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
namespace IO {
	inline char getchar() {
		static const int BUFSIZE=5201314;
		static char buf[BUFSIZE],*begin,*end;
		if(begin==end) {
			begin=buf;
			end=buf+fread(buf,1,BUFSIZE,stdin);
			if(begin==end) return -1;
		}
		return *begin++;
	}
}
inline void read(int &in) {
	int c,symbol=1;
	while(isspace(c=IO::getchar()));
	if(c=='-') { in=0;symbol=-1; }
	else in=c-'0';
	while(isdigit(c=IO::getchar())) { in*=10;in+=c-'0'; }
	in*=symbol;
}
inline int read() { static int x;read(x);return x; }
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

const int maxn=1<<20;
int pre[maxn],pos[maxn],n,m,k;
ll ans[maxn],cnt[maxn],ANS;
struct Lan {
	int id,l,r;
	bool operator<(const Lan &rhs)const { if(pos[l]==pos[rhs.l]) return r<rhs.r;return pos[l]<pos[rhs.l]; }
}q[maxn];

void add(int idx) {
	ANS+=cnt[pre[idx]^k];
	++cnt[pre[idx]];
}

void del(int idx) {
	--cnt[pre[idx]];
	ANS-=cnt[pre[idx]^k];
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	scanf("%d%d%d",&n,&m,&k);
	int sz=sqrt(n);
	For(i,1,n) { scanf("%d",pre+i);pre[i]^=pre[i-1];pos[i]=i/sz; }
	For(i,1,m) {
		scanf("%d%d",&q[i].l,&q[i].r);q[i].id=i;
	}
	std::sort(q+1,q+1+m);
	cnt[0]=1;
	int L=1,R=0;
	For(i,1,m) {
		while(L<q[i].l) del(L-1),++L;
		while(L>q[i].l) { --L;add(L-1); }
		while(R<q[i].r) add(++R);
		while(R>q[i].r) del(R--);
		ans[q[i].id]=ANS;
	}
	For(i,1,m) printf("%I64d\n",ans[i]);

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}