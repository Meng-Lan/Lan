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
int v[maxn],n,q;
std::vector<int> G[maxn];
int pre[maxn],dfs_clock,pos[maxn],last[maxn],sz;
struct Lan { int l,r,v; }t[maxn*100];

void dfs(int u) {
	pre[u]=++dfs_clock;
	pos[pre[u]]=u;
	for(auto &v:G[u]) dfs(v);
	last[u]=dfs_clock;
}

int root[maxn];
void build(int &x,int y,int bit,int val) {
	t[++sz]=t[y];t[sz].v++;x=sz;
	if(bit<0) return;
	if(val&(1<<bit)) build(t[x].r,t[y].r,bit-1,val);
	else build(t[x].l,t[y].l,bit-1,val);
}


void query(int x,int y,int bit,int &val) {
	if(bit<0) return;
	int have=(val>>bit)&1;
	//printf("bit:%d have:%d\n",bit,have);
	if(!have) {
		if(t[t[y].r].v-t[t[x].r].v>0) {
			val|=(1<<bit);
			query(t[x].r,t[y].r,bit-1,val);
		}
		else query(t[x].l,t[y].l,bit-1,val);
	}
	else {
		if(t[t[y].l].v-t[t[x].l].v>0) query(t[x].l,t[y].l,bit-1,val);
		else {
			val^=(1<<bit);
			query(t[x].r,t[y].r,bit-1,val);
		}
	}
}

void print(int i,int bit) {
	printf("i:%d bit:%d\n",i,bit);
	if(bit==0) return;
	if(t[i].l) printf("L:%d v:%d\n",t[i].l,t[t[i].l].v),print(t[i].l,bit-1);
	if(t[i].r) printf("RRR:%d v:%d\n",t[i].r,t[t[i].r].v),print(t[i].r,bit-1);
}

void printall() {
	For(i,1,n) print(root[i],30);
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	while(scanf("%d%d",&n,&q)==2) {
		For(i,1,n) scanf("%d",v+i);
		For(i,1,n) G[i].clear();
		For(i,2,n) { int x;scanf("%d",&x);G[x].push_back(i); }
		//memset(pre,0,sizeof(pre));
		//memset(pos,0,sizeof(pos));
		memset(root,0,sizeof(root));
		memset(t,0,sizeof(Lan)*(sz+10));
		dfs_clock=sz=0;
		dfs(1);
		//For(i,1,n) printf("#%d pre:%d pos:%d last:%d\n",i,pre[i],pos[i],last[i]);
		//For(i,1,n) printf("vpos:%d\n",v[pos[i]]);
		For(i,1,n) build(root[i],root[i-1],30,v[pos[i]]);
		//printall();
		FOR(i,0,q) {
			int u,x;scanf("%d%d",&u,&x);
			//printf("u:%d x:%d\n",u,x);
			//printf("pre:%d last:%d\n",pre[u]-1,last[u]);
			query(root[pre[u]-1],root[last[u]],30,x);
			printf("%d\n",x);
		}
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}