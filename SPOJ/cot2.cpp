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

const int maxn=4e4+10;
const int maxm=1e5+10;
const int Log=20;
int n,m,w[maxn],t[maxn];
int head[maxn],to[maxm],nxt[maxm],sz;

void AddEdge(int u,int v) {
    to[sz]=v;nxt[sz]=head[u];head[u]=sz++;
    to[sz]=u;nxt[sz]=head[v];head[v]=sz++;
}

int belong[maxn],dfn[maxn],dfs_clock;

struct Query {
    int u,v,id;
    void miao() { if(belong[u]>belong[v]) std::swap(u,v); }
    bool operator<(const Query &rhs)const {
        if(belong[u]==belong[rhs.u]) return belong[v]<belong[rhs.v];
        return belong[u]<belong[rhs.u];
    }
}q[maxm];
int ans[maxm],c[maxn],res;
int anc[Log][maxn],L[maxn];
int s[maxn],top,block,tot;

int dfs(int u,int fa,int dep) {
    dfn[u]=++dfs_clock;
    L[u]=dep;anc[0][u]=fa;
    int size=0;
    for(int i=head[u];~i;i=nxt[i]) {
        int v=to[i];
        if(v==fa) continue;
        size+=dfs(v,u,dep+1);
        if(size>=block) {
            ++tot;
            while(size--) belong[s[top--]]=tot;
            size=0;
        }
    }
    s[++top]=u;
    ++size;
    if(size>=block) {
        ++tot;
        while(size--) belong[s[top--]]=tot;
        size=0;
    }
    return size;
}

int LCA(int p,int q) {
    if(L[p]<L[q]) std::swap(p,q);
    for(int i=Log;i>=0;--i)
        if(L[p]-(1<<i)>=L[q]) p=anc[i][p];
    if(p==q) return p;
    for(int i=Log-1;i>=0;--i)
        if(anc[i][p]!=anc[i][q]) { p=anc[i][p];q=anc[i][q]; }
    return anc[0][p];
}

bool vis[maxn];
inline void reverse(int x) {
    if(vis[x]) { vis[x]=false;res-=(--c[w[x]]==0); }
    else { vis[x]=true;res+=(++c[w[x]]==1); }
}

void solve(int u,int v) {
    if(L[u]<L[v]) std::swap(u,v);
    while(L[u]!=L[v]) reverse(u),u=anc[0][u];
    while(u!=v) {
        reverse(u);u=anc[0][u];
        reverse(v);v=anc[0][v];
    }
}

int main() {
#ifdef MengLan
    int Beginning=clock();
    //freopen("in","r",stdin);
    //freopen("out","w",stdout);
#endif // MengLan

    read(n),read(m);//scanf("%d%d",&n,&m);
    For(i,1,n) read(w[i]),t[i-1]=w[i];

    std::sort(t,t+n);
    int len=std::unique(t,t+n)-t;
    For(i,1,n) w[i]=std::lower_bound(t,t+len,w[i])-t+1;

    memset(head,-1,sizeof(int)*(n+2));sz=0;
    FOR(i,1,n) { int u=read(),v=read();AddEdge(u,v); }
    FOR(i,0,m) { read(q[i].u),read(q[i].v);q[i].id=i; }

    block=std::max(1,(int)sqrt(n));
    len=dfs(1,-1,0);
    while(len--) belong[s[top--]]=tot;

    for(int i=1;i<Log;++i)
        for(int j=1;j<=n;++j) {
            if(anc[i-1][j]==-1) anc[i][j]=-1;
            else anc[i][j]=anc[i-1][anc[i-1][j]];
        }

    FOR(i,0,m) q[i].miao();
    std::sort(q,q+m);
    int u=1,v=1;reverse(1);
    FOR(i,0,m) {
        solve(u,q[i].u);
        solve(v,q[i].v);
        reverse(LCA(q[i].u,q[i].v));
        reverse(LCA(u,v));
        ans[q[i].id]=res;
        u=q[i].u;v=q[i].v;
    }

    FOR(i,0,m) printf("%d\n",ans[i]);

#ifdef MengLan
    printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
    return 0;
}
