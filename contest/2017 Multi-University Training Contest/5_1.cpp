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
#include<bitset>
#include<cstdlib>
#define _CRT_RAND_S 
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

namespace IO {
	inline char getchar() {
		static const int BUFSIZE=10000001;
		static char buf[BUFSIZE],*begin,*end;
		if(begin==end) {
			begin=buf;
			end=buf+fread(buf,1,BUFSIZE,stdin);
			if(begin==end) return -1;
		}
		return *begin++;
	}

	bool read(int &in) {
		int c;
		while(!isalnum(c=getchar())&&c!=-1);
		if(c==-1) return false;
		in=c-'0';
		while(isalnum(c=getchar())) { in*=10;in+=c-'0'; }
		return true;
	}
}

const int maxn=50000+10;
std::bitset<maxn> ans,a;
int b[maxn],pos[maxn];
int n,m,q,x,mx;

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	int T;//scanf("%d",&T);
	IO::read(T);
	while(T--) {
		//scanf("%d%d%d",&n,&m,&q);
		IO::read(n);IO::read(m);IO::read(q);
		a.reset();ans.reset();
		mx=0;
		FOR(i,0,n) { IO::read(x);a[x]=1;mx=std::max(mx,x); }
		FOR(i,0,m) { IO::read(b[i]); }
		FOR(i,0,m) {
			x=b[i];
			while(x<=mx) { ans[x]=ans[x]^1;x+=b[i]; }
			For(i,0,mx) printf("%d",(int)ans[i]);puts("");
		}
		/*std::sort(b,b+m);
		FOR(i,0,m) {
			int j=std::lower_bound(b,b+m,i+1)-b;
			//printf("i:%d j:%d b[j]:%d\n",i,j,b[j]);
			for(;j<m;++j) {
				x=i;
				int &add=b[j];
				while(x<=mx) { ans[i]=ans[i]^a[x];x+=add; }
			}
		}*/
		while(q--) {
			IO::read(x);
			int res=(a&(ans<<(x-1))).count();
			printf("%d\n",res&1);
		}
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}