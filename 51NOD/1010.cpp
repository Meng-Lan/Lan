#include<bits/stdc++.h>
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

const ull INF=2e18;
const int maxn=105;
ull a[maxn],b[maxn],c[maxn];
int na,nb,nc;

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    ull t=1;
    do{a[na++]=t;t*=2;}while(t<=INF);
    t=1;
    do{b[nb++]=t;t*=3;}while(t<=INF);
    t=1;
    do{c[nc++]=t;t*=5;}while(t<=INF);
    std::set<ull> s;
    FOR(i,0,na) FOR(j,0,nb){
        if(a[i]*b[j]>=INF) break;
        FOR(k,0,nc){
            if(a[i]*b[j]*c[k]>=INF) break;
            s.is(a[i]*b[j]*c[k]);
        }
    }
    while(*s.begin()<=1) s.erase(s.begin());
    int  T;scanf("%d",&T);
    while(T--){
        ll n;scanf("%lld",&n);
        printf("%llu\n",*s.lower_bound(n));
    }

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
