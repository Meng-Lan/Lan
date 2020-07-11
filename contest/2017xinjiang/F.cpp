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

using namespace std;
const int maxn=10000+10;
int n,m;
vector<int>edge[maxn];
int low[maxn],dfn[maxn];
int dfs_clock;
int Stack[maxn];
bool Instack[maxn];
int top;
int Belong[maxn],scc_clock;
int out[maxn],in[maxn];

void init() {
	for(int i=1; i<=n; ++i)
		edge[i].clear();
}

void getmap() {
	scanf("%d%d",&n,&m);
	while(m--) {
		int a,b;
		scanf("%d%d",&a,&b);
		edge[a].push_back(b);
	}
}

void tarjan(int u,int per) {
	int v;
	low[u]=dfn[u]=++dfs_clock;
	Stack[top++]=u;
	Instack[u]=true;
	for(int i=0; i < edge[u].size(); i++) {
		v=edge[u][i];
		if(!dfn[v]) {
			tarjan(v,u);
			low[u]=min(low[v],low[u]);
		}
		else if(Instack[v]) {
			low[u]=min(low[u],dfn[v]);
		}
	}
	if(dfn[u]==low[u]) {
		scc_clock++;
		do {
			v=Stack[--top];
			Instack[v]=false;
			Belong[v]=scc_clock;
		} while(u!=v);
	}
}

void find() {
	memset(low,0,sizeof(low));
	memset(dfn,0,sizeof(dfn));
	memset(Instack,false,sizeof(Instack));
	memset(Belong,0,sizeof(Belong));
	dfs_clock=scc_clock=top=0;
	for(int i=1; i<=n; ++i) {
		if(!dfn[i])
			tarjan(i,i);
	}
}

void suodian() {
	for(int i=1; i<=scc_clock; ++i) {
		in[i]=0;
		out[i]=0;
	}
	for(int i=1; i<=n; ++i) {
		for(int j=0; j < edge[i].size(); ++j) {
			int u=Belong[i];
			int v=Belong[edge[i][j]];
			if(u!=v) {
				out[u]++,in[v]++;
			}
		}
	}
}

void solve() {
	if(scc_clock==1) {
		printf("0\n");
		return;
	}
	int numin=0,numout=0;
	for(int i=1; i<=scc_clock; ++i) {
		if(in[i]==0) numin++;
		if(out[i]==0) numout++;
	}
	//printf("%d\n",scc_clock);  
	printf("%d\n",max(numin,numout));
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	int T;
	scanf("%d",&T);
	while(T--) {
		init();
		getmap();
		find();
		suodian();
		solve();
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}