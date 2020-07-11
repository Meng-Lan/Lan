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
typedef std::pair<ll,ll> P;
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
const ll INF=1e18;
std::vector<P> G[maxn];
ll d[maxn];
bool vis[maxn];
int n,m;

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    int T;scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        memset(d,0,sizeof(d));
        memset(vis,0,sizeof(vis));
        For(i,0,n) G[i].clear();
        FOR(i,0,m) {
            int x,y,z;scanf("%d%d%d",&x,&y,&z);
            assert(x>=1&&x<=n);
            assert(y>=1&&y<=n);
            G[x].pb(P(y,z));G[y].pb(P(x,z));
            d[x]+=z;d[y]+=z;
        }
        ll ans=0;
        std::priority_queue<P,std::vector<P>,std::greater<P>> q;
        For(i,1,n) q.push(P(d[i],i));
        while(!q.empty()){
            auto u=q.top();q.pop();
            if(d[u.se]>ans) ans=d[u.se];
            if(vis[u.se]) continue;
            vis[u.se]=true;
            FOR(i,0,G[u.se].size()) if(!vis[G[u.se][i].fi]){
                d[G[u.se][i].fi]-=G[u.se][i].se;
                q.push(P(d[G[u.se][i].fi],G[u.se][i].fi));
            }
        }
        printf("%lld\n",ans);
    }


#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
