#include<bits/stdc++.h>
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

const int mod=1e9+7;
const int maxn=1e5+10;
std::vector<P> G[maxn];
int n;
ll ans;
int sz[maxn];
ll f[maxn];

void dfs(int u,int fa){
    sz[u]=1;
    for(auto &v:G[u]) if(v.fi!=fa){
        dfs(v.fi,u);
        sz[u]+=sz[v.fi];
        ans=(ans+1LL*sz[v.fi]*(n-sz[v.fi])%mod*f[n-1]%mod*v.se%mod)%mod;
    }
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    f[0]=1;
    FOR(i,1,maxn) f[i]=f[i-1]*i%mod;
    while(scanf("%d",&n)==1&&n){
        For(i,1,n) G[i].clear();
        ans=0;
        memset(sz,0,sizeof(int)*(n+2));
        FOR(i,1,n){
            int x,y,l;scanf("%d%d%d",&x,&y,&l);
            G[x].pb(P(y,l));
            G[y].pb(P(x,l));
        }
        dfs(1,0);
        printf("%lld\n",ans*2%mod);
    }


#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
