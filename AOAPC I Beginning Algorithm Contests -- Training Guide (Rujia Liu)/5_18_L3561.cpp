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
namespace IO {
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
inline int read() { static int x;read(x);return x; }
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
const int maxn=4e3+10;
struct Edge {
	int from,to,dist,val;
	Edge(int from=0,int to=0,int dist=0,int val=0) :from(from),to(to),dist(dist),val(val) {}
};
struct HeapNode {
	int u,d;
	HeapNode(int d,int u) :d(d),u(u) {}
	bool operator<(const HeapNode &rhs)const { return d>rhs.d; }
};
struct Dijkstra {
	int n,m;
	std::vector<Edge> edges;
	std::vector<int> G[maxn];
	bool done[maxn];
	int p[maxn],d[maxn];

	void init(int n) {
		this->n=n;
		FOR(i,0,n) G[i].clear();
		edges.clear();
	}

	void AddEdge(int from,int to,int dist,int val) {
		edges.push_back({ from,to,dist,val });
		m=edges.size();
		G[from].push_back(m-1);
	}

	void dijkstra(int s) {
		memset(done,0,sizeof(done));
		FOR(i,0,n) d[i]=INF;
		std::priority_queue<HeapNode> q;
		d[s]=0;q.push({ 0,s });
		while(!q.empty()) {
			auto x=q.top();q.pop();
			int u=x.u;
			if(done[u]) continue;
			done[u]=true;
			for(auto &i:G[u]) {
				Edge &e=edges[i];
				if(d[e.to]>d[u]+e.dist) {
					d[e.to]=d[u]+e.dist;
					p[e.to]=i;
					q.push({ d[e.to],e.to });
				}
			}
		}
	}

	std::vector<int> GetShortestPath(int s,int t) {
		std::vector<int> path;
		while(t!=s) {
			path.push_back(edges[p[t]].val);
			t=edges[p[t]].from;
		}
		std::reverse(path.begin(),path.end());
		return path;
	}
}solver;

int n_cities;
std::map<int,int> city_id;
int ID(int city) {
	if(city_id.count(city)) return city_id[city];
	city_id[city]=n_cities++;
	return n_cities-1;
}
int ID(int visited,int cur) { return (visited-1)*n_cities+cur; }

const int maxnt=100;
int cost[maxnt];
std::vector<int> cities[maxnt],iti;
int NT,NI,x,len,kase;

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	while(scanf("%d",&NT)==1&&NT) {
		n_cities=0;city_id.clear();
		FOR(i,0,NT) {
			cities[i].clear();
			scanf("%d%d",cost+i,&len);
			while(len--) { scanf("%d",&x);cities[i].push_back(ID(x)); }
		}
		scanf("%d",&NI);
		++kase;
		For(trip,1,NI) {
			iti.clear();
			scanf("%d",&len);
			FOR(i,0,len) { scanf("%d",&x);iti.push_back(ID(x)); }
			solver.init(n_cities*len);
			FOR(ticket,0,NT) {
				FOR(visited,1,len) {
					int cur=cities[ticket][0];
					int next=visited;
					FOR(leg,1,cities[ticket].size()) {
						if(cities[ticket][leg]==iti[next]) ++next;
						solver.AddEdge(ID(visited,cur),ID(next,cities[ticket][leg]),cost[ticket],ticket+1);
						if(next==len) break;
					}
				}
			}
			int src=ID(1,iti[0]),dest=ID(len,iti[len-1]);
			solver.dijkstra(src);
			printf("Case %d, Trip %d: Cost = %d\n",kase,trip,solver.d[dest]);
			printf("  Tickets used:");
			std::vector<int> path=solver.GetShortestPath(src,dest);
			for(int i=0; i<path.size(); i++) printf(" %d",path[i]);
			printf("\n");
		}
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}