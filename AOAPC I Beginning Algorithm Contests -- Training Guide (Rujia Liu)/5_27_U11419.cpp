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
while(isalnum(c=IO::getchar())) { in*=10;in+=c-'0'; }
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

const int maxn=1e3+10;
struct BMP {
	int n,m;
	std::vector<int> G[maxn];
	int S[maxn],T[maxn];
	int left[maxn],right[maxn];

	void init(int n,int m) {
		this->n=n;
		this->m=m;
		FOR(i,0,n) G[i].clear();
	}

	void AddEdge(int u,int v) {
		G[u].push_back(v);
	}

	bool match(int u) {
		S[u]=true;
		for(auto &v:G[u]) {
			if(!T[v]) {
				T[v]=true;
				if(left[v]==-1||match(left[v])) {
					left[v]=u;
					right[u]=v;
					return true;
				}
			}
		}
		return false;
	}

	int solve() {
		int ans=0;
		memset(left,-1,sizeof(left));
		memset(right,-1,sizeof(right));
		FOR(u,0,n) {
			memset(S,0,sizeof(S));
			memset(T,0,sizeof(T));
			if(match(u)) ++ans;
		}
		return ans;
	}

	int mincover(std::vector<int> &X,std::vector<int> &Y) {
		int ans=solve();
		memset(S,0,sizeof(S));
		memset(T,0,sizeof(T));
		FOR(u,0,n) if(right[u]==-1) match(u);
		FOR(i,0,n) if(!S[i]) X.push_back(i);
		FOR(i,0,m) if(T[i]) Y.push_back(i);
		return ans;
	}
}solver;
int n,m,c;

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	while(scanf("%d%d%d",&n,&m,&c)==3&&n&&m&&c) {
		solver.init(n,m);
		FOR(i,0,c) { int x,y;scanf("%d%d",&x,&y);--x;--y;solver.AddEdge(x,y); }
		std::vector<int> X,Y;
		printf("%d",solver.mincover(X,Y));
		for(auto &u:X) printf(" r%d",u+1);
		for(auto &v:Y) printf(" c%d",v+1);
		puts("");
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}