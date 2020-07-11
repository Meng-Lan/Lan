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
const int maxm=maxn*50;
int a1[maxn],a2[maxn],in[maxn],pos[maxn],t[maxn];
int ls[maxm],rs[maxm],sum[maxm],sz,root[maxn];
int L[30],R[30],n,m;

inline int lowbit(int x) { return x&(-x); }

inline int getans(int x) {
	int res=0;
	for(int i=x;i;i-=lowbit(i)) res+=t[i];
	return res;
}

void update(int &rt,int l,int r,int x) {
	if(!rt) rt=++sz;
	sum[rt]++;
	if(l==r) return;
	int m=l+(r-l)/2;
	//printf("l:%d r:%d m:%d\n",l,r,m);
	if(x<=m) update(ls[rt],l,m,x);
	else update(rs[rt],m+1,r,x);
}

int findless(int l,int r,int num) {
	L[0]=R[0]=0;--l;int res=0;
	for(int i=l;i;i-=lowbit(i)) L[++L[0]]=root[i];
	for(int i=r;i;i-=lowbit(i)) R[++R[0]]=root[i];
	l=1,r=n;
	while(l<r) {
		int m=l+(r-l)/2;
		//printf("l:%d r:%d m:%d\n",l,r,m);
		if(num>m) {
			For(i,1,L[0]) res-=sum[ls[L[i]]];
			For(i,1,R[0]) res+=sum[ls[R[i]]];
			For(i,1,L[0]) L[i]=rs[L[i]];
			For(i,1,R[0]) R[i]=rs[R[i]];
			l=m+1;
		}
		else {
			For(i,1,L[0]) L[i]=ls[L[i]];
			For(i,1,R[0]) R[i]=ls[R[i]];
			r=m;
		}
	}
	return res;
}

int findmore(int l,int r,int num) {
	L[0]=R[0]=0;--l;int res=0;
	for(int i=l;i;i-=lowbit(i)) L[++L[0]]=root[i];
	for(int i=r;i;i-=lowbit(i)) R[++R[0]]=root[i];
	//printf("l:%d r:%d num:%d\nR[0]:%d",l,r,num,R[0]);
	//For(i,1,R[0]) printf(" R[%d]:%d",i,R[i]);puts("");
	l=1,r=n;
	while(l<r) {
		int m=l+(r-l)/2;
		//printf("findmore|l:%d r:%d m:%d\n",l,r,m);
		if(num<=m) {
			For(i,1,L[0]) res-=sum[rs[L[i]]];
			For(i,1,R[0]) res+=sum[rs[R[i]]];
			For(i,1,L[0]) L[i]=ls[L[i]];
			For(i,1,R[0]) R[i]=ls[R[i]];
			r=m;
		}
		else {
			For(i,1,L[0]) L[i]=rs[L[i]];
			For(i,1,R[0]) R[i]=rs[R[i]];
			l=m+1;
		}
	}
	return res;
}

void print(int idx,int l,int r,int x) {
	printf("l:%d r:%d sum:%d\n",l,r,sum[idx]);
	if(l==r) return;
	int m=l+(r-l)/2;
	if(x<=m) print(ls[idx],l,m,x);
	else print(rs[idx],m+1,r,x);
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	ll ans=0;
	scanf("%d%d",&n,&m);
	For(i,1,n) {
		scanf("%d",in+i);
		pos[in[i]]=i;
		a1[i]=getans(n)-getans(in[i]);
		ans+=a1[i];
		for(int j=in[i];j<=n;j+=lowbit(j)) ++t[j];
	}
	//For(i,1,n) printf("%d%c",a1[i]," \n"[i==n]);
	memset(t,0,sizeof(t));
	for(int i=n;i;--i) {
		a2[i]=getans(in[i]-1);
		for(int j=in[i];j<=n;j+=lowbit(j)) ++t[j];
	}
	//For(i,1,n) printf("%d%c",a2[i]," \n"[i==n]);
	For(i,1,m) {
		printf("%lld\n",ans);
		int x;scanf("%d",&x);x=pos[x];
		ans-=a1[x]+a2[x]-findless(x+1,n,in[x])-findmore(1,x-1,in[x]);
		//printf("findless:%d\nfindmore:%d\n",findless(x+1,n,in[x]),findmore(1,x-1,in[x]));
		//printf("sum5:%d\n",sum[root[2]]);
		//print(root[2],1,n,5);
		for(int j=x;j<=n;j+=lowbit(j)) update(root[j],1,n,in[x]);
	}


#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}