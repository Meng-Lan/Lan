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
#define fi first
#define se second
#define pb push_back
#define is insert
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
	while(isdigit(c=IO::getchar())) { in*=10;in+=c-'0'; }
	in*=symbol;
}
inline int read() { static int x;read(x);return x; }
ll gcd(ll a,ll b) { return b?gcd(b,a%b):a; }
ll lcm(ll a,ll b) { return a/gcd(a,b)*b; }
#define PA(name,init,len) cout<<#name"["<<#len"]=";FOR(_,init,len) cout<<name[_]<<" \n"[_==(len-1)];
#define Pa(name,init,len) cout<<#name"["<<#len"]=";For(_,init,len) cout<<name[_]<<" \n"[_==(len)];
#define PV(name) cout<<#name"="<<name<<'\n';

const int maxn=200+10;
const int INF=255*1000+10;

struct Edge {
	int from,to,cap,flow;
};

bool operator < (const Edge& a,const Edge& b) {
	return a.from < b.from||(a.from==b.from && a.to < b.to);
}

struct Dinic {
	int n,m,s,t;
	std::vector<Edge> edges;    // 边数的两倍
	std::vector<int> G[maxn];   // 邻接表，G[i][j]表示结点i的第j条边在e数组中的序号
	bool vis[maxn];         // BFS使用
	int d[maxn];           // 从起点到i的距离
	int cur[maxn];        // 当前弧指针

	void ClearAll(int n) {
		for(int i=0; i<n; i++) G[i].clear();
		edges.clear();
	}

	void ClearFlow() {
		for(int i=0; i<edges.size(); i++) edges[i].flow=0;
	}

	void AddEdge(int from,int to,int cap) {
		edges.push_back({ from,to,cap,0 });
		edges.push_back({ to,from,0,0 });
		m=edges.size();
		G[from].push_back(m-2);
		G[to].push_back(m-1);
	}

	bool BFS() {
		memset(vis,0,sizeof(vis));
		std::queue<int> Q;
		Q.push(s);
		vis[s]=1;
		d[s]=0;
		while(!Q.empty()) {
			int x=Q.front(); Q.pop();
			for(int i=0; i<G[x].size(); i++) {
				Edge& e=edges[G[x][i]];
				if(!vis[e.to]&&e.cap>e.flow) {
					vis[e.to]=1;
					d[e.to]=d[x]+1;
					Q.push(e.to);
				}
			}
		}
		return vis[t];
	}

	int DFS(int x,int a) {
		if(x==t||a==0) return a;
		int flow=0,f;
		for(int& i=cur[x]; i<G[x].size(); i++) {
			Edge& e=edges[G[x][i]];
			if(d[x]+1==d[e.to]&&(f=DFS(e.to,std::min(a,e.cap-e.flow)))>0) {
				e.flow+=f;
				edges[G[x][i]^1].flow-=f;
				flow+=f;
				a-=f;
				if(a==0) break;
			}
		}
		return flow;
	}

	int Maxflow(int s,int t) {
		this->s=s; this->t=t;
		int flow=0;
		while(BFS()) {
			memset(cur,0,sizeof(cur));
			flow+=DFS(s,INF);
		}
		return flow;
	}

	void Mincut() { // call this after maxflow
		for(auto &e:edges)
			if(e.cap>0) {
				if(e.flow==e.cap) e.cap++;
				else e.cap=INF;
			}
		//ClearFlow();
	}

	void Reduce() {
		for(int i=0; i<edges.size(); i++) edges[i].cap-=edges[i].flow;
	}

	void print(int test) {
		printf("test:%d\n",test);
		for(auto &e:edges) printf("from:%d to:%d cap:%d flow:%d\n",e.from+1,e.to+1,e.cap,e.flow);
	}
}g;

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	int T;scanf("%d",&T);
	while(T--) {
		int n,m;scanf("%d%d",&n,&m);
		int s,t;scanf("%d%d",&s,&t);
		--s,--t;
		g.ClearAll(n);
		For(i,1,m) {
			int u,v,c;scanf("%d%d%d",&u,&v,&c);
			--u,--v;
			g.AddEdge(u,v,c);
		}
		g.Maxflow(s,t);
		//g.print(1);
		g.Mincut();
		int ans=g.Maxflow(s,t);
		//g.print(2);
		printf("%d\n",ans);
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}
