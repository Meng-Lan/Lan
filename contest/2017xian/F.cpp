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
#define fi first
#define se second
#define pb push_back
#define is insert
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
ll gcd(ll a,ll b) { return b?gcd(b,a%b):a; }
ll lcm(ll a,ll b) { return a/gcd(a,b)*b; }

const ll mod=998244353LL;
const int maxm=1e4+10;
ll qpow(ll a,ll b) {
	ll ans=1;
	while(b) {
		if(b&1) ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
ll f[maxm],invf[maxm];
ll n,m;

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	f[0]=1;
	FOR(i,1,maxm) f[i]=f[i-1]*i%mod;
	invf[maxm-1]=qpow(f[maxm-1],mod-2);
	for(int i=maxm-2;i>=0;--i) invf[i]=invf[i+1]*(i+1)%mod;
	while(cin>>n>>m) {
		if((n&1)^(m&1)) { puts("0");continue; }
		if(m>n) { puts("0");continue; }
		if(m==0) { puts("998244352");continue; }
		ll ans=1;
		for(ll i=n-m+2;i<=n+m-2;i+=2) { ans*=i;ans%=mod; }
		ans=ans*n%mod;
		ll k=1;
		For(i,1,m) { k=k*i%mod; }
		ll x=qpow(k,mod-2);
		ans=ans*x%mod;
		if(((n-m)/2)&1) ans=(mod-ans)%mod;
		cout<<ans<<endl;
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}
