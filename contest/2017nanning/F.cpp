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

const int maxn=1e3+10;
typedef std::pair<P,P> PP;
int n;
std::vector<int> x;
struct Lan {
	int y1,y2,add;
};
std::vector<PP> in;
std::vector<Lan> add[maxn<<1];
int find(int v) { return std::lower_bound(x.begin(),x.end(),v)-x.begin(); }
const int M=1e6+10;
int t[M<<2],sum[M<<2];

void build() { memset(t,0,sizeof(t));memset(sum,0,sizeof(sum)); }

inline void pushdown(int rt) {
	if(t[rt]) { t[rt<<1]+=t[rt];t[rt<<1|1]+=t[rt];t[rt]=0; }
}
inline void maintain(int rt,int l,int r) {
	if(t[rt]>0) sum[rt]=r-l+1;
	else sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}

void update(int rt,int l,int r,int L,int R,int v) {
	if(L<=l&&r<=R) {
		t[rt]+=v;
		if(t[rt]>0) sum[rt]=r-l+1;
		else sum[rt]=sum[rt<<1]+sum[rt<<1|1];
		//printf("l:%d r:%d sum:%d\n",l,r,sum[rt]);
		return;
	}
	pushdown(rt);
	int m=l+(r-l)/2;
	if(L<=m) update(rt<<1,l,m,L,R,v);else maintain(rt<<1,l,m);
	if(R>m) update(rt<<1|1,m+1,r,L,R,v);else maintain(rt<<1|1,m+1,r);
	maintain(rt,l,r);
	//printf("l:%d r:%d sum:%d\n",l,r,sum[rt]);
}

int query(int rt,int l,int r) {
	if(t[rt]>0) return r-l+1;
	return sum[rt];
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	while(scanf("%d",&n)==1&&n) {
		x.clear();in.clear();
		for(auto &v:add) v.clear();
		FOR(i,0,n) {
			int a,b,c,d;scanf("%d%d%d%d",&a,&b,&c,&d);
			in.pb({ P(a,b),P(c,d) });
			x.pb(a);x.pb(c);
		}
		std::sort(x.begin(),x.end());
		x.erase(std::unique(x.begin(),x.end()),x.end());
		FOR(i,0,n) {
			add[find(in[i].fi.fi)].pb({ in[i].fi.se+1,in[i].se.se,1 });
			add[find(in[i].se.fi)].pb({ in[i].fi.se+1,in[i].se.se,-1 });
		}
		build();
		int ans=0;
		const int mx=1e6;
		for(int i=0;i<x.size();++i) {
			if(i) ans+=query(1,0,mx)*(x[i]-x[i-1]);
			//printf("i:%d ans:%d\n",i,ans);
			for(auto &v:add[i]) {
				update(1,0,mx,v.y1,v.y2,v.add);
				//printf("x:%d y1:%d y2:%d v:%d\n",x[i],v.y1,v.y2,v.add);
				//printf("sum:%d\n",query(1,0,mx));
			}
		}
		printf("%d\n",ans);
	}
	puts("*");

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}
