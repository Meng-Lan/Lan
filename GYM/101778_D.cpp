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

const int maxn=20;
std::vector<P> G[maxn];
struct Edge{
    int u,v,c;
    Edge(int u,int v,int c):u(u),v(v),c(c){}
    Edge():Edge(0,0,0){}
    bool operator<(const Edge &e)const{return c<e.c;}
};
int n,m,k;
int x[20];
std::vector<Edge> edges;

bool d[20][20];
bool check(int l){
    memset(d,0,sizeof(d));
    FOR(i,0,n) if(l&(1<<i)) d[i][i]=true;
    for(auto &e:edges) d[e.u][e.v]=d[e.v][e.u]=true;
    FOR(k,0,n) FOR(i,0,n) FOR(j,0,n) d[i][j]|=d[i][k]&&d[k][j];
    FOR(i,0,n) if(l&(1<<i)) FOR(j,0,n) if(l&(1<<j)) if(!d[i][j]) return false;
    return true;
}

int p[20];
int find(int x){return p[x]==x?x:find(p[x]);}
int MST(){
    FOR(i,0,n) p[i]=i;
    std::sort(edges.begin(),edges.end());
    int ans=0;
    for(auto &e:edges){
        int u=find(e.u),v=find(e.v);
        if(u!=v){
            p[u]=v;
            ans+=e.c;
        }
    }
    return ans;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    int T;scanf("%d",&T);
    while(T--){
        scanf("%d%d%d",&n,&m,&k);
        //PV(n)PV(m)PV(k)
        For(i,0,n) G[i].clear();
        FOR(i,0,m){
            int u,v,c;scanf("%d%d%d",&u,&v,&c);
            --u;--v;
            G[u].pb(P(v,c));
        }
        FOR(i,0,k) scanf("%d",x+i),--x[i];
        int ans=1e9;
        FOR(i,0,(1<<n)){
            bool ok=true;
            FOR(j,0,k) if(!(i&(1<<x[j]))) ok=false;
            if(!ok) continue;
            //PV(i);
            edges.clear();
            FOR(j,0,n) if(i&(1<<j)) FOR(l,0,G[j].size()) if(i&(1<<G[j][l].fi)) edges.pb(Edge(j,G[j][l].fi,G[j][l].se));
            if(!check(i)) continue;
            ans=std::min(ans,MST());
        }
        printf("%d\n",ans);
    }


#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
