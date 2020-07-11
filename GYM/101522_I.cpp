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

const int maxn=1e6+10;
int in[maxn],n;
ll sum,ans;

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	scanf("%d",&n);
	FOR(i,0,n) {
		scanf("%d",in+i);
		if(i) sum+=std::abs(in[i]-in[i-1]);
	}
	ans=sum;
	FOR(i,0,n) {
		ll diff=0;
		if(i) diff-=std::abs(in[i]-in[i-1]);
		if(i<n-1) diff-=std::abs(in[i+1]-in[i]);
		if(i) diff+=std::abs(-in[i]-in[i-1]);
		if(i<n-1) diff+=std::abs(in[i+1]+in[i]);
		ans=std::min(ans,sum+diff);
	}
	P df(0,0);
	FOR(i,1,n) {
		ll diff=0;
		diff-=std::abs(in[i]-in[i-1]);
		diff+=std::abs(-in[i]-in[i-1]);
		if(diff<df.fi) {
			df.se=df.fi;
			df.fi=diff;
		}
		else if(diff<df.se) df.se=diff;
		ans=std::min(ans,sum+df.fi+df.se);
	}
	printf("%lld\n",ans);

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}
