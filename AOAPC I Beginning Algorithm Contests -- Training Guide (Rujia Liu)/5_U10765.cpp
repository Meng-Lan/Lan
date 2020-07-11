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

const int maxn=1e4+10;
std::vector<int> G[maxn];
int pre[maxn],cut[maxn],low[maxn],rnk[maxn];
int dfs_clock,n,m;

int dfs(int u,int fa) {
	int lowu=pre[u]=++dfs_clock;
	int child=0;
	for(auto &v:G[u]) {
		if(!pre[v]) {
			++child;
			int lowv=dfs(v,u);
			lowu=std::min(lowu,lowv);
			if(lowv>=pre[u]) ++cut[u];
		}
		else if(pre[v]<pre[u]&&v!=fa) {
			lowu=std::min(lowu,pre[v]);
		}
	}
	if(fa<0&&child==1) cut[u]=1;
	low[u]=lowu;
	return lowu;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	freopen("in","r",stdin);
	freopen("out","w",stdout);
#endif // MengLan

	while(scanf("%d%d",&n,&m)==2&&n) {
		int u,v;
		FOR(i,0,n) G[i].clear();
		while(scanf("%d%d",&u,&v)==2&&u!=-1&&v!=-1) { G[u].push_back(v),G[v].push_back(u); }
		FOR(i,0,n) cut[i]=i?1:0;
		dfs_clock=0;
		memset(pre,0,sizeof(pre));
		dfs(0,-1);
		//FOR(i,0,n) printf("cur[%d]=%d\n",i,cut[i]);
		FOR(i,0,n) rnk[i]=i;
		std::sort(rnk,rnk+n,[&](const int &l,const int &r) {return cut[l]>cut[r]||cut[l]==cut[r]&&l<r;});
		FOR(i,0,m) printf("%d %d\n",rnk[i],cut[rnk[i]]);
		puts("");
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}