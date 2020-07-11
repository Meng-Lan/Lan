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

const int maxn=1005;
const int INF=1e9;
struct Edge{
    int from,to,cap,flow,cost;
    Edge(int from,int to,int cap,int flow,int cost):from(from),to(to),cap(cap),flow(flow),cost(cost){}
    Edge():Edge(0,0,0,0,0){}
};
struct MCMF{
    int n,m,s,t,S;
    std::vector<int> G[maxn];
    std::vector<Edge> edges;
    int p[maxn];
    int inq[maxn];
    int d[maxn];
    int a[maxn];

    void init(int n){
        this->n=n;m=0;
        edges.clear();
        For(i,0,n) G[i].clear();
    }

    void AddEdge(int from,int to,int cap,int cost){
        edges.pb(Edge(from,to,cap,0,cost));
        edges.pb(Edge(to,from,0,0,-cost));
        m=edges.size();
        G[from].pb(m-2);
        G[to].pb(m-1);
    }

    void printEdge(){
        for(int i=0;i<edges.size();i+=2){
            Edge &e=edges[i];
            printf("from:%d to:%d cap:%d cost:%d\n",e.from,e.to,e.cap,e.cost);
        }
    }

    int BM(int s,int t,int &flow,int &cost){
        For(i,0,n) d[i]=INF;
        memset(inq,0,sizeof(inq));
        d[s]=0;inq[s]=1;p[s]=0;a[s]=INF;
        std::queue<int> q;
        q.push(s);
        while(!q.empty()){
            int u=q.front();q.pop();
            inq[u]=0;
            FOR(i,0,G[u].size()){
                Edge &e=edges[G[u][i]];
                if(e.cap>e.flow&&d[e.to]>d[u]+e.cost){
                    d[e.to]=d[u]+e.cost;
                    p[e.to]=G[u][i];
                    a[e.to]=std::min(a[u],e.cap-e.flow);
                    if(!inq[e.to]){q.push(e.to);inq[e.to]=1;}
                }
            }
        }
        if(d[t]>S) return false;
        flow+=a[t]*(S-d[t]+1);
        cost+=d[t]*a[t];
        for(int u=t;u!=s;u=edges[p[u]].from){
            edges[p[u]].flow+=a[t];
            edges[p[u]^1].flow-=a[t];
        }
        return true;
    }

    int MincostMaxflow(int s,int t,int &cost,int S,int max){
        int flow=0;cost=0;
        this->S=S;
        while(BM(s,t,flow,cost));
        return flow;
    }
}solver;
int n,s,g,S,m;

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    int T;scanf("%d",&T);
    while(T--){
        scanf("%d%d%d%d%d",&n,&s,&g,&S,&m);
        solver.init(n+2);
        int t=n+1;
        FOR(i,0,m){int x;scanf("%d",&x);solver.AddEdge(x,t,INF,0);}
        int r;scanf("%d",&r);
        FOR(i,0,r){
            int a,b,p,t;scanf("%d%d%d%d",&a,&b,&p,&t);
            solver.AddEdge(a,b,p,t);
        }
        int cost=0,flow=0;
        //solver.printEdge();
        flow=solver.MincostMaxflow(s,t,cost,S,g);
        printf("%d\n",std::min(flow,g));
    }


#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
