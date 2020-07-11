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
/*namespace IO {
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
inline int read() { static int x;read(x);return x; }*/
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

const int maxn=1e5+10;
struct Lan {
	int a,b,c,cnt,ans;
	bool operator==(const Lan &rhs)const { return a==rhs.a&&b==rhs.b&&c==rhs.c; }
}in[maxn];
int n,k,ans[maxn<<1];

int C[maxn<<1];

inline int lowbit(int x) { return x&-x; }

void add(int x,int y) {
	while(x<=k) { C[x]+=y;x+=lowbit(x); }
}

int query(int x) {
	int res=0;
	while(x>0) { res+=C[x];x-=lowbit(x); }
	return res;
}

void cdq(int l,int r) {
	if(l==r) return;
	int m=l+(r-l)/2;
	cdq(l,m);
	cdq(m+1,r);
	std::sort(in+l,in+m+1,[](const Lan &l,const Lan &r) {return l.b<r.b;});
	std::sort(in+m+1,in+r+1,[](const Lan &l,const Lan &r) {return l.b<r.b;});
	int l1=l;
	For(i,m+1,r) {
		while(l1<=m&&in[l1].b<=in[i].b) { add(in[l1].c,in[l1].cnt);l1++; }
		in[i].ans+=query(in[i].c);
	}
	FOR(i,l,l1) add(in[i].c,-in[i].cnt);
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	scanf("%d%d",&n,&k);
	For(i,1,n) scanf("%d%d%d",&in[i].a,&in[i].b,&in[i].c),in[i].cnt=1;
	std::sort(in+1,in+1+n,[](const Lan &l,const Lan &r) {return l.a<r.a||l.a==r.a&&l.b<r.b||l.a==r.a&&l.b==r.b&&l.c<r.c;});
	int r=1;
	//For(i,1,n) printf("sort a:%d b:%d c:%d cnt:%d\n",in[i].a,in[i].b,in[i].c,in[i].cnt);
	For(i,2,n) if(in[i]==in[r]) in[r].cnt++;else in[++r]=in[i];
	//For(i,1,r) printf("unique a:%d b:%d c:%d cnt:%d\n",in[i].a,in[i].b,in[i].c,in[i].cnt);
	cdq(1,r);
	For(i,1,r) ans[in[i].cnt+in[i].ans-1]+=in[i].cnt;
	FOR(i,0,n) printf("%d\n",ans[i]);

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}