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

std::map<int,P> m;
const int maxn=1<<13;
int cnt[maxn],n,in[30];

int c2i(char c) { return c-'A'; }

int main() {
#ifdef MengLan
	int Beginning=clock();
#else
	freopen("jurassic.in","r",stdin);
	freopen("jurassic.out","w",stdout);
#endif // MengLan

	FOR(i,1,maxn) cnt[i]=cnt[i>>1]+(i&1);
	cin>>n;
	FOR(i,0,n) {
		std::string s;cin>>s;
		FOR(j,0,s.size()) in[i]^=1<<c2i(s[j]);
		//printf("%d\n",in[i]);
	}
	int l=n/2+(n&1),r=n-l;
	//PV(l);PV(r);
	int ans=0,use=0;
	m[0]=P(0,0);
	FOR(i,1,(1<<l)) {
		int t=0;
		FOR(j,0,l) if(i&(1<<j)) t^=in[j];
		if(cnt[i]>m[t].fi) m[t]=P(cnt[i],i);
		//if(t==0&&cnt[i]>ans) ans=cnt[i],use=i;
	}
	FOR(i,0,(1<<r)) {
		int t=0;
		FOR(j,0,r) if(i&(1<<j)) t^=in[j+l];
		if(m.count(t)&&m[t].fi+cnt[i]>ans) ans=m[t].fi+cnt[i],use=m[t].se|(i<<l);
	}
	printf("%d\n",ans);
	FOR(i,0,n) if(use&(1<<i)) printf("%d ",i+1);puts("");

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}
