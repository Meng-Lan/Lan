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
std::vector<int> G[maxn],bcc[maxn];
int pre[maxn],iscut[maxn],bccno[maxn],dfs_clock,bcc_cnt;
bool vis[maxn];
struct Edge{
    int u,v;
    Edge(int u=0,int v=0):u(u),v(v){}
};
std::stack<Edge> S;
int n,m,k;

int dfs(int u,int fa){
    int lowu=pre[u]=++dfs_clock;
    int child=0;
    for(int i=0;i<G[u].size();++i){
        int v=G[u][i];
        Edge e=Edge(u,v);
        if(!pre[v]){
            S.push(e);
            child++;
            int lowv=dfs(v,u);
            lowu=std::min(lowu,lowv);
            if(lowv>=pre[u]){
                iscut[u]=true;
                bcc_cnt++;bcc[bcc_cnt].clear();
                for(;;){
                    Edge x=S.top();S.pop();
                    if(bccno[x.u]!=bcc_cnt){bcc[bcc_cnt].pb(x.u);bccno[x.u]=bcc_cnt;}
                    if(bccno[x.v]!=bcc_cnt){bcc[bcc_cnt].pb(x.v);bccno[x.v]=bcc_cnt;}
                    if(x.u==u&&x.v==v) break;
                }
            }
        }
        else if(pre[v]<pre[u]&&v!=fa){
            S.push(e);
            lowu=std::min(lowu,pre[v]);
        }
    }
    if(fa<0&&child==1) iscut[u]=0;
    return lowu;
}

void find_bcc(int n){
    memset(pre,0,sizeof(pre));
    memset(iscut,0,sizeof(iscut));
    memset(bccno,0,sizeof(bccno));
    dfs_clock=bcc_cnt=0;
    for(int i=0;i<n;++i) if(!pre[i]) dfs(i,-1);
    /*PV(dfs_clock)PV(bcc_cnt);
    For(i,1,bcc_cnt){
        PV(i)
        FOR(j,0,bcc[i].size()) printf("%d ",bcc[i][j]);puts("");
    }*/
}

struct Lan{
    int a,b;
    Lan(int a=0,int b=0):a(a),b(b){}
    bool operator<(const Lan &rhs)const{return a*rhs.b>b*rhs.a;}
};

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    int T;scanf("%d",&T);
    while(T--){
        scanf("%d%d%d",&n,&m,&k);
        For(i,0,n) G[i].clear();
        FOR(i,0,m){
            int u,v;scanf("%d%d",&u,&v);
            G[u].pb(v);
            G[v].pb(u);
        }
        find_bcc(n);
        std::vector<Lan> vp;
        memset(vis,0,sizeof(vis));
        For(i,1,bcc_cnt) if(bcc[i].size()>2){
            for(auto &v:bcc[i]) vis[v]=true;
        }
        int ans=0;
        For(i,1,n) if(G[i].size()==1&&!vis[i]){
            Lan need(0,0);
            std::queue<int> q;
            q.push(i);
            while(!q.empty()){
                int u=q.front();q.pop();
                if(vis[u]) continue;
                if(G[u].size()==1) ++need.b;
                need.a++;vis[u]=true;
                for(auto v:G[u]) if(!vis[v]) q.push(v);
            }
            ans+=need.a;
            vp.pb(need);
        }
        std::sort(vp.begin(),vp.end());
        for(auto &it:vp) if(k>=it.b) {ans-=it.a;k-=it.b;}
        //for(int i=0;i<(vi.size()-k);++i) ans+=vi[i];
        printf("%d\n",ans);
    }

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
