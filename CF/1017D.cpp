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

const int maxn=(1<<12)+10;
const int maxm=5e5+10;
int n,q,m;
int w[15];
int num[maxn];
std::vector<P> in[maxn];
int ans[maxm];
int ss[105];

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    scanf("%d%d%d",&n,&q,&m);
    FOR(i,0,n) scanf("%d",w+i);
    char s[15];
    FOR(i,0,q){
        scanf("%s",s);
        int hash=0;
        FOR(j,0,n) if(s[j]=='1') hash|=1<<j;
        num[hash]++;
    }

    FOR(i,0,m){
        int v;
        scanf("%s%d",s,&v);
        int h=0;
        FOR(j,0,n) if(s[j]=='1') h|=1<<j;
        in[h].pb(P(v,i));
    }

    int S=1<<n;
    FOR(i,0,S) if(!in[i].empty()){
        memset(ss,0,sizeof(ss));
        FOR(j,0,S)if(num[j]){
            int ret=0;
            FOR(k,0,n) if(!(((i^j)>>k)&1)) {ret+=w[k];}
            if(ret<=100) ss[ret]+=num[j];
        }
        For(i,1,100) ss[i]+=ss[i-1];
        for(auto &v:in[i]){
            ans[v.se]=ss[v.fi];
        }
    }

    FOR(i,0,m) printf("%d\n",ans[i]);


#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
