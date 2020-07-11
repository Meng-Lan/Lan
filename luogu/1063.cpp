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

const int maxn=200+10;
int in[maxn];
int d[maxn][maxn];
int n;

inline int cost(int i,int j,int k) { return i*j*k; }

int dp(int *t) {
    memset(d,0,sizeof(d));
    //FOR(i,0,n) printf("%d%c",t[i],i==n-1?'\n':' ');
    For(k,2,n) {
        FOR(i,0,n) for(int j=i+1;j<i+k&&j<n;++j)
            d[i][i+k]=std::max(d[i][i+k],d[i][j]+d[j][i+k]+cost(t[i],t[j],t[i+k]));
    }
    return d[0][n];
}

int main() {
#ifdef MengLan
    int Beginning=clock();
    //freopen("in","r",stdin);
    //freopen("out","w",stdout);
#endif // MengLan

    scanf("%d",&n);
    For(i,1,n) scanf("%d",in+i);
    For(i,1,n) in[i+n]=in[i];
    int ans=0;
    For(i,1,n) ans=std::max(ans,dp(in+i));
    printf("%d\n",ans);

#ifdef MengLan
    printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
    return 0;
}
