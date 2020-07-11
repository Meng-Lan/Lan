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
typedef std::pair<ll,ll> P;
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

const int INF=1e9;
const int maxn=100;
ll f[100];
P ab[maxn];

void gcd(ll a,ll b,ll &d,ll &x,ll &y){
    if(!b) {d=a;x=1;y=0;}
    else{gcd(b,a%b,d,y,x);y-=x*(a/b);}
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    f[1]=1;f[2]=1;
    int maxk;
    for(int i=3;;++i){
        f[i]=f[i-1]+f[i-2];
        if(f[i]>INF) {maxk=i;break;}
    }
    ab[1]=P(1,0);ab[2]=P(0,1);ab[3]=P(1,1);
    FOR(i,4,maxk) ab[i]=P(ab[i-1].fi+ab[i-2].fi,ab[i-1].se+ab[i-2].se);
    int T;scanf("%d",&T);
    while(T--){
        int n;scanf("%d",&n);
        ll x=0,y=n;
        FOR(i,3,maxk) if(n>=f[i]){
            int g=gcd(ab[i].fi,ab[i].se);
            //PV(g);
            if(n%g==0){
                ll d=-1,tx=0,ty=0;
                gcd(ab[i].fi,ab[i].se,d,tx,ty);
                //if(d!=1) PV(d);
                tx/=d;ty/=d;
                tx*=n;ty*=n;
                int L=-INF,R=INF;
                while(L<R){
                    int m=L+(R-L+1)/2;
                    if(tx+ab[i].se*m<=ty-ab[i].fi*m) L=m;
                    else R=m-1;
                }
                //PV(L)
                tx+=ab[i].se*L;ty-=ab[i].fi*L;
                if(tx>0&&ty>0&&ty<=y) x=tx,y=ty;
            }
        }
        cout<<x<<' '<<y<<endl;
    }

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
