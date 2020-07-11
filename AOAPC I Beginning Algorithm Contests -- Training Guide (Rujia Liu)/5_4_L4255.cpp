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

const int maxn=15;
int sum[maxn],n,G[maxn][maxn],c[maxn];
std::vector<int> topo;

bool dfs(int u) {
	c[u]=-1;
	For(v,0,n) if(G[u][v]) {
		if(c[v]<0) return false;
		else if(!c[v]) dfs(v);
	}
	c[u]=1;topo.push_back(u);
	return true;
}

bool topsort() {
	topo.clear();
	memset(c,0,sizeof(c));
	For(u,0,n) if(!c[u]) if(!dfs(u)) return false;
	std::reverse(topo.begin(),topo.end());
	return true;
}

int fa[maxn];
int find(int x) { return fa[x]=fa[x]==x?x:find(fa[x]); }

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	int T;scanf("%d",&T);
	while(T--) {
		char in[100],S[11][11];
		scanf("%d%s",&n,in);
		int idx=0;
		For(i,0,n) fa[i]=i;
		For(i,1,n) For(j,i,n) {
			S[i][j]=in[idx++];
			if(S[i][j]=='0') fa[j]=i-1;
		}
		memset(G,0,sizeof(G));
		For(i,1,n) For(j,i,n) {
			if(S[i][j]=='-') G[find(j)][find(i-1)]=1;
			if(S[i][j]=='+') G[find(i-1)][find(j)]=1;
		}
		topsort();
		int cur=0;
		For(i,0,n) sum[topo[i]]=cur++;
		For(i,1,n) {
			sum[i]=sum[find(i)];
			if(i>1) printf(" ");
			printf("%d",sum[i]-sum[i-1]);
		}
		puts("");
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}