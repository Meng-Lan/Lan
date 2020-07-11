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
struct Edge { int from,to,use; };
std::vector<Edge> edges;
std::vector<int> G[maxn];

typedef std::pair<P,int> PI;
typedef std::pair<PI,PI> PP;
PP in[maxn];
int n;
int sz;
inline int ID(std::map<PI,int> &m,PI x) {
	if(m.find(x)!=m.end()) return m[x];
	return m[x]=++sz;
}
inline int ID(std::map<P,int> &m,P x) {
	if(m.find(x)!=m.end()) return m[x];
	return m[x]=++sz;
}

std::set<P> s;
void AddEdge(int from,int to) {
	if(s.count(P(from,to))) return;
	edges.pb({ from,to,0 });s.insert(P(from,to));
	edges.pb({ to,from,0 });s.insert(P(to,from));
	auto v=edges.size();
	G[from].pb(v-2);
	G[to].pb(v-1);
}

int vis[maxn];

bool dfs(int u,int dep) {
	if(vis[u]&&dep-vis[u]>=3) return true;
	vis[u]=dep;
	for(auto &v:G[u]) if(!edges[v].use&&!edges[v^1].use) {
		edges[v].use=1;
		//if(vis[edges[v].to]) return true;
		if(dfs(edges[v].to,dep+1)) return true;
	}
	return false;
}

void solve1() {
	std::map<PI,int> m;
	//PV(1);
	FOR(i,0,n) {
		int u=ID(m,in[i].fi),v=ID(m,in[i].se);
		//printf("u:%d v:%d\n",u,v);
		if(u==v) continue;
		AddEdge(u,v);
	}
	if(dfs(1,1)) puts("True closed chains");
	else puts("No true closed chains");
}

void solve2() {
	std::map<P,int> m;
	sz=0;
	for(auto &v:G) v.clear();
	edges.clear();s.clear();
	//PV(2);
	FOR(i,0,n) {
		int u=ID(m,in[i].fi.fi),v=ID(m,in[i].se.fi);
		//printf("u:%d v:%d\n",u,v);
		if(u==v) continue;
		AddEdge(u,v);
	}
	memset(vis,0,sizeof(vis));
	if(dfs(1,1)) puts("Floor closed chains");
	else puts("No floor closed chains");
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	scanf("%d",&n);
	FOR(i,0,n) {
		int x,y,z;scanf("%d%d%d",&x,&y,&z);
		PI a=PI(P(x,y),z);
		scanf("%d%d%d",&x,&y,&z);
		PI b=PI(P(x,y),z);
		in[i]=PP(a,b);
	}
	solve1();
	solve2();

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}
