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

const int maxn=1e5+10;
struct Edge{
    int v,c;
    Edge(int v=0,int c=0):v(v),c(c){}
};
std::vector<Edge> G[maxn];
int n;
ll c[maxn],c1[maxn],c2[maxn];

void dfs(int u,int fa,ll d,ll *cost){
    cost[u]=d;
    for(auto &e:G[u]) if(e.v!=fa){
        dfs(e.v,u,d+e.c,cost);
    }
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    while(scanf("%d",&n)==1){
        For(i,1,n) G[i].clear();
        memset(c,0,sizeof(c));
        memset(c1,0,sizeof(c1));
        memset(c2,0,sizeof(c2));
        FOR(i,1,n){
            int u,v,c;scanf("%d%d%d",&u,&v,&c);
            G[u].pb(Edge(v,c));
            G[v].pb(Edge(u,c));
        }
        dfs(1,-1,0,c);
        int u;
        ll max=-1;
        For(i,1,n) if(c[i]>max){max=c[i];u=i;}
        std::priority_queue<ll,std::vector<ll>,std::greater<ll>> q;
        dfs(u,-1,0,c1);
        max=-1;
        int v=0;
        For(i,1,n){
            q.push(c1[i]);
            if(max<c1[i]){max=c1[i];v=i;}
        }
        dfs(v,-1,0,c2);
        while(q.size()>=n) q.pop();
        For(i,1,n)if(i!=u){
            if(q.top()<c2[i]){
                q.pop();q.push(c2[i]);
            }
        }
        ll ans=c1[v];
        For(i,1,n) if(i!=u&&i!=v) ans+=std::max(c1[i],c2[i]);
        printf("%lld\n",ans);
    }

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
