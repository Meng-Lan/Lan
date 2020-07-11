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

const int maxn=2e3+10;
struct TwoSAT {
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
		FOR(i,0,n<<1) G[i].clear();
		memset(mark,0,sizeof(mark));
	}

	void add_clause(int x,int xval,int y,int yval) {
		x=(x<<1)+xval;
		y=(y<<1)+yval;
		G[x^1].push_back(y);
		G[y^1].push_back(x);
	}

	bool solve() {
		for(int i=0;i<(n<<1);i+=2) {
			if(!mark[i]&&!mark[i+1]) {
				c=0;
				if(!dfs(i)) {
					while(c>0) mark[S[--c]]=false;
					if(!dfs(i+1)) return false;
				}
			}
		}
		return true;
	}
}solver;
int n,T[maxn][2];

bool test(int diff) {
	solver.init(n);
	FOR(i,0,n) FOR(a,0,2)
		FOR(j,i+1,n) FOR(b,0,2)
		if(std::abs(T[i][a]-T[j][b])<diff) solver.add_clause(i,a^1,j,b^1);
	return solver.solve();
}

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	while(scanf("%d",&n)==1&&n) {
		int L=0,R=0;
		FOR(i,0,n) FOR(a,0,2) {
			scanf("%d",T[i]+a);
			R=std::max(R,T[i][a]);
		}
		while(L<R) {
			int m=L+(R-L+1)/2;
			if(test(m)) L=m;else R=m-1;
		}
		printf("%d\n",L);
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}