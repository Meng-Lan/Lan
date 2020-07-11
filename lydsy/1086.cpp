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

const int maxn=1e3+10;
int dfn[maxn],dfs_clock;
int head[maxn],to[maxn<<1],nxt[maxn<<1],sz;
int belong[maxn],s[maxn],tot,top,blc;
int n,m,city[maxn];
int dfs(int u,int fa) {
    dfn[u]=++dfs_clock;
    int size=0;
    for(int i=head[u];~i;i=nxt[i]) if(to[i]!=fa) {
        //L[to[i]]=L[u]+1;anc[to[i]][0]=u;
        size+=dfs(to[i],u);
        if(size>=m) {
            ++tot;
            city[tot]=u;
            For(i,1,size) belong[s[top--]]=tot;
            size=0;
        }
    }
    s[++top]=u;
    return size+1;
}

inline void AddEdge(int u,int v) {
    to[sz]=v;nxt[sz]=head[u];head[u]=sz++;
    to[sz]=u;nxt[sz]=head[v];head[v]=sz++;
}

int main() {
#ifdef MengLan
    int Beginning=clock();
    //freopen("in","r",stdin);
    //freopen("out","w",stdout);
#endif // MengLan

    scanf("%d%d",&n,&m);
    memset(head,-1,sizeof(head));
    FOR(i,1,n) { int u,v;scanf("%d%d",&u,&v);AddEdge(u,v); }
    int cnt=dfs(1,-1);
    For(i,1,cnt) belong[s[top--]]=tot;
    if(tot==0) { puts("0");return 0; }
    printf("%d\n",tot);
    For(i,1,n) printf("%d%c",belong[i]," \n"[i==n]);
    For(i,1,tot) printf("%d%c",city[i]," \n"[i==tot]);

#ifdef MengLan
    printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
    return 0;
}
