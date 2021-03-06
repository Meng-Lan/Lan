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
#define PA(name,init,len) cout<<#name"["<<(len-init)<<"]=";FOR(_,init,len) cout<<name[_]<<" \n"[_==(len-1)];
#define Pa(name,init,len) cout<<#name"["<<(len-init+1)<<"]=";For(_,init,len) cout<<name[_]<<" \n"[_==(len)];
#define PV(name) cout<<#name"="<<name<<'\n';

const int mod=1e9+7;
const int maxn=61*202;
int f[maxn],invf[maxn];

inline void up(int &x,int y) { x+=y;x>=mod?x-=mod:0; }

int fpow(int x,int y) {
	int ans=1,res=x;
	while(y) {
		if(y&1) ans=1LL*ans*res%mod;
		y>>=1;
		res=1LL*res*res%mod;
	}
	return ans;
}

void init() {
	f[0]=1;
	FOR(i,1,maxn) f[i]=1LL*f[i-1]*i%mod;
	invf[maxn-1]=fpow(f[maxn-1],mod-2);
	for(int i=maxn-2;i>=0;--i) invf[i]=1LL*invf[i+1]*(i+1)%mod;
}

inline int C(int n,int m) {
	if(n<m||m<0) return 0;
	return 1LL*f[n]*invf[m]%mod*invf[n-m]%mod;
}

int cal(int sum,int n,int m) {
	int ans=0;
	For(i,0,n) {
		int res=1LL*C(n,i)*C(sum-i*(m+1)+n-1,n-1)%mod;
		if(i&1) res=mod-res;
		up(ans,res);
	}
	return ans;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	init();
	int n,m;
	while(cin>>n>>m) {
		if(!n&&!m) break;
		int ans=0;
		For(i,0,m) up(ans,cal((n-1)*i,n-1,m));
		ans=1LL*ans*n%mod;
		cout<<ans<<'\n';
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}
