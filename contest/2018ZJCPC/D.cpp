#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<sstream>
#include<fstream>
#include<vector>
#include<list>
#include<deque>
#include<stack>
#include<queue>
#include<map>
#include<set>
#include<cmath>
#include<utility>
#include<numeric>
#include<iterator>
#include<algorithm>
#include<functional>
#include<ctime>
#include<cassert>
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

const int maxn=1e3+10;
ll d[maxn][maxn];
typedef std::pair<char,int> PCI;
PCI in[maxn];
int n;
char s[maxn];
ll ss[maxn];

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    int T;scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        scanf(" %s",s+1);
        For(i,1,n) scanf("%d",&in[i].se),in[i].fi=s[i];
        memset(ss,0,sizeof(ss));
        For(i,1,n) if(in[i].fi==')') ss[i]=ss[i-1]+in[i].se; else ss[i]=ss[i-1];
        int cnt=0;
        int now,old;
        memset(d,0,sizeof(d));
        For(i,1,n) if(in[i].fi=='('){
            if(!cnt){
                For(j,i+1,n) if(in[j].fi==')') d[i][j]=in[i].se*(ss[j]-ss[i-1]);else d[i][j]=d[i][j-1];
                old=i;++cnt;
            }
            else{
                now=i;
                ll max=0;
                FOR(j,1,i) max=std::max(max,d[old][j]);
                d[now][i]=max;
                For(j,i+1,n) if(in[j].fi==')') {
                    max=std::max(max,d[old][j]);
                    d[now][j]=in[now].se*(ss[j]-ss[i-1])+max;
                }
                else d[i][j]=d[i][j-1];
                old=i;
            }
        }
        ll max=0;
        For(i,1,n) max=std::max(max,d[old][i]);
        printf("%lld\n",max);
    }


	return 0;
}
