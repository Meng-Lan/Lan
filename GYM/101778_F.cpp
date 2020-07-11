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

const int maxn=105;
const int maxa=505;
int in[maxn][maxn],d[maxn][maxn][maxa];
int n,m,q;

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    int T;read(T);
    while(T--){
        read(n);read(m);read(q);//scanf("%d%d%d",&n,&m,&q);
        memset(in,0,sizeof(in));
        memset(d,0,sizeof(d));
        int ma=0;
        For(i,1,n) For(j,1,m) read(in[i][j]),d[i][j][in[i][j]]=1,ma=std::max(ma,in[i][j]);
        For(i,1,n) For(j,1,m) For(k,1,ma) d[i][j][k]+=d[i][j-1][k];
        For(i,1,n) For(j,1,m) For(k,1,ma) d[i][j][k]+=d[i-1][j][k];
        while(q--){
            int a,b,c,e;read(a);read(b);read(c);read(e);//scanf("%d%d%d%d",&a,&b,&c,&e);
            int cnt=((c-a+1)*(e-b+1)+1)/2;
            int ans=1;
            For(i,1,ma){
                int t=d[c][e][i]-d[a-1][e][i]-d[c][b-1][i]+d[a-1][b-1][i];
                if(cnt){cnt-=t;ans=i;}
                if(cnt<=0) break;
            }
            printf("%d\n",ans);
        }
    }

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
