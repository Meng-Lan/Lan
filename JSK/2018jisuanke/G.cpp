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

const int mod=1e9+7;
const int maxn=1e5+10;
char s[maxn],t[maxn];
int c[255],d[255];
int ns,nt;

ll f[maxn],invf[maxn];

ll qpow(ll a,ll b){
    ll ret=1;
    while(b){
        if(b&1) ret=a*ret%mod;
        b>>=1;
        a=a*a%mod;
    }
    return ret;
}

const int b='a';
const int e='z';

bool check(){For(i,b,e) if(c[i]<d[i]) return false;return true;}

int solve(){
    ns=strlen(s);
    nt=strlen(t);
    // getnxt();
    memset(c,0,sizeof(c));
    memset(d,0,sizeof(d));
    FOR(i,0,ns) c[s[i]]++;
    FOR(i,0,nt) d[t[i]]++;
    f[0]=1;
    FOR(i,1,maxn) f[i]=f[i-1]*i%mod;
    invf[maxn-1]=qpow(f[maxn-1],mod-2);
    for(int i=maxn-2;i>=0;--i) invf[i]=invf[i+1]*(i+1)%mod;
    if(!check()) return 0;
    For(i,b,e) c[i]-=d[i];
    ll ans=f[ns-nt+1];
    For(i,b,e) ans=ans*invf[c[i]]%mod;
    return  ans;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    int T;scanf("%d",&T);
    while(T--){
        scanf(" %s %s",s,t);
        printf("%d\n",solve());
    }

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
