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

const int maxn=1e5+10;
int n,m,cost[maxn],val[maxn],vlen;
std::vector<int> G[maxn];
int root[maxn],sz;
struct Node { int l,r;ll sum; }t[maxn*30];

int anc[maxn][20],L[maxn];
void dfs(int u,int fa) {
	anc[u][0]=fa;
	for(auto &v:G[u]) if(v!=fa) { L[v]=L[u]+1;dfs(v,u); }
}
void preprocess() {
	memset(anc,0,sizeof(anc));
	L[1]=1;
	dfs(1,0);
	for(int j=1;(1<<j)<=n;++j) For(i,1,n)
		if(anc[i][j-1]!=0) {
			int a=anc[i][j-1];
			anc[i][j]=anc[a][j-1];
		}
}
int query(int p,int q) {
	int log,tmp,i;
	if(L[p]<L[q]) std::swap(p,q);
	for(log=1;(1<<log)<=L[p];++log);--log;
	for(int i=log;i>=0;--i) if(L[p]-(1<<i)>=L[q]) p=anc[p][i];
	if(p==q) return p;
	for(int i=log;i>=0;--i)
		if(anc[p][i]!=0&&anc[p][i]!=anc[q][i]) {
			p=anc[p][i];q=anc[q][i];
		}
	return anc[p][0];
}

int ID(int x) {
	int idx=std::lower_bound(val,val+1+vlen,x)-val;
	//printf("x:%d idx:%d v:%d\n",x,idx,val[idx]);
	return idx;
}

void update(int l,int r,int &x,int y,int pos,int val) {
	t[++sz]=t[y];t[sz].sum+=val;x=sz;
	if(l==r) return;
	int m=l+(r-l)/2;
	if(pos<=m) update(l,m,t[x].l,t[y].l,pos,val);
	else update(m+1,r,t[x].r,t[y].r,pos,val);
}

int tot=0,idx[maxn];
void dfs2(int u,int fa) {
	idx[u]=++tot;
	//printf("u:%d idx:%d ID(u):%d cost[u]:%d\n",u,idx[u],ID(cost[u]),cost[u]);
	update(1,vlen,root[tot],root[idx[fa]],ID(cost[u]),cost[u]);
	for(auto &v:G[u]) if(v!=fa) dfs2(v,u);
}

ll query(int l,int r,int x,int y,int L,int R) {
	//printf("query: l:%d r:%d x:%d y:%d L:%d R:%d sum:%lld\n",l,r,x,y,L,R,t[y].sum-t[x].sum);
	if(L<=l&&r<=R) return t[y].sum-t[x].sum;
	int m=l+(r-l)/2;
	ll sum=0;
	if(L<=m) sum+=query(l,m,t[x].l,t[y].l,L,R);
	if(R>m) sum+=query(m+1,r,t[x].r,t[y].r,L,R);
	return sum;
}

void print(int rt,int l,int r) {
	printf("rt:%d l:%d r:%d sum:%d\n",rt,l,r,t[rt].sum);
	if(l==r) return;
	int m=l+(r-l)/2;
	print(t[rt].l,l,m);
	print(t[rt].r,m+1,r);
}

void print(int u,int fa) {
	printf("tree u:%d idx:%d sum:%d\n",u,idx[u],t[root[idx[u]]].sum);
	print(root[idx[u]],1,vlen);
	for(auto &v:G[u]) if(v!=fa) print(v,u);
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	while(scanf("%d%d",&n,&m)==2) {
		memset(val,0,sizeof(val));
		For(i,1,n) scanf("%d",cost+i),val[i]=cost[i];
		std::sort(val+1,val+1+n);
		vlen=std::unique(val+1,val+1+n)-(val+1);
		//printf("vlen:%d\n",vlen);
		For(i,1,n) G[i].resize(0);
		FOR(i,1,n) {
			int u,v;scanf("%d%d",&u,&v);
			G[u].push_back(v);G[v].push_back(u);
		}
		preprocess();
		memset(t,0,sizeof(t));
		memset(root,0,sizeof(root));
		memset(idx,0,sizeof(idx));
		tot=sz=0;dfs2(1,0);
		//print(1,0);
		//int rt=root[idx[1]];
		//For(i,1,vlen) printf("i:%d val:%d\n",i,val[i]);
		For(i,1,m) {
			int s,t,a,b;scanf("%d%d%d%d",&s,&t,&a,&b);
			int lca=query(s,t);
			//printf("s:%d t:%d lca:%d\n",s,t,lca);
			int l=ID(a),r=ID(b);
			if(val[r]!=b) --r;
			//printf("a:%d l:%d b:%d r:%d\n",a,l,b,r);
			//printf("rt:%d root:%d sum:%lld\n",rt,idx[s],query(1,vlen,0,root[idx[s]],l,r));
			//printf("rt:%d root:%d sum:%lld\n",rt,idx[t],query(1,vlen,0,root[idx[t]],l,r));
			//printf("rt:%d root:%d sum:%lld\n",rt,idx[lca],query(1,vlen,0,root[idx[lca]],l,r));
			//printf("rt:%d root:%d sum:%lld\n",rt,idx[anc[lca][0]],query(1,vlen,0,root[idx[anc[lca][0]]],l,r));
			//ll ans=0;
			ll ans=query(1,vlen,0,root[idx[s]],l,r)+query(1,vlen,0,root[idx[t]],l,r)
				-query(1,vlen,0,root[idx[lca]],l,r)-query(1,vlen,0,root[idx[anc[lca][0]]],l,r);
			printf("%lld%c",ans," \n"[i==m]);
		}
	}


#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}