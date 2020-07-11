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

const int maxn=5e5+10;
std::vector<int> G[maxn];
int n,vis[maxn],f[maxn];

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	scanf("%d",&n);
	FOR(i,1,n) {
		int u,v;scanf("%d%d",&u,&v);
		G[u].pb(v);G[v].pb(u);
	}
	std::queue<P> q;q.push({ 1,1 });
	int s=-1;vis[1]=1;
	while(!q.empty()) {
		P u=q.front();q.pop();
		s=u.fi;
		for(auto &v:G[u.fi]) if(!vis[v]) {
			q.push({ v,u.se+1 });vis[v]=1;
		}
	}
	memset(vis,0,sizeof(vis));
	int ans=0;
	//PV(s);
	q.push({ s,1 });vis[s]=1;
	while(!q.empty()) {
		P u=q.front();q.pop();
		ans=std::max(ans,u.se);
		for(auto &v:G[u.fi]) if(!vis[v]) {
			q.push({ v,u.se+1 });vis[v]=1;
		}
	}
	//PV(ans);
	f[1]=0;f[2]=1;f[3]=f[4]=2;
	for(int i=5;i<maxn;++i) {
		f[i]=f[(i+1)/2]+1;
	}
	//PA(f,1,10);
	printf("%d\n",f[ans-1]);

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}
