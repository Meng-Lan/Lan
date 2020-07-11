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
typedef long long LL;
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
	while(isalnum(c=IO::getchar())) { in*=10;in+=c-'0'; }
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

int dight[100],tmp[100];
long long dp[40][40][40][40];
long long dfs(int k,int start,int pos,int s,bool limit) {
	if(pos<0)
		return s;
	if(!limit&&dp[k][pos][s][start]!=-1)
		return dp[k][pos][s][start];
	int end;
	long long ret=0;
	if(limit)
		end=dight[pos];
	else
		end=k-1;
	for(int d=0; d<=end; ++d) {
		tmp[pos]=d;
		if(start==pos&&d==0)
			ret+=dfs(k,start-1,pos-1,s,limit&&d==end);
		else if(s&&pos<(start+1)/2)
			ret+=dfs(k,start,pos-1,tmp[start-pos]==d,limit&&d==end);
		else
			ret+=dfs(k,start,pos-1,s,limit&&d==end);
	}
	if(!limit)
		dp[k][pos][s][start]=ret;
	return ret;
}
long long f(long long a,int base) {
	memset(dight,0,sizeof(dight));
	int cnt=0;
	while(a!=0) {
		dight[cnt++]=a%base;
		a/=base;
	}
	return dfs(base,cnt-1,cnt-1,1,1);
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	memset(dp,-1,sizeof(dp));
	int T;read(T);
	For(kase,1,T) {
		int L,R,l,r;
		read(L);read(R);read(l);read(r);
		if(L>R) std::swap(L,R);
		if(l>r) std::swap(l,r);
		ll ans=0;
		For(i,l,r) {
			ll t=f(R,i)-f(L-1,i);
			ans+=t*i;
			ans+=(R-L+1)-t;
		}
		printf("Case #%d: %lld\n",kase,ans);
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}