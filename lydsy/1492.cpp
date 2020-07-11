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
const double eps=1e-9;
struct Lan {
	double a,b,rate,x,y,slope;
	int id;
	bool operator<(const Lan &rhs)const { return slope>rhs.slope; }
}p[maxn],tp[maxn];
int top,s[maxn],n;
double f[maxn];

inline double slope(int a,int b) {
	if(!b) return -1e20;
	if(fabs(p[a].x-p[b].x)<eps) return 1e20;
	return (p[b].y-p[a].y)/(p[b].x-p[a].x);
}

void solve(int l,int r) {
	if(l==r) {
		f[l]=std::max(f[l],f[l-1]);
		p[l].y=f[l]/(p[l].a*p[l].rate+p[l].b);
		p[l].x=p[l].y*p[l].rate;
		return;
	}
	int mid=l+(r-l)/2;
	int l1=l,l2=mid+1;
	For(i,l,r) if(p[i].id<=mid) tp[l1++]=p[i];else tp[l2++]=p[i];
	For(i,l,r) p[i]=tp[i];
	solve(l,mid);
	top=0;
	For(i,l,mid) {
		while(top>1&&slope(s[top-1],s[top])<slope(s[top-1],i)+eps) --top;
		s[++top]=i;
	}
	s[++top]=0;
	int j=1;
	For(i,mid+1,r) {
		while(j<top&&slope(s[j],s[j+1])+eps>p[i].slope) ++j;
		f[p[i].id]=std::max(f[p[i].id],p[s[j]].x*p[i].a+p[s[j]].y*p[i].b);
	}
	solve(mid+1,r);
	l1=l,l2=mid+1;
	For(i,l,r) {
		if(((p[l1].x<p[l2].x||fabs(p[l1].x-p[l2].x)<eps&&p[l1].y<p[l2].y)||l2>r)&&l1<=mid) tp[i]=p[l1++];
		else tp[i]=p[l2++];
	}
	For(i,l,r) p[i]=tp[i];
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	scanf("%d%lf",&n,&f[0]);
	For(i,1,n) {
		scanf("%lf%lf%lf",&p[i].a,&p[i].b,&p[i].rate);
		p[i].slope=-p[i].a/p[i].b;p[i].id=i;
	}
	std::sort(p+1,p+1+n);
	solve(1,n);
	printf("%.3f\n",f[n]);

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}