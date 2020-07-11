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

const int maxn=52+10;
const ll INF=1LL<<60;
int n,G[maxn][maxn],src,dest,p;
int mark[maxn];
ll d[maxn];

int read_node() {
	char ch[9];
	scanf("%s",ch);
	if(ch[0]>='A'&&ch[0]<='Z') return ch[0]-'A';
	return ch[0]-'a'+26;
}

char format_node(int u) {
	return u<26?u+'A':u+'a'-26;
}

ll forward(ll item,int next) {
	if(next<26) return item-(item+19)/20;
	return item-1;
}

ll back(int u) {
	if(u>=26) return d[u]+1;
	ll x=d[u]*20/19;
	while(forward(x,u)<d[u]) ++x;
	return x;
}

void solve() {
	n=52;
	memset(mark,0,sizeof(mark));
	mark[dest]=1;
	d[dest]=p;
	FOR(i,0,n) if(i!=dest) {
		d[i]=INF;
		if(G[i][dest]) d[i]=back(dest);
	}

	while(!mark[src]) {
		int minu=-1;
		FOR(i,0,n) if(!mark[i]) if(minu<0||d[i]<d[minu]) minu=i;
		mark[minu]=1;
		FOR(i,0,n) if(!mark[i]) if(G[i][minu]) d[i]=std::min(d[i],back(minu));
	}

	printf("%lld\n",d[src]);
	printf("%c",format_node(src));
	int u=src;
	ll item=d[src];
	while(u!=dest) {
		int next=0;
		for(;next<n;++next) if(G[u][next]&&forward(item,next)>=d[next]) break;
		item=d[next];
		printf("-%c",format_node(next));
		u=next;
	}
	puts("");
}

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	int kase=0;
	while(scanf("%d",&n)==1&&n>=0) {
		memset(G,0,sizeof(G));
		FOR(i,0,n) {
			int u=read_node();
			int v=read_node();
			if(u!=v) G[u][v]=G[v][u]=1;
		}
		scanf("%d",&p);
		src=read_node();
		dest=read_node();
		printf("Case %d:\n",++kase);
		solve();
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}