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

const int maxn=(1<<20)+10;
const int N=25;
ll S[maxn];
int n;
int a[N],b[N],s[N],p[N];
bool vis[maxn];
int q[maxn],front,end;

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    scanf("%d",&n);
    FOR(i,0,n){
        scanf("%d%d%d",a+i,b+i,s+i);
        FOR(j,0,s[i]){int t;scanf("%d",&t);p[i]|=1<<(t-1);}
    }
    q[end++]=0;
    while(front<end){
        int u=q[front++];
        for(int i=0;i<n;++i) {
            if((!((u>>i)&1))&&((u&p[i])==p[i])){
                int v=u|(1<<i);
                int t=0;
                FOR(j,0,n) if((v>>j)&1) ++t;
                ll add=(ll)a[i]*t+b[i];
                S[v]=std::max(S[v],S[u]+add);
                if(!vis[v]) {q[end++]=v;vis[v]=true;}
            }
        }
    }
    ll ans=0;
    for(int i=0;i<(1<<n);++i) {ans=std::max(ans,S[i]);}
    printf("%lld\n",ans);

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
