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

const int maxn=2500+5;
int in[maxn][maxn];
int d[maxn][maxn],x[maxn][maxn],y[maxn][maxn];
int n,m;

int main() {
#ifdef MengLan
    int Beginning=clock();
    //freopen("in","r",stdin);
    //freopen("out","w",stdout);
#endif // MengLan

    read(n),read(m);
    //scanf("%d%d",&n,&m);
    For(i,1,n) For(j,1,m) read(in[i][j]);//scanf("%d",in[i]+j);
    For(i,1,n) For(j,1,m) if(!in[i][j]) x[i][j+1]=x[i][j]+1;
    For(j,1,m) For(i,1,n) if(!in[i][j]) y[i+1][j]=y[i][j]+1;
    int ans=0;
    For(i,1,n) For(j,1,m) if(in[i][j]) 
        d[i][j]=std::min({ d[i-1][j-1],x[i][j],y[i][j] })+1,ans=std::max(ans,d[i][j]);
    memset(x,0,sizeof(x));memset(d,0,sizeof(d));
    For(i,1,n) for(int j=m;j>=1;--j) if(!in[i][j]) x[i][j-1]=x[i][j]+1;
    For(i,1,n) for(int j=m;j>=1;--j) if(in[i][j])
        d[i][j]=std::min({ d[i-1][j+1],x[i][j],y[i][j] })+1,ans=std::max(ans,d[i][j]);
    printf("%d\n",ans);



#ifdef MengLan
    printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
    return 0;
}
