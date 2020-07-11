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

const ll mod=1e9;
const int maxn=5e5+20;
struct Lan{
    int idx,p;
    Lan(int idx=0,int p=0):idx(idx),p(p){}
    bool operator<(const Lan &rhs)const{return p<rhs.p;}
    bool operator<(const int &rhs)const{return p<rhs;}
}b[maxn];
int a[maxn];
int n,m;
ll ss[maxn];

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    int T;scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        FOR(i,0,n) scanf("%d",a+i);
        For(i,1,m) scanf("%d",&b[i].p),b[i].idx=i;
        std::sort(b+1,b+1+m);
        //For(i,1,m) printf("p:%d idx:%d\n",b[i].p,b[i].idx);
        memset(ss,0,sizeof(ss));
        For(i,1,m) ss[i]=ss[i-1]+b[i].idx;
        ll ans=0;
        FOR(i,0,n){
            int r=m;
            For(j,1,30)if(r){
                int p=std::ceil(pow(a[i],1.0/j));
                int l=std::lower_bound(b+1,b+1+m,p)-b;
                ans=(ans+(ss[r]-ss[l-1])%mod*(a[i]/j)%mod)%mod;
                //printf("i:%d j:%d l:%d p:%lld ans:%lld\n",i,j,l,p,ans);
                r=l-1;
            }
        }
        printf("%lld\n",ans);
    }

	return 0;
}
