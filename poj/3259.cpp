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

struct Edge{
    int from,to,cost;
    Edge(int f=0,int t=0,int c=0):from(f),to(t),cost(c){}
};
std::vector<Edge> edges;
int n,m,w;
const int maxn=555;
int d[maxn];

bool BM(){
    memset(d,0,sizeof(d));
    FOR(i,0,n) FOR(j,0,edges.size()){
        Edge &e=edges[j];
        if(d[e.to]>d[e.from]+e.cost){
            d[e.to]=d[e.from]+e.cost;
            if(i==n-1) return true;
        }
    }
    return false;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    int T;scanf("%d",&T);
    while(T--){
        scanf("%d%d%d",&n,&m,&w);
        edges.clear();
        FOR(i,0,m){
            int u,v,c;scanf("%d%d%d",&u,&v,&c);
            edges.pb(Edge(u,v,c));
            edges.pb(Edge(v,u,c));
        }
        FOR(i,0,w){
            int u,v,c;scanf("%d%d%d",&u,&v,&c);
            edges.pb(Edge(u,v,-c));
        }
        if(BM()) puts("YES");
        else puts("NO");
    }



#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
