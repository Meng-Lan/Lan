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

const int mod=1e9+7;
const int maxn=1e6+10;
char s1[maxn*2],s2[maxn];
int pre[maxn],f[maxn],g[maxn];

void getFail(char *P,int *f) {
	int m=strlen(P);
	f[0]=f[1]=0;
	for(int i=1;i<m;++i) {
		int j=f[i];
		while(j&&P[i]!=P[j]) j=f[j];
		f[i+1]=P[i]==P[j]?j+1:0;
	}
}

void find(char *T,char *P,int *f) {
	int n=strlen(T),m=strlen(P);
	getFail(P,f);
	int j=0;
	for(int i=0;i<n;++i) {
		while(j&&P[j]!=T[i]) j=f[j];
		if(P[j]==T[i]) ++j;
		g[i]=j;
	}
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	int T;scanf("%d",&T);
	while(T--) {
		scanf("%s%s",s1,s2);
		int len1=strlen(s1),len2=strlen(s2);
		std::reverse(s1,s1+len1);
		std::reverse(s2,s2+len2);
		memset(g,0,sizeof(g));
		find(s1,s2,f);
		memset(pre,0,sizeof(pre));
		//FOR(i,0,len1) printf("%d%c",g[i]," \n"[i==len1-1]);
		//For(i,0,len2) printf("%d%c",f[i]," \n"[i==len2]);
		FOR(i,0,len1) {
			if(g[i]+1!=g[i+1]) pre[g[i]]++;
		}
		int fail=f[g[len1-1]];
		while(fail) { pre[fail]++;fail=f[fail]; }
		//printf("fail:%d\n",fail);
		//find(s2,s2,f);
		//FOR(i,0,len2) printf("%d%c",g[i]," \n"[i==len2-1]);
		//For(i,0,len2) printf("%d%c",pre[i]," \n"[i==len2]);
		//FOR(i,0,fail) if(i==fail-1||g[i]+1!=g[i+1]) pre[g[i]]++;
		//For(i,0,len2) printf("%d%c",pre[i]," \n"[i==len2]);
		//For(i,0,g[len1-1]) if(i==len2||f[i]+1!=f[i+1]) pre[f[i]]++;
		//For(i,0,len2) printf("%d%c",pre[i]," \n"[i==len2]);
		for(int i=len2-1;i>0;--i) pre[i]+=pre[i+1];
		//For(i,0,len2) printf("%d%c",pre[i]," \n"[i==len1]);
		ll ans=0;
		For(i,1,len2) ans+=(ll)pre[i]*i%mod;
		printf("%lld\n",ans%mod);
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}