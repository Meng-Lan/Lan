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

const int maxn=505;
const int INF=1e9;
struct KM {
	int W[maxn][maxn],n;
	int Lx[maxn],Ly[maxn],left[maxn];
	bool S[maxn],T[maxn];
	std::vector<int> G[maxn];

	void init(int n) {
		this->n=n;
		FOR(i,0,n) G[i].clear();
		memset(W,0,sizeof(W));
	}

	void AddEdge(int u,int v,int w) {
		G[u].push_back(v);
		W[u][v]=w;
	}

	bool match(int u) {
		S[u]=true;
		FOR(i,0,G[u].size()) {
			int v=G[u][i];
			if(Lx[u]+Ly[v]==W[u][v]&&!T[v]) {
				T[v]=true;
				if(left[v]==-1||match(left[v])) {
					left[v]=u;
					return true;
				}
			}
		}
		return false;
	}

	void update() {
		int a=INF;
		FOR(u,0,n) if(S[u]) FOR(i,0,G[u].size()) {
			int v=G[u][i];
			if(!T[v]) a=std::min(a,Lx[u]+Ly[v]-W[u][v]);
		}
		FOR(i,0,n) {
			if(S[i]) Lx[i]-=a;
			if(T[i]) Ly[i]+=a;
		}
	}

	void solve() {
		FOR(i,0,n) {
			Lx[i]=*std::max_element(W[i],W[i]+n);
			left[i]=-1;
			Ly[i]=0;
		}
		FOR(u,0,n) {
			for(;;) {
				FOR(i,0,n) S[i]=T[i]=false;
				if(match(u)) break; else update();
			}
		}
	}
}solver;

const int maxp=55;
const int maxr=15;
int m,n,runtime[maxp][maxr];

void print_solution(){
	int start[maxp],region_num[maxp],total=0;
	FOR(region,0,m) {
		std::vector<int> programs;
		FOR(pos,0,n) {
			int right=region*n+pos;
			int left=solver.left[right];
			if(left>=n) break;
			programs.push_back(left);
			region_num[left]=region;
			total-=solver.W[left][right];
		}
		std::reverse(programs.begin(),programs.end());
		int time=0;
		FOR(i,0,programs.size()) {
			start[programs[i]]=time;
			time+=runtime[programs[i]][region];
		}
	}
	printf("Average turnaround time = %.2lf\n",(double)total/n);
	for(int p=0; p < n; p++)
		printf("Program %d runs in region %d from %d to %d\n",p+1,region_num[p]+1,start[p],start[p]+runtime[p][region_num[p]]);
	printf("\n");
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	freopen("in","r",stdin);
	freopen("out","w",stdout);
#endif // MengLan

	int kase=0;
	while(scanf("%d%d",&m,&n)==2&&m&&n){
		solver.init(m*n);
		int size[maxr];
		FOR(i,0,m) scanf("%d",size+i);
		FOR(program,0,n) {
			int k,s[maxr],t[maxr];
			scanf("%d",&k);
			FOR(i,0,k) scanf("%d%d",s+i,t+i);
			FOR(region,0,m) {
				int &time=runtime[program][region];
				time=INF;
				if(size[region]<s[0]) continue;
				FOR(i,0,k) {
					if(i==k-1||size[region]<s[i+1]) {
						time=t[i];break;
					}
				}
				FOR(pos,0,n) solver.AddEdge(program,region*n+pos,-(pos+1)*time);
			}
		}
		FOR(i,n,n*m) FOR(j,0,n*m) solver.AddEdge(i,j,1);
		solver.solve();
		printf("Case %d\n",++kase);
		print_solution();
	}

#ifdef MengLan
	//printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}