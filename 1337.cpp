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

const int INF=2e9;
const int maxn=2e3+10;
struct Lan{
	int x,y;
	ll k,b;
	bool operator<(const Lan &rhs)const {
		if (x!=rhs.x) return x<rhs.x;
		if (y!=rhs.y) return y<rhs.y;
		if (k!=rhs.k) return k<rhs.k;
		return b<rhs.b;
	}
	Lan() :x(0),y(0),k(0),b(0) {}
}edges[maxn*maxn],in[maxn];
int n;

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	scanf("%d",&n);
	FOR(i,0,n) scanf("%d%d",&in[i].x,&in[i].y);
	std::sort(in,in+n);
	int i,j;
	for(i=0,j=1;j<n;++j) if(in[i].x!=in[j].x||in[i].y!=in[j].y) in[++i]=in[j];
	int m=0;n=i+1;
	FOR(i,0,n) FOR(j,0,n) if (i!=j) {
		auto &e=edges[m];
		e.x=in[i].x-in[j].x;e.y=in[i].y-in[j].y;
		if (e.x==0) { e.k=INF;e.b=in[i].x; }
		else if ((ll)in[i].y*e.x-in[i].x*e.y==0) e.k=e.b=0;
		else {
			ll t=gcd(e.x,(ll)in[i].y*e.x-in[i].x*e.y);
			e.k=e.x/t;e.b=((ll)in[i].y*e.x-in[i].x*e.y)/t;
		}
		m++;
	}
	std::sort(edges,edges+m);
	ll ans=0;
	for (i=0,j=1;j<=m;++j) if (j==m||edges[i].x!=edges[j].x||edges[i].y!=edges[j].y) {
		for (int l=i,r=l+1;r<=j;++r) if (r==j||edges[l].k!=edges[r].k||edges[l].b!=edges[r].b) {
			ans+=(ll)(r-l)*(l-i);l=r;
		}
		i=j;
	}
	cout<<(ans/4)<<endl;


#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}