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

const int maxn=11;
int mstv[maxn],msta[maxn],ppv[maxn],ppa[maxn],n;
struct Lan {
	int i,v,a;
	Lan(int i,int v,int a) :i(i),v(v),a(a) {}
	Lan() :Lan(0,0,0) {}
	bool operator<(const Lan &rhs)const { return i>rhs.i||i==rhs.i&&v<rhs.v; }
}d[1<<maxn];
std::vector<int> G[maxn];

Lan fight(int v,int a,Lan b) {
	//printf("v:%d a:%d b.i:%d b.v:%d b.a:%d\n",v,a,b.i,b.v,b.a);
	while (v>0) {
		v-=b.a;b.v-=a;
		if (b.v<=0) {
			b.i++;
			if (b.i>=n) return Lan(n,v,a);
			b.v=mstv[b.i];b.a=msta[b.i];
		}
	}
	//printf("v:%d a:%d b.i:%d b.v:%d b.a:%d\n",v,a,b.i,b.v,b.a);
	return b;
}

bool solve() {
	for(auto &t:G) t.clear();
	FOR(i,0,1<<n) {
		int t=i,cnt=0;
		while (t) { cnt+=t&1;t>>=1; }
		G[cnt].push_back(i);
	}
	FOR(i,0,1<<n) d[i]=Lan(0,mstv[0],msta[0]);
	//FOR(i,0,n) { printf("#%d\n",i);for (auto &t:G[i]) printf("%d ",t);puts(""); }
	FOR(i,0,n) for (auto &t:G[i]) {
		FOR(j,0,n) if (!(t&(1<<j))) {
			int s=t|(1<<j);
			d[t|(1<<j)]=std::min(d[t|(1<<j)],fight(ppv[j],ppa[j],d[t]));
			if (d[s].i>=n&&(i!=n-1||d[s].v>0)) {
				//printf("t:%d j:%d s:%d\n",t,j,s);
				//printf("#i:%d v:%d a:%d\n",d[s].i,d[s].v,d[s].a);
				return true;
			}
		}
	}
	int s=(1<<n)-1;
	//printf("i:%d v:%d a:%d\n",d[s].i,d[s].v,d[s].a);
	return false;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	/*FOR(i,0,maxn) {
		printf("#%d\n",i);
		for (auto &t:G[i]) printf("%d ",t);
		puts("");
	}*/
	int T;scanf("%d",&T);
	while (T--) {
		scanf("%d",&n);
		FOR(i,0,n) scanf("%d%d",mstv+i,msta+i);
		FOR(i,0,n) scanf("%d%d",ppv+i,ppa+i);
		int S=(1<<n)-1;
		//printf("i:%d v:%d a:%d\n",d[S].i,d[S].v,d[S].a);
		if (solve()) puts("YES");
		else puts("NO");
	}


#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}