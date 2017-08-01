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
	if (n-r < r) r=n-r;
	ll ansn=1,ansr=1;
	for (ll i=n-r+1; i<=n; ++i) ansn*=i;
	for (ll j=1; j<=r; ++j) ansr*=j;
	return ansn/ansr;
}
ll gcd(ll a,ll b) { return b?gcd(b,a%b):a; }
ll lcm(ll a,ll b) { return a/gcd(a,b)*b; }
std::vector<int> Eratosthenes(const int len,int *vis) {
	memset(vis,0,sizeof(int)*len);
	std::vector<int> prime;
	int m=(int)sqrt(len+0.5);
	For(i,2,m) if (!vis[i]) for (int j=i*i; j < len; j+=i) vis[j]=1;
	FOR(i,2,len) if (!vis[i]) prime.push_back(i);
	return prime;
}
void phi_table(int n,int *phi) {
	For(i,2,n) phi[i]=0;
	phi[1]=1;
	For(i,2,n) if (!phi[i])
		for (int j=i; j<=n; j+=i) {
			if (!phi[j]) phi[j]=j;
			phi[j]=phi[j]/i*(i-1);
		}
}

const int maxn=2e5+10;
struct Lan {
	int k,b;
	ll yu,yv;
	void input() { scanf("%d%d",&k,&b); }
	bool operator<(const Lan &rhs)const { return yu<rhs.yu||yu==rhs.yu&&yv>rhs.yv; }
}in[maxn];
int n,u,v,c[maxn],m;
ll t[maxn];

inline int lowbit(int x) { return x&-x; }

void add(int x) {
	while (x<=m) {
		c[x]+=1;x+=lowbit(x);
	}
}

int sum(int x) {
	int res=0;
	while (x>0) {
		res+=c[x];x-=lowbit(x);
	}
	return res;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	scanf("%d%d%d",&n,&u,&v);
	FOR(i,0,n) {
		in[i].input();
		in[i].yu=(ll)in[i].k*u+in[i].b;
		in[i].yv=t[i+1]=(ll)in[i].k*v+in[i].b;
	}
	std::sort(in,in+n);
	std::sort(t+1,t+n+1);m=std::unique(t+1,t+n+1)-t-1;
	//FOR(i,0,m) printf("t[%d]=%lld\n",i,t[i]);
	ll ans=0;
	FOR(i,0,n) {
		int tmp=std::lower_bound(t+1,t+m+1,in[i].yv)-t;
		//printf("yv:%lld tmp:%d\n",in[i].yv,tmp);
		ans+=i-sum(tmp-1);
		add(tmp);
	}
	cout<<ans<<endl;

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}