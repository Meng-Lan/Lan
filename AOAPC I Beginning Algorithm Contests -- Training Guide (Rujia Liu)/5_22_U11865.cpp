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

const int INF=1000000000;
const int maxn=70,maxm=1e4+10;
int n,m,cost;
struct Edge {
	int u,v,b,c;
	Edge(int u,int v,int b,int c) :u(u),v(v),b(b),c(c) {}
	Edge() :Edge(0,0,0,0) {}
	bool operator<(const Edge &rhs)const { return b>rhs.b; }
};
std::vector<Edge> edges;

struct MDST {
	int n;
	int w[maxn][maxn];
	int vis[maxn];
	int ans;
	int removed[maxn];
	int cid[maxn];
	int pre[maxn];
	int iw[maxn];
	int max_cid;

	void init(int n) {
		this->n=n;
		FOR(i,0,n) FOR(j,0,n) w[i][j]=INF;
	}

	void AddEdge(int u,int v,int cost) {
		w[u][v]=std::min(w[u][v],cost);
	}

	int dfs(int s) {
		vis[s]=1;
		int ans=1;
		FOR(i,0,n) if(!vis[i]&&w[s][i]<INF) ans+=dfs(i);
		return  ans;
	}

	bool cycle(int u) {
		max_cid++;
		int v=u;
		while(cid[v]!=max_cid) { cid[v]=max_cid;v=pre[v]; }
		return v==u;
	}

	void update(int u) {
		iw[u]=INF;
		FOR(i,0,n) if(!removed[i]&&w[i][u]<iw[u]) {
			iw[u]=w[i][u];
			pre[u]=i;
		}
	}

	bool solve(int s) {
		memset(vis,0,sizeof(vis));
		if(dfs(s)!=n) return false;

		memset(removed,0,sizeof(removed));
		memset(cid,0,sizeof(cid));
		FOR(u,0,n) update(u);
		pre[s]=s;iw[s]=0;
		ans=max_cid=0;
		for(;;) {
			bool have_cycle=false;
			FOR(u,0,n) if(u!=s&&!removed[u]&&cycle(u)) {
				have_cycle=true;
				int v=u;
				do {
					if(v!=u) removed[v]=1;
					ans+=iw[v];
					FOR(i,0,n) if(cid[i]!=cid[u]&&!removed[i]) {
						if(w[i][v]<INF) w[i][u]=std::min(w[i][u],w[i][v]-iw[v]);
						w[u][i]=std::min(w[u][i],w[v][i]);
						if(pre[i]==v) pre[i]=u;
					}
					v=pre[v];
				} while(v!=u);
				update(u);
				break;
			}
			if(!have_cycle) break;
		}
		FOR(i,0,n) if(!removed[i]) ans+=iw[i];
		return true;
	}
}solver;

bool check(int cnt) {
	solver.init(n);
	FOR(i,0,cnt) solver.AddEdge(edges[i].u,edges[i].v,edges[i].c);
	if(!solver.solve(0)) return false;
	return solver.ans<=cost;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	int T;scanf("%d",&T);
	while(T--) {
		scanf("%d%d%d",&n,&m,&cost);
		edges.clear();
		FOR(i,0,m) {
			int u,v,b,c;scanf("%d%d%d%d",&u,&v,&b,&c);
			//if(u==v) continue;
			edges.push_back(Edge(u,v,b,c));
		}
		std::sort(edges.begin(),edges.end());
		int L=1,R=m,ans=-1;
		while(L<=R) {
			int M=L+(R-L)/2;
			if(check(M)) { ans=edges[M-1].b; R=M-1; }
			else L=M+1;
		}
		if(ans < 0) printf("streaming not possible.\n");
		else printf("%d kbps\n",ans);
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}