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
const int maxc=1e6+10;
struct Q { int l,r,vs,id; }q[maxn];
struct UP { int pre,now,pos; }u[maxn];
int blc,c[maxn],las[maxn],n,m;
bool  vis[maxn];
bool cmp(Q &l,Q &r) { return (l.l/blc)==(r.l/blc)?l.r<r.r:l.l<r.l; }
int qsz,usz,ans[maxn],now,num[maxc],res;

void cal(int x) {
    if(vis[x]) { if((--num[c[x]])==0) --res; }
    else { if((++num[c[x]])==1) ++res; }
    vis[x]=!vis[x];
}
void change(int pos,int v) {
    if(vis[pos]) { cal(pos);c[pos]=v;cal(pos); }
    else c[pos]=v;
}

int main() {
#ifdef MengLan
    int Beginning=clock();
    //freopen("in","r",stdin);
    //freopen("out","w",stdout);
#endif // MengLan

    scanf("%d%d",&n,&m);
    For(i,1,n) scanf("%d",c+i),las[i]=c[i];
    blc=sqrt(n);
    For(i,1,m) {
        char cmd[4];
        int x,y;
        scanf(" %s%d%d",cmd,&x,&y);
        if(cmd[0]=='R') {
            ++usz;u[usz].pre=las[x];u[usz].now=y;u[usz].pos=x;las[x]=y;
        }
        else {
            ++qsz;q[qsz].l=x;q[qsz].r=y;q[qsz].id=qsz;q[qsz].vs=usz;
        }
    }
    std::sort(q+1,q+1+qsz,cmp);
    int l=1,r=0;now=0;
    For(i,1,qsz) {
        while(now<q[i].vs) { ++now;change(u[now].pos,u[now].now); }
        while(now>q[i].vs) { change(u[now].pos,u[now].pre);--now; }
        while(l<q[i].l) cal(l++);
        while(l>q[i].l) cal(--l);
        while(r<q[i].r) cal(++r);
        while(r>q[i].r) cal(r--);
        ans[q[i].id]=res;
    }
    For(i,1,qsz) printf("%d\n",ans[i]);

#ifdef MengLan
    printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
    return 0;
}
