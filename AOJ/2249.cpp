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

const int maxn=1e4+10;
const int INF=1e9;
std::vector<int> G[maxn];
struct Edge{
    int to,dis,cost;
    Edge(int to=0,int dis=0,int cost=0):to(to),dis(dis),cost(cost){}
};
std::vector<Edge> edges;
int n,m;
struct Lan{
    int d,c,idx;
    Lan(int d=0,int c=0,int idx=0):d(d),c(c),idx(idx){}
    bool operator<(const Lan &rhs)const{
        return d>rhs.d||d==rhs.d&&c>rhs.c;
    }
    void print(){printf("d:%d c:%d idx:%d\n",d,c,idx);}
};
P d[maxn];

void dijkrust(){
    std::priority_queue<Lan> q;
    For(i,0,n) d[i]=P(INF,INF);d[1]=P(0,0);
    q.push(Lan(0,0,1));
    while(!q.empty()){
        Lan x=q.top();q.pop();
        int u=x.idx;
        if(d[u].fi<x.d||d[u].fi==x.d&&d[u].se<x.c) continue;
        //x.print();
        FOR(i,0,G[u].size()){
            Edge &e=edges[G[u][i]];
            if(d[e.to].fi>d[u].fi+e.dis||d[e.to].fi==d[u].fi+e.dis&&d[e.to].se>e.cost){
                d[e.to]=P(d[u].fi+e.dis,e.cost);
                q.push(Lan(d[e.to].fi,d[e.to].se,e.to));
            }
        }
    }
}


int main() {

    while(scanf("%d%d",&n,&m)==2&&(n||m)){
        edges.clear();
        For(i,0,n) G[i].clear();
        FOR(i,0,m){
            int u,v,d,c;scanf("%d%d%d%d",&u,&v,&d,&c);
            G[u].pb(edges.size());
            edges.push_back(Edge(v,d,c));
            G[v].pb(edges.size());
            edges.pb(Edge(u,d,c));
        }
        dijkrust();
        int ans=0;
        //For(i,1,n) printf("i:%d fi:%d se%d\n",i,d[i].fi,d[i].se); 
        For(i,2,n) ans+=d[i].se;
        printf("%d\n",ans);
    }

	return 0;
}
