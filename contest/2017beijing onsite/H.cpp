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

const int maxn=155;
int n,m,p;
int in[maxn][maxn],sum[maxn],min[maxn],l[maxn],r[maxn],u[maxn],d[maxn];

int main() {
#ifdef MengLan
    int Beginning=clock();
    //freopen("in","r",stdin);
    //freopen("out","w",stdout);
#endif // MengLan

    while(scanf("%d%d%d",&n,&m,&p)==3) {
        For(i,1,n) For(j,1,m) scanf("%d",in[i]+j);
        memset(l,0x80,sizeof(l));
        memset(r,0x80,sizeof(r));
        memset(u,0x80,sizeof(u));
        memset(d,0x80,sizeof(d));
        For(i,1,n) {
            memset(sum,0,sizeof(sum));
            //memset(min,0x80,sizeof(min));
            For(j,i,n) {
                For(k,1,m) sum[k]+=in[j][k];
                int ss=0,mi=0;
                For(k,1,m) { ss+=sum[k];l[k]=std::max(l[k],ss-mi);mi=std::min(mi,ss); }
                ss=0,mi=0;
                for(int k=m;k>=1;--k) { ss+=sum[k];r[k]=std::max(r[k],ss-mi);mi=std::min(mi,ss); }
            }
        }
        For(i,1,m) {
            memset(sum,0,sizeof(sum));
            //memset(min,0x80,sizeof(min));
            For(j,i,m) {
                For(k,1,n) sum[k]+=in[k][j];
                int ss=0,mi=0;
                For(k,1,n) { ss+=sum[k];u[k]=std::max(u[k],ss-mi);mi=std::min(mi,ss); }
                ss=0,mi=0;
                for(int k=n;k>=1;--k) { ss+=sum[k];d[k]=std::max(d[k],ss-mi);mi=std::min(mi,ss); }
            }
        }
        For(i,1,m) l[i]=std::max(l[i],l[i-1]);
        for(int i=m;i>=1;--i) r[i]=std::max(r[i],r[i+1]);
        For(i,1,n) u[i]=std::max(u[i],u[i-1]);
        for(int i=n;i>=1;--i) d[i]=std::max(d[i],d[i+1]);
        int max=l[m],ans=max;
        For(i,1,n) For(j,1,m) if(in[i][j]>p) {
            int t=std::max({ u[i-1],d[i+1],l[j-1],r[j+1],max-in[i][j]+p });
            ans=std::min(t,ans);
        }
        printf("%d\n",ans);
    }

#ifdef MengLan
    printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
    return 0;
}
