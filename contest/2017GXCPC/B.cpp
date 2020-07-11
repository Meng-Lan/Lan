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

const int INF=1e6+1;
const int maxn=150000;
struct Lan { int l,r,v; }t[maxn*50];
int  root[55],sz;

void update(int &rt,int l,int r,int y,int x) {
	if(!rt) { rt=++sz;t[rt].l=t[rt].r=0;t[rt].v=INF; }
	if(x<=t[rt].v) t[rt].v=x;
	if(l==r) return;
	int m=l+(r-l)/2;
	if(y<=m) update(t[rt].l,l,m,y,x);
	else update(t[rt].r,m+1,r,y,x);
}

bool query(int rt,int l,int r,int L,int R,int x) {
	if(L<=l&&r<=R) return t[rt].v<=x;
	if(t[rt].v>x) return false;
	int m=l+(r-l)/2;
	bool min=false;
	if(L<=m)min=min||query(t[rt].l,l,m,L,R,x);
	if(R>m) min=min||query(t[rt].r,m+1,r,L,R,x);
	return min;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	int op;
	t[0].v=INF;
	for(;;){
		read(op);
		if(op==0||op==3) {
			memset(root,0,sizeof(root));
			sz=0;t[0].l=t[0].r=0;t[0].v=INF;
			if(op==3) break;
		}
		if(op==1) { int x=read(),y=read(),c=read();update(root[c],1,INF,y,x); }
		if(op==2) {
			int ans=0,x=read(),y=read(),z=read();
			For(c,0,50) if(query(root[c],1,INF,y,z,x)) ++ans;
			printf("%d\n",ans);
		}
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}