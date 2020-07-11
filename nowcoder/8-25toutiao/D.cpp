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

const int INF=2e9;
const int maxn=1e3+10;
int n,t;
std::vector<int> in;
int g[maxn];
int d[maxn];

std::vector<int> LIS(std::vector<int> &t,int &ans){
    int len=t.size();
    For(i,1,len) g[i]=INF;
    int max=0;
    FOR(i,0,len){
        int x=std::upper_bound(g+1,g+1+len,t[i])-g;
        d[i]=x;
        g[x]=t[i];
        max=std::max(x,max);
    }
    ans=max;
    std::vector<int> ret;
    for(int i=len-1;i>=0;--i) if(d[i]==max){
        ret.pb(t[i]);
        --max;
    }
    return ret;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    scanf("%d%d",&n,&t);
    FOR(i,0,n) {int x;scanf("%d",&x);in.pb(x);}
    std::map<int,int> m;
    FOR(i,0,n) m[in[i]]++;
    int max=0;
    for(auto &v:m) max=std::max(max,v.second);
    ll ans=0;
    int T;
    auto ret=LIS(in,T);
    ans+=T;
    --t;
    ans+=t*max;
    printf("%lld\n",ans);

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
