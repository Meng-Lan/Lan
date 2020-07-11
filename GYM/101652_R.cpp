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

const double eps=1e-6;
const double pi=acos(-1.0);
const int maxn=111;
int n,x;
double v;
struct Lan{
    int l,r;
    double v;
    Lan(int l,int r,double v):l(l),r(r),v(v){}
    Lan():Lan(0,0,0){}
    bool operator<(const Lan &rhs)const{return l<rhs.l;}
}in[maxn];


int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    scanf("%d%d%lf",&n,&x,&v);
    FOR(i,0,n) scanf("%d%d%lf",&in[i].l,&in[i].r,&in[i].v);
    //std::sort(in,in+n);
    double step=pi/18000;
    double ans=1e9;
    int emp=x;
    FOR(i,0,n) emp-=in[i].r-in[i].l;
    double L=-pi/3,R=pi/3;
    FOR(i,0,1000){
        double m=(L+R)/2;
        double vx=cos(m)*v,vy=sin(m)*v;
        double t=emp/vx;
        double sy=t*vy;
        FOR(j,0,n){
            double tt=(in[j].r-in[j].l)/vx;
            sy+=(vy+in[j].v)*tt;
            t+=tt;
        }
        if(std::abs(sy)<eps) ans=std::min(ans,t);
        if(sy<0) L=m;
        else R=m;
    }
    if(ans==1e9) puts("Too hard");
    else printf("%.3f\n",ans);

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
