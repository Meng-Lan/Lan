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

std::string s;
int n,r,b,R,B;
std::vector<P> ans;

bool find(int l,int r,int nr,int nb) {
	for(;l<=r;) {
		int L=l,R=r;
		nb=b;nr=::r;
		while(L<=R&&(nb||nr)) {
			if(s[L]=='B'&&nb) ++L,--nb;
			else if(s[L]=='R'&&nr) ++L,--nr;
			else break;
			//printf("1 L:%d R:%d\n",L,R);
		}
		while(L<=R&&(nb||nr)) {
			if(s[R]=='B'&&nb) --R,--nb;
			else if(s[R]=='R'&&nr) --R,--nr;
			else if(L-1>=l) {
				if(s[L-1]=='B') ++nb,--L;
				else ++nr,--L;
			}
			//printf("2 L:%d R:%d\n",L,R);
		}
		//printf("L:%d R:%d\n",L,R);
		if(nb||nr) return false;
		ans.pb({ L,R });
		l=L;r=R;
	}
	return true;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	cin>>n>>r>>b>>s;
	for(auto &v:s) v=='B'?++B:++R;
	if(B%b||R%r||B/b!=R/r||n%(r+b)) { puts("NO");return 0; }
	if(find(0,n-1,r,b)) {
		puts("YES");
		printf("%d\n",(int)ans.size());
		int l=0,r=n;
		for(auto &v:ans) {
			for(int i=l;i<v.fi;++i) printf("%d ",i+1);
			for(int i=v.se+1;i<r;++i) printf("%d ",i+1);
			l=v.fi;r=v.se;
			printf("\n");
		}
	}
	else puts("NO");

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}
