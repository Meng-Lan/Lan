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

const int maxn=3e5+10;
std::vector<int> G[maxn];
int n,q;
int in[maxn];
int anc[maxn][20],L[maxn];

void dfs(int u,int f,int d) {
    L[u]=d;anc[u][0]=f;
    for(auto &v:G[u]) if(v!=f) {
        dfs(v,u,d+1);
    }
}

void init() {
    for(int j=1;(1<<j)<n;++j) {
        For(i,1,n) if(anc[i][j-1]!=-1) {
            int a=anc[i][j-1];
            anc[i][j]=anc[a][j-1];
        }
    }
}

int query(int p,int q) {
    if(L[p]<L[q]) std::swap(p,q);
    int log;
    for(log=1;(1<<log)<=L[p];++log);--log;
    for(int i=log;i>=0;--i) if(L[p]-(1<<i)>=L[q]) p=anc[p][i];

    if(p==q) return p;

    for(int i=log;i>=0;--i) if(anc[p][i]!=-1&&anc[p][i]!=anc[q][i]) {
        p=anc[p][i];q=anc[q][i];
    }
    return anc[p][0];
}



int main() {
#ifdef MengLan
    int Beginning=clock();
    //freopen("in","r",stdin);
    //freopen("out","w",stdout);
#endif // MengLan

    scanf("%d",&n);
    FOR(i,1,n) {
        int u,v;scanf("%d%d",&u,&v);
        G[u].pb(v);G[v].pb(u);
    }
    memset(anc,-1,sizeof(anc));
    dfs(1,-1,1);
    init();
    scanf("%d",&q);
    FOR(i,0,q) {
        int s;scanf("%d",&s);
        FOR(i,0,s) scanf("%d",in+i);
        //assert(s!=1);
        if(s==1) puts("0");
        else {
            int u=in[0],v=in[1];
            int ans=L[u]+L[v]-2*L[query(u,v)];
            FOR(i,2,s) {
                int t=L[u]+L[in[i]]-2*L[query(u,in[i])];
                int t2=L[v]+L[in[i]]-2*L[query(v,in[i])];
                if(t>ans||t2>ans) {
                    if(t>t2) { v=in[i];ans=t; }
                    else { u=in[i];ans=t2; }
                }
            }
            printf("%d\n",(ans+1)/2);
        }
    }

#ifdef MengLan
    printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
    return 0;
}
