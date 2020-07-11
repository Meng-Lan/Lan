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

const int maxn=70;
struct TwoSAT {
	int n;
	std::vector<int> G[maxn<<1];
	bool mark[maxn<<1];
	int S[maxn<<1],c;

	void init(int n) {
		this->n=n;
		FOR(i,0,n<<1) G[i].clear();
		memset(mark,0,sizeof(mark));
	}

	void add_clause(int x,int xval,int y,int yval) {
		x=(x<<1)+xval;
		y=(y<<1)+yval;
		G[x^1].push_back(y);
		G[y^1].push_back(x);
	}

	bool dfs(int x) {
		if(mark[x]) return true;
		if(mark[x^1]) return false;
		mark[x]=true;
		S[c++]=x;
		for(auto &v:G[x]) if(!dfs(v)) return false;
		return true;
	}

	bool solve() {
		for(int i=0;i<(n<<1);i+=2) if(!mark[i]&&!mark[i+1]) {
			c=0;
			if(!dfs(i)) {
				while(c>0) mark[S[--c]]=false;
				if(!dfs(i+1)) return false;
			}
		}
		return true;
	}
}solver;
int n,m;
std::vector<P> in;

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	while(scanf("%d%d",&n,&m)==2&&n&&m) {
		int u,v;
		char s1[10],s2[10];
		solver.init(n<<1);
		solver.mark[1]=true;
		for(int i=0;i<(n<<1);i+=2) {
			solver.add_clause(i,1,i+1,1);
			solver.add_clause(i,0,i+1,0);
		}
		FOR(i,0,m) {
			scanf("%d%s%d%s",&u,s1,&v,s2);
			u<<=1;v<<=1;
			if(s1[0]=='h') u|=1;
			if(s2[0]=='h') v|=1;
			solver.add_clause(u,1,v,1);
		}
		if(!solver.solve()) puts("bad luck");
		else {
			for(int i=1;i<n;++i) printf("%d%c%c",i,"wh"[solver.mark[i<<2]]," \n"[i==n-1]);
		}
	}


#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}