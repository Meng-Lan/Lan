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

namespace IO {
	inline char getchar() {
		static const int BUFSIZE=10000001;
		static char buf[BUFSIZE],*begin,*end;
		if(begin==end) {
			begin=buf;
			end=buf+fread(buf,1,BUFSIZE,stdin);
			if(begin==end) return -1;
		}
		return *begin++;
	}

	bool read(int &in) {
		int c;
		while(!isalnum(c=getchar())&&c!=-1);
		if(c==-1) return false;
		in=c-'0';
		while(isalnum(c=getchar())) { in*=10;in+=c-'0'; }
		return true;
	}
}

bool read(int &in) {
	int c;
	while(!isalnum(c=getchar())&&c!=-1);
	if(c==-1) return false;
	in=c-'0';
	while(isalnum(c=getchar())) { in*=10;in+=c-'0'; }
	return true;
}

const int mod=1e9+7;
const int maxn=1e6+10;
struct Node {
	int l,r,id;
	bool operator<(const Node &rhs)const { return l<rhs.l||l==rhs.l&&r>rhs.r; }
}in[maxn];
int n;
ll f[maxn],invf[maxn];

ll qpow(ll a,ll b) {
	ll ans=1;
	while(b) {
		if(b&1) ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}

inline void init() {
	f[0]=1;
	FOR(i,1,maxn) f[i]=f[i-1]*i%mod;
	invf[maxn-1]=qpow(f[maxn-1],mod-2);
	for(int i=maxn-2;i>=0;--i) invf[i]=invf[i+1]*(i+1)%mod;
}

inline ll C(ll n,ll m) {
	ll ans=1;
	if(n<m) return 0;
	ans=ans*f[n]%mod*invf[m]%mod*invf[n-m]%mod;
	return ans;
}

int idx;
inline ll dfs(int l,int r) {
	if(l>r) return 1;
	if(in[idx].l!=l||in[idx].r!=r) return 0;
	Node &now=in[idx++];
	return (dfs(now.l,now.id-1)*C(now.r-now.l,now.id-now.l)%mod)*dfs(now.id+1,now.r)%mod;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	int kase=0;
	init();
	while(IO::read(n)) {
		For(i,1,n) in[i].id=i;
		For(i,1,n) IO::read(in[i].l);
		For(i,1,n) IO::read(in[i].r);
		//For(i,1,n) printf("%d%c",in[i].l,i!=n?' ':'\n');
		//For(i,1,n) printf("%d%c",in[i].r,i!=n?' ':'\n');
		std::sort(in+1,in+n+1);
		//For(i,1,n) printf("#%d l:%d r:%d\n",i,in[i].l,in[i].r);
		idx=1;
		//printf("%d\n",n);
		printf("Case #%d: %lld\n",++kase,dfs(1,n));
	}


#ifdef MengLan
	//printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}