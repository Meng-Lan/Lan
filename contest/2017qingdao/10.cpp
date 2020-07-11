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
#define PA(name,init,len) cout<<#name"["<<#len"]=";FOR(_,init,len) cout<<name[_]<<" \n"[_==(len-1)];
#define Pa(name,init,len) cout<<#name"["<<#len"]=";For(_,init,len) cout<<name[_]<<" \n"[_==(len)];
#define PV(name) cout<<#name"="<<name<<'\n';

const int maxn=1e5+10;
struct Lan {
	int L,R,v;
}lan[maxn];
int n,pos[maxn];

void Link(int L,int R) {
	lan[L].R=R;lan[R].L=L;
}

/*
1
10
1 1 2 2 3 3 2 2 1 1

*/

void solve() {
	std::vector<int> deal;
	for(int i=1;lan[i].v<maxn;) {
		int j=lan[i].L,k=i,l=lan[i].R;
		if(lan[j].v<=lan[k].v&&lan[k].v<=lan[l].v) {
			i=l;continue;
		}
		while(lan[j].v>lan[k].v||lan[k].v>lan[l].v) {
			j=k;k=l;l=lan[l].R;
		}
		j=lan[i].L;
		deal.pb(j);
		deal.pb(k);
		Link(j,k);
		i=l;
		//for(int i=lan[0].R,j=1;lan[i].v<n+1;++j,i=lan[i].R) printf("%d ",lan[i].v);puts("");
	}
	std::vector<int> now;
	for(;!deal.empty();) {
		int to=0;
		for(auto &i:deal) if(i>to) {
			int j=lan[i].L,k=i,l=lan[i].R;
			if(lan[j].v<=lan[k].v&&lan[k].v<=lan[l].v) continue;
			while(lan[j].v>lan[k].v||lan[k].v>lan[l].v) {
				j=k;k=l;l=lan[l].R;
			}
			j=lan[i].L;
			now.pb(j);
			now.pb(k);
			Link(j,k);
			to=l;
		}
		//for(int i=lan[0].R,j=1;lan[i].v<n+1;++j,i=lan[i].R) printf("%d ",lan[i].v);puts("");
		deal=now;now.clear();
	}
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	int T;scanf("%d",&T);
	while(T--) {
		scanf("%d",&n);
		For(i,1,n) { int x;scanf("%d",&x);lan[i].v=x; }
		For(i,1,n) { lan[i].L=i-1;lan[i].R=i+1; }
		lan[0].v=0;lan[0].R=1;
		lan[n+1].v=maxn;lan[n+1].L=n;lan[n+1].R=n+2;
		lan[n+2].v=maxn;lan[n+2].L=n+1;lan[n+2].R=n+2;
		solve();
		int ans=0;
		for(int i=lan[0].R;lan[i].v<maxn;++ans,i=lan[i].R);
		printf("%d\n",ans);
		for(int i=lan[0].R,j=1;lan[i].v<maxn;++j,i=lan[i].R) printf("%d ",lan[i].v);puts("");
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}
