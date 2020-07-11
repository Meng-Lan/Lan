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
while(isalnum(c=IO::getchar())) { in*=10;in+=c-'0'; }
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

const int maxn=505;
int w[maxn][maxn],n;
int Lx[maxn],Ly[maxn];
int left[maxn];
bool s[maxn],t[maxn];

bool match(int i) {
	s[i]=true;
	For(j,1,n) if(Lx[i]+Ly[j]==w[i][j]&&!t[j]) {
		t[j]=true;
		if(!left[j]||match(left[j])) {
			left[j]=i;
			return true;
		}
	}
	return false;
}

void update() {
	int a=1<<30;
	For(i,1,n) if(s[i]) For(j,1,n) if(!t[j]) a=std::min(a,Lx[i]+Ly[j]-w[i][j]);
	For(i,1,n) {
		if(s[i]) Lx[i]-=a;
		if(t[i]) Ly[i]+=a;
	}
}

void KM() {
	For(i,1,n) {
		left[i]=Lx[i]=Ly[i]=0;
		For(j,1,n) Lx[i]=std::max(Lx[i],w[i][j]);
	}
	For(i,1,n) {
		for(;;) {
			For(j,1,n) s[j]=t[j]=0;
			if(match(i)) break;else update();
		}
	}
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	while(scanf("%d",&n)==1) {
		For(i,1,n) For(j,1,n) scanf("%d",w[i]+j);
		KM();
		For(i,1,n) printf("%d%c",Lx[i]," \n"[i==n]);
		For(i,1,n) printf("%d%c",Ly[i]," \n"[i==n]);
		int ans=0;
		For(i,1,n) ans+=Lx[i]+Ly[i];
		printf("%d\n",ans);
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}