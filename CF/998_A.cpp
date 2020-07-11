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

const int maxn=11;
int in[maxn],n;

bool check(int a,int b){
    int ca=0,cb=0;
    int sa=0,sb=0;
    FOR(i,0,n) if(a&(1<<i)){++ca;sa+=in[i];}
    FOR(i,0,n) if(b&(1<<i)){++cb;sb+=in[i];}
    // PV(a);PV(b);PV(ca);PV(cb);PV(sa)PV(sb)
    if(ca==0||cb==0) return false;
    if(sa==sb) return false;
    printf("%d\n",ca);
    FOR(i,0,n) if(a&(1<<i)) printf("%d ",i+1);
    return true;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    cin>>n;
    FOR(i,0,n) cin>>in[i];
    int sum=(1<<n)-1;
    bool ok=false;
    FOR(i,0,(1<<n)) if(check(i,sum^i)) {ok=true;break;}
    if(!ok) puts("-1");

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
