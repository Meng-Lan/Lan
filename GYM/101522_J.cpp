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

const int maxn=205;
const ll INF=1e18;
ll d[maxn][maxn][maxn][3];
int b,r,s;
ll k;

ll dp(int b,int r,int s,int fr) {
	if(b<0||r<0||s<0) return 0;
	//printf("b:%d r:%d s:%d fr:%d ans:%lld\n",b,r,s,fr,d[b][r][s]);
	if(d[b][r][s][fr]>=0) return d[b][r][s][fr];
	ll &ans=d[b][r][s][fr];ans=0;
	if(fr==0&&!r&&!s) return ans;
	if(fr==1&&!b&&!s) return ans;
	if(fr==2&&!b&&!r) return ans;
	if(b+r+s==1) return ans=1;
	if(fr!=0&&b) ans+=dp(b-1,r,s,0);
	if(fr!=1&&r) ans+=dp(b,r-1,s,1);
	if(fr!=2&&s) ans+=dp(b,r,s-1,2);
	if(ans>=INF) ans=INF;
	//printf("b:%d r:%d s:%d fr:%d ans:%lld\n",b,r,s,fr,ans);
	return ans;
}

void print(int b,int r,int s,int fr,ll k) {
	if(b<0||r<0||s<0) return;
	if(b+r+s==1) {
		if(b) printf("B");
		if(r) printf("R");
		if(s) printf("S");
		return;
	}
	if(fr!=0&&b) {
		if(k>dp(b-1,r,s,0)) k-=dp(b-1,r,s,0);
		else { printf("B");print(b-1,r,s,0,k);return; }
	}
	if(fr!=1&&r) {
		if(k>dp(b,r-1,s,1)) k-=dp(b,r-1,s,1);
		else { printf("R");print(b,r-1,s,1,k);return; }
	}
	if(fr!=2&&s) {
		printf("S");print(b,r,s-1,2,k);
	}
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	memset(d,-1,sizeof(d));
	cin>>b>>r>>s>>k;
	ll sum=0;
	sum+=dp(b-1,r,s,0);
	sum+=dp(b,r-1,s,1);
	sum+=dp(b,r,s-1,2);
	if(sum<k) puts("None");
	else print(b,r,s,3,k),printf("\n");

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}
