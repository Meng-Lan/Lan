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

const int maxn=60000+10;
int in[maxn],pre[maxn],pos[maxn],n;
double add[maxn<<2],sum[maxn<<2];

void pushdown(int rt) {
	if(add[rt]) {
		int ls=rt<<1,rs=rt<<1|1;
		add[ls]+=add[rt];
		add[rs]+=add[rt];
		sum[ls]+=add[rt];
		sum[rs]+=add[rt];
		add[rt]=0;
		sum[rt]=std::min(sum[ls],sum[rs]);
	}
}

void update(int rt,int l,int r,int x,int y,double v) {
	if(x>y) return;
	//printf("rt:%d l:%d r:%d x:%d y:%d v:%f\n",rt,l,r,x,y,v);
	if(x<=l&&y>=r) { add[rt]+=v;sum[rt]+=v; return;}
	pushdown(rt);
	int m=l+(r-l)/2;
	if(x<=m) update(rt<<1,l,m,x,y,v);
	if(y>m) update(rt<<1|1,m+1,r,x,y,v);
	sum[rt]=std::min(sum[rt<<1],sum[rt<<1|1]);
}

double query(int rt,int l,int r,int x,int y) {
	if(x<=l&&r<=y) return sum[rt];
	pushdown(rt);
	int m=l+(r-l)/2;
	double min=1;
	if(x<=m) min=std::min(min,query(rt<<1,l,m,x,y));
	if(y>m) min=std::min(min,query(rt<<1|1,m+1,r,x,y));
	return min;
}

bool check(double x) {
	memset(add,0,sizeof(add));memset(sum,0,sizeof(sum));
	double ans=1;
	For(i,1,n) {
		update(1,1,n,1,i,-x);
		update(1,1,n,1,pre[i],-1);
		update(1,1,n,1,i,1);
		ans=std::min(ans,query(1,1,n,1,i));
	}
	return ans<=0;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	int T;scanf("%d",&T);
	while(T--) {
		memset(pos,0,sizeof(pos));
		scanf("%d",&n);
		For(i,1,n) { scanf("%d",in+i);pre[i]=pos[in[i]];pos[in[i]]=i; }
		double l=0,r=1;
		For(i,0,15) {
			double m=l+(r-l)/2;
			if(check(m)) r=m;
			else l=m;
		}
		printf("%.6f\n",r);
	}


#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}