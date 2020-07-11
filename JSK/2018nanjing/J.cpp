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

const int maxn=2e7+10;
int f[maxn];
int s[maxn];
int p[maxn];
bool vis[maxn];

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    int cnt=1;p[1]=2;
    FOR(i,2,maxn){
        if(!vis[i]) p[++cnt]=i,f[i]=1;
        for(int j=1;j<=cnt&&i*p[j]<maxn;++j){
            vis[i*p[j]]=true;
            if(i%p[j]!=0) f[i*p[j]]=f[i]+1;
            else{f[i*p[j]]=f[i];break;}
        }
    }
    for(int i=2;i*i<maxn;++i) if(!vis[i]){
        int t=i*i;
        for(int j=t;j<maxn;j+=t) f[j]--;
    }
    FOR(i,1,maxn) f[i]=1<<f[i];
    for(ll i=2;i*i*i<maxn;++i){
        if(!vis[i]){
            int t=i*i*i;
            for(int j=t;j<maxn;j+=t) f[j]=0;
        }
    }
    FOR(i,1,maxn) s[i]=s[i-1]+f[i];

    int T;scanf("%d",&T);
    while(T--){
        int n;scanf("%d",&n);
        printf("%d\n",s[n]);
    }

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
