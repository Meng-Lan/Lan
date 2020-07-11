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
#define PA(name,init,len) cout<<#name"["<<(len-init)<<"]=";FOR(_,init,len) cout<<name[_]<<" \n"[_==(len-1)];
#define Pa(name,init,len) cout<<#name"["<<(len-init+1)<<"]=";For(_,init,len) cout<<name[_]<<" \n"[_==(len)];
#define PV(name) cout<<#name"="<<name<<'\n';

const ll INF=1e18;
const int maxn=444;
struct Edge{
	int from,to;
	ll cap,flow;
	Edge(int u,int v,ll c,ll f):from(u),to(v),cap(c),flow(f){}
	Edge():Edge(0,0,0,0){}
};
struct Dinic{
	int n,m,s,t;
	std::vector<int> G[maxn];
	std::vector<Edge> edges;
	bool vis[maxn];
	int d[maxn];
	int cur[maxn];

	void init(int n){
		this->n=n;m=0;
		edges.clear();
		For(i,0,n) G[i].clear();
	}

	void AddEdge(int u,int v,ll c){
		edges.pb(Edge(u,v,c,0));
		edges.pb(Edge(v,u,0,0));
		m=edges.size();
		G[u].pb(m-2);
		G[v].pb(m-1);
	}

	bool BFS(){
		std::queue<int> q;q.push(s);
		memset(vis,0,sizeof(vis));
		vis[s]=true;
		d[s]=0;
		while(!q.empty()){
			int x=q.front();q.pop();
			for(auto i:G[x]){
				Edge &e=edges[i];
				if(!vis[e.to]&&e.cap>e.flow){
					vis[e.to]=true;
					d[e.to]=d[x]+1;
					q.push(e.to);
				}
			}
		}
		return vis[t];
	}

	ll DFS(int u,ll a){
		if(u==t||a==0) return a;
		ll flow=0,f;
		for(int &i=cur[u];i<G[u].size();++i){
			Edge &e=edges[G[u][i]];
			if(d[e.to]==d[u]+1&&(f=DFS(e.to,std::min(a,e.cap-e.flow)))>0){
				flow+=f;
				e.flow+=f;
				edges[G[u][i]^1].flow-=f;
				a-=f;
			}
			if(a==0) break;
		}
		return flow;
	}

	ll Maxflow(int s,int t){
		this->s=s;this->t=t;
		ll flow=0;
		while(BFS()){
			memset(cur,0,sizeof(cur));
			flow+=DFS(s,INF);
		}
		return flow;
	}
}g;
int n,m;
int v[maxn],c[maxn];

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	int T;scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		ll ans=0;
		For(i,1,n) scanf("%d",v+i),ans+=v[i];
		For(i,1,m) scanf("%d",c+i);
		g.init(n+m+2);
		int S=0,T=n+m+1;
		For(i,1,n){
			int x,y;scanf("%d%d",&x,&y);
			FOR(j,0,x){
				int t;scanf("%d",&t);
				g.AddEdge(i,t+n,INF);
			}
			FOR(j,0,y){
				int t;scanf("%d",&t);
				g.AddEdge(S,t,INF);
			}
		}
		For(i,1,n) g.AddEdge(S,i,v[i]);
		For(i,1,m) g.AddEdge(i+n,T,c[i]);
		printf("%lld\n",ans-g.Maxflow(S,T));
	}


#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
