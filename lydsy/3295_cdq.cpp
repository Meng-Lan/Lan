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
	int x,id,pos;
	bool operator<(const Lan &rhs)const { return pos<rhs.pos; }
}q[maxn],nq[maxn];
int in[maxn],pos[maxn],n,m,cnt[maxn],f[maxn],vis[maxn],kase;
ll ans;

int c[maxn];
inline int lowbit(int x) { return x&-x; }

void add(int x,int flag) {
	for(;x&&x<=n;x+=lowbit(x)*flag) {
		if(vis[x]!=kase) { c[x]=0;vis[x]=kase; }
		c[x]++;
	}
}

int query(int x,int flag) {
	int res=0;
	for(;x&&x<=n;x+=lowbit(x)*flag) {
		if(vis[x]==kase) res+=c[x];
	}
	return res;
}

void cdq(int l,int r) {
	if(l==r) {
		printf("%lld\n",ans);
		ans-=cnt[q[l].pos];
		ans+=f[l];
		return;
	}
	int m=l+(r-l)/2,l1=l,l2=m+1;
	For(i,l,r) {
		if(q[i].id<=m) nq[l1++]=q[i];
		else nq[l2++]=q[i];
	}
	For(i,l,r) q[i]=nq[i];
	cdq(l,m);
	++kase;
	int j=l;
	For(i,m+1,r) {
		for(;j<=m&&q[j].pos<q[i].pos;++j) add(q[j].x,-1);
		f[q[i].id]+=query(q[i].x,1);
	}
	++kase;j=m;
	for(int i=r;i>m;--i) {
		for(;j>=l&&q[j].pos>q[i].pos;--j) add(q[j].x,1);
		f[q[i].id]+=query(q[i].x,-1);
	}
	cdq(m+1,r);
	l1=l,l2=m+1;
	For(i,l,r) {
		if((q[l1]<q[l2]||l2>r)&&l1<=m) nq[i]=q[l1++];
		else nq[i]=q[l2++];
	}
	For(i,l,r) q[i]=nq[i];
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	scanf("%d%d",&n,&m);
	For(i,1,n) {
		scanf("%d",in+i);pos[in[i]]=i;
		cnt[i]=query(in[i],1);
		add(in[i],-1);
		ans+=cnt[i];
	}
	kase++;
	for(int i=n;i;--i) {
		cnt[i]+=query(in[i],-1);
		add(in[i],1);
	}
	For(i,1,m) {
		scanf("%d",&q[i].x);
		q[i].id=i;
		q[i].pos=pos[q[i].x];
	}
	std::sort(q+1,q+1+m);
	cdq(1,m);

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}
