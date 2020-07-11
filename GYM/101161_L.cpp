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

const int maxn=1e5+10;
P coor[maxn];
std::vector<int> v[maxn];
std::vector<P> vp[maxn];
int n,m,vis[maxn],in[maxn];
const int INF=1e9;

void dfs(int s) {
	if(vis[s]) return;
	vis[s]=true;
	FOR(i,0,v[s].size()) {
		int t=v[s][i];
		if(vis[t]) continue;
		coor[t].fi=coor[s].fi+vp[s][i].fi;
		coor[t].se=coor[s].se+vp[s][i].se;
	}
	FOR(i,0,v[s].size()) {
		dfs(v[s][i]);
	}
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	scanf("%d%d",&n,&m);
	FOR(i,0,m) {
		int a,b,x,y;scanf("%d%d%d%d",&a,&b,&x,&y);
		v[a].pb(b);vp[a].pb({ x,y });
		v[b].pb(a);vp[b].pb({ -x,-y });
		in[a]=1;in[b]=1;
	}
	For(i,1,n) assert(in[i]==1);
	dfs(1);
	For(i,1,n) assert(vis[i]);
	P mi(0,0),mx(0,0);
	For(i,1,n) {
		mi.fi=std::min(mi.fi,coor[i].fi);
		mi.se=std::min(mi.se,coor[i].se);
		mx.fi=std::max(mx.fi,coor[i].fi);
		mx.se=std::max(mx.se,coor[i].se);
	}
	P fl(mi.fi+INF,mi.se+INF);
	For(i,1,n) printf("%d %d\n",coor[i].fi-fl.fi,coor[i].se-fl.se);

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}
