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

const int INF=1e9;
const int maxn=510;
const int maxm=2710;
struct Edge {
	int to,dist;
	Edge(int to=0,int dist=0) :to(to),dist(dist) {}
};
struct BellmanFord {
	int n,m;
	Edge edges[maxm];
	int head[maxn];
	int next[maxm];
	bool inq[maxn];   // 是否在队列中
	int d[maxn];      // s到各个点的距离
	int cnt[maxn];    // 进队次数

	void init(int n) {
		this->n=n;
		m=0;
		memset(head,-1,sizeof(head));
	}

	void AddEdge(int from,int to,int dist) {
		next[m]=head[from];
		head[from]=m;
		edges[m++]=Edge(to,dist);
	}

	bool negativeCycle() {
		std::queue<int> Q;
		memset(inq,0,sizeof(inq));
		memset(cnt,0,sizeof(cnt));
		for(int i=0; i < n; i++) { d[i]=0; Q.push(i); }

		int u;
		while(!Q.empty()) {
			u=Q.front(); Q.pop();
			inq[u]=false;
			for(int i=head[u]; i!=-1; i=next[i]) {
				Edge& e=edges[i];
				if(d[e.to] > d[u]+e.dist) {
					d[e.to]=d[u]+e.dist;
					if(!inq[e.to]) { Q.push(e.to); inq[e.to]=true; if(++cnt[e.to] > n) return true; }
				}
			}
		}
		return false;
	}
}solver;

bool test(int x) {
	FOR(i,0,solver.m) solver.edges[i].dist-=x;
	bool ret=solver.negativeCycle();
	FOR(i,0,solver.m) solver.edges[i].dist+=x;
	return !ret;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	int n,m;
	while(scanf("%d%d",&n,&m)==2&&n&&m) {
		solver.init(n);
		int ub=0;
		FOR(i,0,m) {
			int u,v,d;
			scanf("%d%d%d",&u,&v,&d);ub=std::max(ub,d);
			solver.AddEdge(u-1,v-1,d);
		}
		if(test(ub+1)) printf("Infinite\n");
		else if(!test(1)) printf("No Solution\n");
		else {
			int L=2,R=ub,ans=1;
			while(L<=R) {
				int m=L+(R-L)/2;
				if(test(m)) { ans=m;L=m+1; }
				else R=m-1;
			}
			printf("%d\n",ans);
		}
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}