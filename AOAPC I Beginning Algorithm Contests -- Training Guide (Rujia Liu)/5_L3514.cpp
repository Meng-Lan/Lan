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

const int maxm=1000+10;
const int maxn=20000+10;
int pre[maxn],bccsz[maxn],dfs_clock,bcc_cnt;
std::vector<int> G[maxn];

int c[maxn];
void dfs(int u,int fa) {
	for(int &v:G[u]) {
		if(v==fa) continue;
		if(!pre[v]) {
			pre[v]=pre[u]+1;
			dfs(v,u);
			c[u]+=c[v];
		}
		else if(pre[v]<pre[u]) {
			bccsz[bcc_cnt++]=pre[u]-pre[v]+2;
			c[u]++;c[v]--;
		}
	}
}

bool find_bcc(int n) {
	memset(pre,0,sizeof(pre));
	memset(c,0,sizeof(c));
	dfs_clock=bcc_cnt=0;
	pre[1]=1;
	dfs(1,-1);
	For(i,1,n) if(!pre[i]||c[i]>1) return false;
	return true;
}

int n,m;
const int mod=1e1;
int ans[maxn];
void putans() {
	memset(ans,0,sizeof(ans));
	int len=0;
	ans[len]=1;
	for(int i=0;i<bcc_cnt;i++) {
		for(int j=0;j<=len;j++)
			ans[j]*=bccsz[i];
		for(int j=0;j<=len;j++) {
			ans[j+1]+=ans[j]/mod;
			ans[j]%=mod;
		}
		while(ans[len+1]) {
			ans[len+2]+=ans[len+1]/mod;
			ans[++len]%=mod;
		}
	}
	for(int i=len;i>=0;i--)
		printf("%d",ans[i]);
	puts("");
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	int kase=0;
	while(scanf("%d%d",&n,&m)==2&&n) {
		if(kase++) puts("");
		For(i,1,n) G[i].clear();
		FOR(i,0,m) {
			int cnt,u;scanf("%d%d",&cnt,&u);
			FOR(i,1,cnt) { int v;scanf("%d",&v);G[u].push_back(v);G[v].push_back(u);u=v; }
		}
		if(find_bcc(n)) putans();
		else puts("0");
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}