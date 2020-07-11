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

const int maxn=1e5+10;
int n,d;
//int dp[maxn];
int in[maxn];
int vis[maxn];

int find(int x){
    int ret=0;
    for(int i=x>=d?x-d:0;i<=x+d;++i) ret=std::max(ret,vis[i]);
    return ret;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    int T;scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&d);
        //memset(dp,0,sizeof(dp));
        memset(vis,0,sizeof(vis));
        int ans=0;
        FOR(i,0,n){
            int x;scanf("%d",&x);
            int max=find(x)+1;
            vis[x]=max;
            ans=std::max(max,ans);
        }
        printf("%d\n",ans);
    }

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
