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

const int maxn=105;
struct TwoSTA {
	int n;
	std::vector<int> G[maxn<<1];
	bool mark[maxn<<1];
	int S[maxn<<1],c;

	bool dfs(int x) {
		if(mark[x^1]) return false;
		if(mark[x]) return true;
		mark[x]=true;
		S[c++]=x;
		for(auto &v:G[x]) if(!dfs(v)) return false;
		return true;
	}

	void init(int n) {
		this->n=n;
		FOR(i,0,(n<<1)) G[i].clear();
		memset(mark,0,sizeof(mark));
	}

	void add(int x,int y) { G[x].push_back(y); }

	void add_clause(int x,int xval,int y,int yval) {
		x=(x<<1)|xval;
		y=(y<<1)|yval;
		add(x^1,y);
		add(y^1,x);
	}
}solver;

int n,m;
char ans[maxn];
bool solve() {
	for(int i=0;i<(n<<1);i+=2)
		if(!solver.mark[i]&&!solver.mark[i+1]) {
			solver.c=0;
			bool no=solver.dfs(i);
			while(solver.c) { solver.mark[solver.S[--solver.c]]=false; }
			solver.c=0;
			bool yes=solver.dfs(i+1);
			while(solver.c) { solver.mark[solver.S[--solver.c]]=false; }
			//printf("i:%d no:%d yes:%d\n",i,(int)no,int(yes));
			if(no&&yes) ans[i/2]='?';
			else if(no) ans[i/2]='n';
			else if(yes) ans[i/2]='y';
			else return false;
		}
	ans[n]='\0';
	return true;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	int kase=0;
	while(scanf("%d%d",&n,&m)==2&&n) {
		solver.init(n);
		FOR(i,0,m) {
			int k;scanf("%d",&k);
			int no[5],val[5];char c;
			FOR(i,0,k) scanf("%d %c",no+i,&c),val[i]=c=='y'?1:0,--no[i];
			if(k<=2) FOR(i,0,k) solver.add(no[i]*2+(val[i]^1),no[i]*2+val[i]);
			else FOR(i,0,k) FOR(j,i+1,k) solver.add_clause(no[i],val[i],no[j],val[j]);
		}
		printf("Case %d: ",++kase);
		if(!solve()) puts("impossible");
		else puts(ans);
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}