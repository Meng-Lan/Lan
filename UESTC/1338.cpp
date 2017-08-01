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

const int maxn=1e6+10;
struct Lan {
	int v,x,y,idx;
	Lan(int v,int x,int y,int idx) :v(v),x(x),y(y),idx(idx) {}
	Lan() :Lan(0,0,0,0) {}
	bool operator<(const Lan &rhs)const { return v<rhs.v; }
}in[maxn];
int x[maxn],y[maxn],mx[maxn],my[maxn],fa[maxn],ans[maxn],n,m;

int find(int x) { return fa[x]=x==fa[x]?x:find(fa[x]); }

void Union(int x,int y) { fa[find(x)]=find(y); }

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	scanf("%d%d",&n,&m);
	FOR(i,0,n*m) {
		scanf("%d",&in[i].v);
		in[i].x=i/m;in[i].y=i%m;in[i].idx=i;
	}
	std::sort(in,in+n*m);
	FOR(i,0,n*m) fa[i]=i;
	int j=-1;
	FOR(i,0,n*m) {
		if (i!=n*m-1&&in[i].v==in[i+1].v) continue;
		For(k,j+1,i) { x[in[k].x]=in[k].idx;y[in[k].y]=in[k].idx; }
		For(k,j+1,i) { Union(x[in[k].x],in[k].idx);Union(y[in[k].y],in[k].idx); }
		For(k,j+1,i) { int t=find(in[k].idx);ans[t]=std::max(ans[t],std::max(mx[in[k].x],my[in[k].y])+1); }
		For(k,j+1,i) { mx[in[k].x]=std::max(mx[in[k].x],ans[find(in[k].idx)]);my[in[k].y]=std::max(my[in[k].y],ans[find(in[k].idx)]); }
		j=i;
	}
	FOR(i,0,n*m) {
		printf("%d ",ans[find(i)]);
		if(i%m==m-1) putchar('\n');
	}


#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}