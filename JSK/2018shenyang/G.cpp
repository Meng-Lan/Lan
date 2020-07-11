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

ll t[1000],cnt;
void init(ll n){
    cnt=0;
    for(ll i=2;i*i<=n;++i) if(n%i==0){
        t[cnt++]=i;
        while(n%i==0) n/=i;
    }
    if(n>1) t[cnt++]=n;
}
ll n,m;
const ll mod=1e9+7;

ll qpow(ll a,ll b){
    ll ret=1;
    while(b){
        if(b&1) ret=ret*a%mod;
        b>>=1;
        a=a*a%mod;
    }
    return ret;
}

ll inv2,inv6;
inline ll calc(ll &n,const int &tmp){
    ll x=n/tmp;
    return (1LL*tmp*tmp%mod*x%mod*(x+1)%mod*(2*x+1)%mod*inv6%mod+tmp*x%mod*(x+1)%mod*inv2%mod)%mod;
    // return tmp*tmp*x*(x+1)*(2*x+1)/6+tmp*x*(x+1)/2;
}

ll solve(){
    ll ret=0;
    FOR(i,1,1<<cnt){
        int tmp=1,sz=0;
        FOR(j,0,cnt){
            if((i>>j)&1){++sz;tmp*=t[j];}
        }
        if(sz&1) ret+=calc(n,tmp);
        else ret-=calc(n,tmp);
        // printf("n:%lld tmp:%d cnt:%d ret:%lld\n",n,tmp,cnt,ret);
    }
    ret%=mod;
    ll sum=calc(n,1);
    // PV(sum)
    return (sum-ret+mod)%mod;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    inv2=qpow(2,mod-2);
    inv6=qpow(6,mod-2);
    while(scanf("%lld%lld",&n,&m)==2){
        init(m);
        ll ans=solve();
        printf("%lld\n",ans);
    }

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
