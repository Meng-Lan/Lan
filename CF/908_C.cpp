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
#include <iomanip>
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

const int maxn=1e3+10;;
const int lan=1e3;
int in[maxn];
int n,r;
long double x[maxn];
long double ans[maxn];
bool vis[maxn];

long double cal(long double a,long double b) {
    return sqrt(a*a-b*b);
}
int main() {
#ifdef MengLan
    int Beginning=clock();
    //freopen("in","r",stdin);
    //freopen("out","w",stdout);
#endif // MengLan

    scanf("%d%d",&n,&r);
    //For(i,1,lan) x[i]=-r;
    FOR(i,0,n) {
        scanf("%d",in+i);
        bool ok=false;
        for(int j=in[i]-r;j<=in[i]+r;++j) if(j>=1&&j<=lan) { if(vis[j]) ok=true; }
        //printf("ok:%d\n",ok);
        if(!ok) { ans[i]=x[in[i]]=r;}
        else {
            long double min=0;
            for(int j=in[i]-2*r;j<=in[i]+2*r;++j) if(j>=1&&j<=lan){
                long double c=cal(2*r,std::abs(j-in[i]))+x[j];
                min=std::max(min,c);
            }
            ans[i]=x[in[i]]=min;
        }
        for(int j=in[i]-r;j<=in[i]+r;++j) if(j>=1&&j<=lan)vis[j]=true;
    }
    FOR(i,0,n) printf("%.8lf%c",(double)ans[i],i==n-1?'\n':' ');

#ifdef MengLan
    printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
    return 0;
}
