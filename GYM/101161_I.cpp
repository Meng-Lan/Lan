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

const int INF=1e9;
const int maxn=1e5+10;
const int logn=20;
int n,q,r;
std::vector<int> G[maxn];
int fa[maxn],anc[maxn][logn],L[maxn],size[maxn];

void dfs(int u,int f,int dep) {
	fa[u]=f;L[u]=dep;size[u]=1;
	for(auto &v:G[u]) if(v!=f) dfs(v,u,dep+1),size[u]+=size[v];
}

void preprocess() {
	For(i,1,n) {
		anc[i][0]=fa[i];
		for(int j=1;(1<<j)<n;++j) anc[i][j]=-1;
	}
	for(int j=1;(1<<j)<=n;++j) For(i,1,n) {
		int a=anc[i][j-1];
		anc[i][j]=anc[a][j-1];
	}
}

int query(int p,int q) {
	int tmp,log,i,u=p,v=q;
	if(p==q) return n;
	if(L[p]<L[q]) std::swap(p,q);
	for(log=1;(1<<log)<=L[p];++log);--log;
	for(int i=log;i>=0;--i)
		if(L[p]-(1<<i)>=L[q]) { p=anc[p][i]; }
	if(p==q) {
		if(u==p) return size[v];
		p=u;q=v;
		if(L[p]<L[q]) std::swap(p,q);
		for(int i=log;i>=0;--i)
			if(L[p]-(1<<i)>L[q]) { p=anc[p][i]; }
		return n-size[p];
	}
	for(int i=log;i>=0;--i)
		if(anc[p][i]!=-1&&anc[p][i]!=anc[q][i]) {
			p=anc[p][i];q=anc[q][i];
		}
	return size[v];
}


int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	int T;scanf("%d",&T);
	For(kase,1,T) {
		printf("Case #%d:\n",kase);
		scanf("%d%d%d",&n,&q,&r);
		For(i,1,n) G[i].clear();
		FOR(i,1,n) {
			int u,v;scanf("%d%d",&u,&v);
			G[u].pb(v);G[v].pb(u);
		}
		dfs(1,-1,1);
		preprocess();
		FOR(i,0,q) {
			int s,u;scanf("%d%d",&s,&u);
			if(s==0) { r=u; }
			else {
				printf("%d\n",query(r,u));
			}
		}
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}
