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
struct Edge { int from,to,dis; }edges[maxn<<1];
std::vector<int> G[maxn];

int pre[maxn],dfs_clock;
std::stack<int> S;
const int maxk=1e5+10;
struct Item {
	int s,b;
	Item(int s,int b) :s(s),b(b) {}
	Item()=default;
	bool operator<(const Item &rhs)const { return s<rhs.s; }
};
std::vector<int> W;
int n,m,k;
void merge(std::vector<int> &V,std::vector<int> B) {
	std::priority_queue<Item> q;
	for(int i=0;i<B.size();++i) q.push(Item(V[0]+B[i],0));
	W.resize(0);
	for(int i=1;i<=k;++i) {
		if(!q.empty()) {
			Item item=q.top();q.pop();
			W.pb(item.s);
			int b=item.b;
			if(b+1<V.size()) q.push(Item(item.s-V[b]+V[b+1],b+1));
		}
	}
	V=W;
}

std::vector<int> res;
int dfs(int u,int fa) {
	int lowu=pre[u]=++dfs_clock;
	for(int &i:G[u]) {
		Edge &e=edges[i];
		if(e.to==fa) continue;
		if(!pre[e.to]) {
			S.push(i);
			int lowv=dfs(e.to,i^1);
			if(lowv>=pre[u]) {
				std::vector<int> B;
				for(;;) {
					Edge &x=edges[S.top()];S.pop();
					B.pb(x.dis);
					if(x.from==u&&x.to==e.to) break;
				}
				if(B.size()>1) merge(res,B);
			}
		}
		else if(pre[e.to]<pre[u]&&i!=fa) {
			S.push(i);
			lowu=std::min(lowu,pre[e.to]);
		}
	}
	return lowu;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	int kase=0;
	res.reserve(100001);
	W.reserve(100001);
	while(scanf("%d%d",&n,&m)==2) {
		int sum=0;dfs_clock=0;
		memset(pre,0,sizeof(pre));
		For(i,1,n) G[i].clear();
		int sz=0;
		FOR(i,0,m) {
			int x,y,z;scanf("%d%d%d",&x,&y,&z);
			edges[++sz]=Edge{ x,y,z };G[x].pb(sz);
			edges[++sz]=Edge{ y,x,z };G[y].pb(sz);
			sum+=z;
		}
		scanf("%d",&k);
		res.resize(0);
		res.pb(0);
		dfs(1,0);
		unsigned ans=0;
		//for(int i=1;i<=A[0];++i) printf("A[%d]=%d\n",i,A[i]);
		for(unsigned i=0;i<res.size();++i) ans+=(i+1)*(sum-res[i]);
		printf("Case #%d: %u\n",++kase,ans);
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}
