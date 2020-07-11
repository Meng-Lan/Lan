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
/*namespace IO {
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
inline int read() { static int x;read(x);return x; }*/
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

const int maxn=3e4+10;
const int INF=1e9;
struct Lan {
	int max;ll sum;
	Lan(int max,ll sum) :max(max),sum(sum) {}
	Lan() :sum(0),max(0) {}
}t[maxn<<2];
int n,fa[maxn],top[maxn],dep[maxn],sz[maxn],pos[maxn],w[maxn],cnt,q;
std::vector<int> G[maxn];

void init(int u) {
	sz[u]=1;dep[u]=dep[fa[u]]+1;
	FOR(i,0,G[u].size()) if(G[u][i]!=fa[u]) {
		int &v=G[u][i];fa[v]=u;init(v);sz[u]+=sz[v];
	}
}
void init2(int u) {
	int nxt=0,size=0;pos[u]=++cnt;
	FOR(i,0,G[u].size())
		if(G[u][i]!=fa[u]&&sz[G[u][i]]>size) { nxt=G[u][i];size=sz[G[u][i]]; }
	if(!nxt) return;
	top[nxt]=top[u];init2(nxt);
	FOR(i,0,G[u].size()) if(G[u][i]!=fa[u]&&G[u][i]!=nxt)
		top[G[u][i]]=G[u][i],init2(G[u][i]);
}

void pushup(int rt) {
	int l=rt<<1,r=rt<<1|1;
	t[rt].max=std::max(t[l].max,t[r].max);
	t[rt].sum=t[l].sum+t[r].sum;
}

void build(int rt,int l,int r) {
	if(l==r) { t[rt]=Lan(w[l],w[l]);return; }
	int m=l+(r-l)/2;
	build(rt<<1,l,m);
	build(rt<<1|1,m+1,r);
	pushup(rt);
}

void change(int rt,int l,int r,int x,int y) {
	if(l==r) { t[rt].sum=t[rt].max=y;return; }
	int m=l+(r-l)/2;
	if(x<=m) change(rt<<1,l,m,x,y);
	else if(x>m) change(rt<<1|1,m+1,r,x,y);
	pushup(rt);
}

int querySum(int rt,int l,int r,int L,int R) {
	if(L<=l&&r<=R) return t[rt].sum;
	int m=l+(r-l)/2;
	int sum=0;
	if(L<=m) sum+=querySum(rt<<1,l,m,L,R);
	if(R>m) sum+=querySum(rt<<1|1,m+1,r,L,R);
	return sum;
}

int queryMax(int rt,int l,int r,int L,int R) {
	if(L<=l&&r<=R) return t[rt].max;
	int m=l+(r-l)/2;
	int max=-INF;
	if(L<=m) max=std::max(max,queryMax(rt<<1,l,m,L,R));
	if(R>m) max=std::max(max,queryMax(rt<<1|1,m+1,r,L,R));
	return max;
}

int query(int x,int y,int f) {
	int tot=f?0:-INF;
	while(top[x]!=top[y]) {
		if(dep[top[x]]>dep[top[y]]) std::swap(x,y);
		if(f) tot+=querySum(1,1,cnt,pos[top[y]],pos[y]);
		else tot=std::max(tot,queryMax(1,1,cnt,pos[top[y]],pos[y]));
		y=fa[top[y]];
	}
	if(pos[x]>pos[y]) std::swap(x,y);
	if(f) tot+=querySum(1,1,cnt,pos[x],pos[y]);
	else tot=std::max(tot,queryMax(1,1,cnt,pos[x],pos[y]));
	return tot;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	freopen("in","r",stdin);
	freopen("out","w",stdout);
#endif // MengLan

	scanf("%d",&n);
	FOR(i,1,n) {
		int u,v;scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	init(1);top[1]=1;init2(1);
	For(i,1,n) scanf("%d",&w[pos[i]]);
	build(1,1,cnt);
	//printf("cnt:%d\n",cnt);
	scanf("%d",&q);
	FOR(i,0,q) {
		char cmd[10];int x,y;
		scanf(" %s%d%d",cmd,&x,&y);
		if(!strcmp(cmd,"CHANGE")) change(1,1,cnt,pos[x],y);
		else if(!strcmp(cmd,"QMAX")) printf("%d\n",query(x,y,0));
		else printf("%d\n",query(x,y,1));
	}


#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}