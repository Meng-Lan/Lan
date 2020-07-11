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

const int INF=1e9+7;
const int maxn=5e3+10;
int d[maxn][maxn];
int sum[maxn];
char s[maxn];

inline void up(int &x,int y) { x+=y;if(x>=INF) x-=INF; }

int main() {
#ifdef MengLan
    int Beginning=clock();
    //freopen("in","r",stdin);
    //freopen("out","w",stdout);
#endif // MengLan

    int n;
    scanf("%d",&n);
    For(i,1,n) scanf(" %c",s+i);
    for(int i=n;i>=1;--i) {
        if(i==n) {
            for(int j=0;j<n;++j) d[i][j]=1;
            sum[0]=1;
            for(int j=1;j<n;++j) { sum[j]=sum[j-1];up(sum[j],d[i][j]); }
        }
        else {
            if(s[i]=='f') {
                for(int j=0;j<n;++j)
                    d[i][j]=d[i+1][j+1];
            }
            else {
                for(int j=0;j<n;++j)
                    up(d[i][j],sum[j]);
            }
            sum[0]=d[i][0];
            for(int j=1;j<n;++j) { sum[j]=sum[j-1];up(sum[j],d[i][j]); }
            //FOR(j,0,n) printf("[%d,%d] d:%d s:%d\n",i,j,d[i][j],sum[j]);
        }
    }
    printf("%d\n",d[1][0]);

#ifdef MengLan
    printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
    return 0;
}