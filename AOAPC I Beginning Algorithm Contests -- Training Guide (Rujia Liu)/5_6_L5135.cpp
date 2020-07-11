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
#define mp std::make_pair
ll Factorial(ll i) { return i > 1?i*Factorial(i-1):1; }
ll Combination(ll n,ll r) {
	if(n-r < r) r=n-r;
	ll ansn=1,ansr=1;
	for(ll i=n-r+1; i<=n; ++i) ansn*=i;
	for(ll j=1; j<=r; ++j) ansr*=j;
	return ansn/ansr;
}
ll gcd(ll a,ll b) { return b?gcd(b,a%b):a; }
ll lcm(ll a,ll b) { return a/gcd(a,b)*b; }
std::vector<int> Eratosthenes(const int len,int *vis) {
	memset(vis,0,sizeof(int)*len);
	std::vector<int> prime;
	int m=(int)sqrt(len+0.5);
	For(i,2,m) if(!vis[i]) for(int j=i*i; j < len; j+=i) vis[j]=1;
	FOR(i,2,len) if(!vis[i]) prime.push_back(i);
	return prime;
}
void phi_table(int n,int *phi) {
	For(i,2,n) phi[i]=0;
	phi[1]=1;
	For(i,2,n) if(!phi[i])
		for(int j=i; j<=n; j+=i) {
			if(!phi[j]) phi[j]=j;
			phi[j]=phi[j]/i*(i-1);
		}
}

const int maxn=100000+10;
struct Edge {
	int u,v;
	Edge(int u,int v) :u(u),v(v) {}
	Edge() :Edge(0,0) {}
};
std::vector<int> G[maxn];
int n;

int pre[maxn],iscut[maxn],bccno[maxn],bcc_cnt,dfs_clock;
std::vector<int> bcc[maxn];
std::stack<Edge> s;

int dfs(int u,int fa) {
	int lowu=pre[u]=++dfs_clock;
	int child=0;
	for(auto &v:G[u]) {
		Edge e(u,v);
		if(!pre[v]) {
			s.push(e);
			++child;
			int lowv=dfs(v,u);
			lowu=std::min(lowu,lowv);
			if(lowv>=pre[u]) {
				iscut[u]=true;
				++bcc_cnt;
				bcc[bcc_cnt].clear();
				for(;;) {
					Edge e=s.top();s.pop();
					if(bccno[e.u]!=bcc_cnt) { bccno[e.u]=bcc_cnt;bcc[bcc_cnt].push_back(e.u); }
					if(bccno[e.v]!=bcc_cnt) { bccno[e.v]=bcc_cnt;bcc[bcc_cnt].push_back(e.v); }
					if(e.u==u&&e.v==v) break;
				}
			}
		}
		else if(pre[v]<pre[u]) {
			s.push(e);
			lowu=std::min(lowu,pre[v]);
		}
	}
	if(fa<0&&child==1) iscut[u]=false;
	return lowu;
}

void find_bcc(int n) {
	memset(pre,0,sizeof(pre));
	memset(iscut,0,sizeof(iscut));
	memset(bccno,0,sizeof(bccno));
	dfs_clock=bcc_cnt=0;
	dfs(0,-1);
}

struct ID {
	std::map<int,int> m;
	int cnt;
	ID() :cnt(0) {}
	int get(int x) {
		if(!m.count(x)) m[x]=cnt++;
		return m[x];
	}
};

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	int kase=0;
	while(scanf("%d",&n)==1&&n) {
		For(i,0,n*2) G[i].clear();
		ID id;
		FOR(i,0,n) {
			int u,v;scanf("%d%d",&u,&v);
			u=id.get(u);v=id.get(v);
			G[u].push_back(v);G[v].push_back(u);
		}

		find_bcc(n);

		ll ans1=0,ans2=1;
		For(i,1,bcc_cnt) {
			int cut_cnt=0;
			for(auto &j:bcc[i]) if(iscut[j]) ++cut_cnt;
			if(cut_cnt==1) {
				ans1++;ans2*=(ll)(bcc[i].size()-cut_cnt);
			}
		}
		if(bcc_cnt==1) {
			ans1=2;ans2=bcc[1].size()*(bcc[1].size()-1)/2;
		}
		printf("Case %d: %lld %lld\n",++kase,ans1,ans2);
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}