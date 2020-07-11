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

const int maxn=1e6+10;
bool vis[maxn];

ll f[maxn];
int n;
const int mod=1e9+7;
    
ll qpow(ll a,ll b){
    ll ret=1;
    while(b){
        if(b&1){ret=ret*a%mod;}
        b>>=1;
        a=a*a%mod;
    }
    return ret;
}

ll solve(){
    ll ret=1;
    bool t=false;
    for(int i=2;i<=n;++i) f[i]=i;
    for(int i=2;i<=n;++i){
        if(!vis[i]){
            int cnt=0;
            for(int j=i;j<=n;j+=i){
                vis[j]=true;
                while(f[j]%i==0){f[j]/=i;++cnt;}
            }
            ret*=2*cnt+1;
            if(ret>=mod) t=true;
            ret%=mod;
        }
    }
    int inv=qpow(2,mod-2);
    // PV(inv);
    // PV(ret);
    return ((ret-1)*inv+1)%mod;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    cin>>n;
    cout<<solve()<<'\n';

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
