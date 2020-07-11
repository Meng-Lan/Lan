#include<bits/stdc++.h>
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
#define PA(name,init,len) cout<<#name"["<<(len-init)<<"]=";FOR(_,init,len) cout<<name[_]<<" \n"[_==(len-1)];
#define Pa(name,init,len) cout<<#name"["<<(len-init+1)<<"]=";For(_,init,len) cout<<name[_]<<" \n"[_==(len)];
#define PV(name) cout<<#name"="<<name<<'\n';

const int maxn=2e3+10;
const int mod=1e9+7;
ll f[maxn],invf[maxn];

ll qpow(ll a,ll b){
	ll ret=1;
	while(b){
		if(b&1) ret=ret*a%mod;
		b>>=1;
		a=a*a%mod;
	}
	return ret;
}

void init(){
	f[0]=1;
	FOR(i,1,maxn) f[i]=f[i-1]*i%mod;
	invf[maxn-1]=qpow(f[maxn-1],mod-2);
	for(int i=maxn-2;i>=0;--i) invf[i]=invf[i+1]*(i+1)%mod;
}

ll C(int n,int m){return f[n]*invf[m]%mod*invf[n-m]%mod;}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	init();
	int n,m;
	while(scanf("%d%d",&n,&m)==2){
		ll ans=(C(n+m,n)*C(n+m,n)%mod-C(n+m,m-1)*C(n+m,n-1)%mod+mod)%mod;
		printf("%lld\n",ans);
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
