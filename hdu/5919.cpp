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

const int maxn=2e5+10;
struct Lan {
	int l,r,v;
}t[maxn*36];
int in[maxn],last[maxn],nxt[maxn],n,m,rt[maxn],sz,ans;

void update(int &x,int y,int l,int r,int pos,int v) {
	x=++sz;t[x]=t[y];t[x].v+=v;
	if(l==r) return;
	int m=l+(r-l)/2;
	if(pos<=m) update(t[x].l,t[y].l,l,m,pos,v);
	else update(t[x].r,t[y].r,m+1,r,pos,v);
}

int query(int x,int l,int r,int L,int R) {
	if(L<=l&&r<=R) return t[x].v;
	int m=l+(r-l)/2;
	int ans=0;
	if(L<=m) ans+=query(t[x].l,l,m,L,R);
	if(R>m) ans+=query(t[x].r,m+1,r,L,R);
	return ans;
}

int findans(int x,int l,int r,int k) {
	if(l==r) return l;
	int m=l+(r-l)/2;
	if(t[t[x].l].v>=k) return findans(t[x].l,l,m,k);
	return findans(t[x].r,m+1,r,k-t[t[x].l].v);
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	int T=read();
	For(kase,1,T) {
		read(n);read(m);
		For(i,1,n) read(in[i]);
		memset(last,0,sizeof(int)*(n+2));
		ans=sz=0;
		for(int i=n;i>=1;--i) {
			update(rt[i],rt[i+1],1,n,i,1);
			if(last[in[i]]) update(rt[i],rt[i],1,n,last[in[i]],-1);
			last[in[i]]=i;
		}
		printf("Case #%d:",kase);
		while(m--) {
			int l=read(),r=read();
			l=(l+ans)%n+1,r=(r+ans)%n+1;
			if(l>r) std::swap(l,r);
			int t=query(rt[l],1,n,l,r);
			t=(t+1)/2;
			//printf("L:%d R:%d t:%d\n",l,r,t);
			ans=findans(rt[l],1,n,t);
			printf(" %d",ans);
		}
		puts("");
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}