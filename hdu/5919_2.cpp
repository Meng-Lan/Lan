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
int n,m,in[maxn],belong[maxn],pre[maxn],t[maxn],block,sz;
int L[maxn],R[maxn],cnt[maxn];

void build() {
	block=sqrt(n*log(n));
	sz=n/block;if(n%block) ++sz;
	For(i,1,sz) { L[i]=(i-1)*block+1;R[i]=i*block; }
	R[sz]=n;
	For(i,1,n) belong[i]=(i-1)/block+1;
	For(i,1,n) t[i]=pre[i];
	For(i,1,sz) {
		int l=L[i],r=R[i]+1;
		std::sort(t+l,t+r);
	}
	/*For(i,1,n) printf("b[%d]=%d ",i,belong[i]);puts("");
	For(i,1,n) printf("pre[%d]=%d ",i,pre[i]);puts("");
	For(i,1,n) printf("t[%d]=%d ",i,t[i]);puts("");
	For(i,1,sz) printf("#%d L:%d R:%d\n",i,L[i],R[i]);*/
}

int query(int l,int r) {
	int res=0;
	for(int i=l,len=std::min(R[belong[l]],r);i<=len;++i) if(pre[i]<l) ++res;
	if(belong[l]!=belong[r]) {
		For(i,L[belong[r]],r) if(pre[i]<l) ++res;
	}
	FOR(i,belong[l]+1,belong[r]) {
		cnt[i]=std::lower_bound(t+L[i],t+R[i]+1,l)-(t+L[i]);
		res+=cnt[i];
	}
	int ans=(res+1)/2;
	res=0;
	for(int i=l,len=std::min(R[belong[l]],r);i<=len;++i) {
		if(pre[i]<l) ++res;
		if(res==ans) return i;
	}
	FOR(i,belong[l]+1,belong[r]) {
		if(res+cnt[i]>=ans) {
			For(j,L[i],R[i]) {
				if(pre[j]<l) ++res;
				if(res==ans) return j;
			}
		}
		res+=cnt[i];
	}
	if(belong[l]!=belong[r]) {
		For(i,L[belong[r]],r) {
			if(pre[i]<l) ++res;
			if(res==ans) return i;
		}
	}
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
		memset(t,0,sizeof(int)*(n+2));
		For(i,1,n) read(in[i]);
		For(i,1,n) { pre[i]=t[in[i]];t[in[i]]=i; }
		build();
		//printf("block:%d sz:%d\n",block,sz);
		int ans=0;
		printf("Case #%d:",kase);
		while(m--) {
			int l=read(),r=read();
			l=(l+ans)%n+1,r=(r+ans)%n+1;
			if(l>r) std::swap(l,r);
			//printf("L:%d R:%d\n",l,r);
			ans=query(l,r);
			printf(" %d",ans);
		}
		puts("");
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}