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

const int maxn=1e5+10;
int n;
int f[maxn];
int l[maxn],r[maxn];
std::vector<int> G[maxn];
int ans[maxn];

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	int T;scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		For(i,1,n) G[i].clear();
		For(i,1,n) scanf("%d",f+i),G[f[i]].pb(i);
		For(i,1,n) scanf("%d%d",l+i,r+i);
		std::vector<P> v;v.pb(P(0,-1));
		For(i,1,n) if(!G[i].empty()){
			std::vector<P> t;
			int d=0;
			for(int j=G[i].size()-1;j>=0;--j){
				while(v.back().fi>G[i][j]) v.pop_back();
				d=std::max({d,v.back().se+1,l[G[i][j]]});
				ans[G[i][j]]=d;
				t.pb(P(G[i][j],d));
			}
			std::reverse(t.begin(),t.end());
			v=t;
		}
		For(i,1,n) printf("%d%c",ans[i],i!=n?' ':'\n');
	}


#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}