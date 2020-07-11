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

const int maxn=60;
struct Edge {
	int u,v;
	double d;
	Edge(int u=0,int v=0,double d=0.0) :u(u),v(v),d(d) {}
};
struct BellmanFord {
	int n,m;
	std::vector<int> G[maxn];
	std::vector<Edge> edges;
	bool inq[maxn];
	double d[maxn];
	int p[maxn];
	int cnt[maxn];

	void init(int n) {
		this->n=n;
		FOR(i,0,n) G[i].clear();
		edges.clear();
	}

	void AddEdge(int u,int v,double c) {
		edges.push_back({ u,v,c });
		m=edges.size();
		G[u].push_back(m-1);
	}

	bool nagetiveCycle() {
		std::queue<int> q;
		memset(inq,0,sizeof(inq));
		memset(cnt,0,sizeof(cnt));
		FOR(i,0,n) { d[i]=0;inq[0]=true;q.push(i); }
		while(!q.empty()) {
			int u=q.front();q.pop();
			inq[u]=false;
			for(auto &i:G[u]) {
				Edge &e=edges[i];
				if(d[e.v]>d[u]+e.d) {
					d[e.v]=d[u]+e.d;
					p[e.v]=i;
					if(!inq[e.v]) { q.push(e.v);inq[e.v]=true;if(++cnt[e.v]>n) return true; }
				}
			}
		}
		return false;
	}
}solver;

int n,m;

bool test(double x) {
	for(auto &e:solver.edges) e.d-=x;
	bool ret=solver.nagetiveCycle();
	for(auto &e:solver.edges) e.d+=x;
	return ret;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	int T;scanf("%d",&T);
	For(kase,1,T) {
		scanf("%d%d",&n,&m);
		solver.init(n);
		int ub=0;
		FOR(i,0,m) {
			int u,v,c;
			scanf("%d%d%d",&u,&v,&c);--u;--v;
			solver.AddEdge(u,v,c);ub=std::max(ub,c);
		}
		printf("Case #%d: ",kase);
		if(!test(ub+1)) printf("No cycle found.\n");
		else {
			double L=0,R=ub;
			while(R-L>1e-3) {
				double M=L+(R-L)/2;
				if(test(M)) R=M;else L=M;
			}
			printf("%.2f\n",L);
		}
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}