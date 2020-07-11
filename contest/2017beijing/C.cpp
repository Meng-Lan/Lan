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

const int maxn=305;
const int INF=1e9;
int S[maxn][maxn],in[maxn][maxn],mi[maxn][maxn],n,m,p;
inline void expand(int i,int &b0,int &b1) {
	b0=i&1;i>>=1;
	b1=i&1;
}

inline int sign(int b0,int b1) { return (b0+b1)&1==1?1:-1; }

inline int sum(int x1,int x2,int y1,int y2) {
	int dx=x2-x1+1,dy=y2-y1+1;
	int s=0;
	for(int i=0;i<4;++i) {
		int b0,b1;
		expand(i,b0,b1);
		s-=S[x2-b0*dx][y2-b1*dy]*sign(b0,b1);
	}
	//printf("x1:%d x2:%d y1:%d y2:%d s:%d\n",x1,x2,y1,y2,s);
	return s;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	while(scanf("%d%d%d",&n,&m,&p)==3) {
		memset(S,0,sizeof(S));
		For(i,1,n) For(j,1,m) scanf("%d",in[i]+j),S[i][j]=in[i][j];
		/*for(int i=n;i>=1;--i) {
			if(i==n) for(int j=1;j<=m;++j) mi[i][j]=S[i][j];
			else for(int j=1;j<=m;++j) mi[i][j]=std::min(S[i][j],mi[i+1][j]);
		}*/
		int ans=-1e9;
		For(i,1,n) {
			int b0,b1;
			For(j,1,m) {
				For(k,1,3) {
					expand(k,b0,b1);
					S[i][j]+=S[i-b0][j-b1]*sign(b0,b1);
				}
				//printf("%d ",S[i][j]);
			}
			//puts("");
			//printf("#i:%d\n",i);
			for(int j=i;j>=1;--j) {
				if(j==i) for(int k=1;k<=m;++k) mi[j][k]=in[j][k];
				else for(int k=1;k<=m;++k) mi[j][k]=std::min(mi[j][k],mi[j+1][k]);
			}
			/*for(int j=1;j<=i;++j) {
				printf("#%d :",j);
				for(int k=1;k<=m;++k) printf("%d ",mi[j][k]);puts("");
			}*/
			For(j,1,i) {
				int M=0,x=1;
				std::deque<int> q;
				For(k,1,m) {
					int s=sum(j,i,1,k);
					while(!q.empty()&&q.front()>mi[j][k]) q.pop_back();
					if(q.empty()||mi[j][k]<q.front()) q.push_back(mi[j][k]);
					ans=std::max(ans,s-M+p-q.front());
					if(j!=1||i!=n||x!=1||k!=m) ans=std::max(ans,s-M+std::max(0,p-q.front()));
					//printf("j:%d i:%d x:%d k:%d s:%d M:%d mi:%d ans:%d\n",j,i,x,k,s,M,q.front(),ans);
					if(s+std::max(0,p-q.front())<M) {
						M=s;x=k+1;q.clear();
					}
				}
			}
		}
		printf("%d\n",ans);
	}

#ifdef MengLan
	//printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}
/*
3 3 -11
100 -12 -13
-14 10 10
-15 10 10

*/