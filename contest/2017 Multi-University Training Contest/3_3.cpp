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

const int maxn=5e5+10;
int in[maxn],pre[maxn],next[maxn],pos[maxn],n,k;

void del(int x) {
	next[pre[x]]=next[x];
	pre[next[x]]=pre[x];
}

int a[100],b[100];
inline ll solve(int x) {
	int ba=0,bb=0;
	for(int i=x;i;i=pre[i]) {
		a[++ba]=i-pre[i];
		if(ba==k) break;
	}
	for(int i=x;i<=n;i=next[i]) {
		b[++bb]=next[i]-i;
		if(bb==k) break;
	}
	ll t=0;
	For(i,1,ba) if(k-i+1<=bb) t+=(ll)a[i]*b[k-i+1];
	return t;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	int T;scanf("%d",&T);
	while(T--) {
		scanf("%d%d",&n,&k);
		For(i,1,n) scanf("%d",in+i),pos[in[i]]=i;
		For(i,1,n) pre[i]=i-1,next[i]=i+1;
		pre[0]=0;next[n+1]=n+1;
		ll ans=0;
		For(i,1,n) {
			int x=pos[i];
			ans+=solve(x)*i;
			del(x);
		}
		printf("%lld\n",ans);
	}


#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}