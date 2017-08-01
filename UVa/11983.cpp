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

const int maxn=3e4+10;
struct Lan {
	int x,y1,y2,v;
	Lan(int x,int y1,int y2,int v) :x(x),y1(y1),y2(y2),v(v) {}
	Lan() :Lan(0,0,0,0) {}
	bool operator< (const Lan &rhs)const { return x<rhs.x; }
}node[maxn<<1];
P inv[maxn<<2];
ll sum[maxn<<4][12];
int addv[maxn<<4],y[maxn<<1],n,k;

void build(int rt,int l,int r) {
	sum[rt][0]=y[r+1]-y[l];
	if (l==r) return;
	int m=l+(r-l)/2;
	build(rt<<1,l,m);
	build(rt<<1|1,m+1,r);
}

void pushup(int rt,int l,int r) {
	memset(sum[rt],0,sizeof(sum[rt]));
	if(l==r) sum[rt][std::min(k,addv[rt])]=y[r+1]-y[l];
	else {
		FOR(i,0,12) sum[rt][std::min(i+addv[rt],k)]+=sum[rt<<1][i]+sum[rt<<1|1][i];
	}
}

int L,R,val;
int cnt=0;
void update(int rt,int l,int r) {
	if (L<=l&&R>=r) { addv[rt]+=val; }
	else {
		int m=l+(r-l)/2;
		if(L<=m) update(rt<<1,l,m);
		if(R>m) update(rt<<1|1,m+1,r);
	}
	pushup(rt,l,r);
	//printf("rt:%d l:%d r:%d sum:%lld add:%d\n",rt,l,r,sum[rt][k],addv[rt]);
}

void print(int rt,int l,int r) {
	if (l==r) {
		printf("L:%d R:%d [%d,%d] add:%d\n",l,r,y[l],y[r+1],addv[rt]);
		FOR(i,0,12) printf("sum[%d]=%lld\n",i,sum[rt][i]);
	}
	else {
		int m=l+(r-l)/2;
		print(rt<<1,l,m);
		print(rt<<1|1,m+1,r);
		printf("L:%d R:%d [%d,%d] add:%d\n",l,r,y[l],y[r+1],addv[rt]);
		FOR(i,0,12) printf("sum[%d]=%lld\n",i,sum[rt][i]);
	}
}

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	int T;scanf("%d",&T);
	For(kase,1,T) {
		scanf("%d%d",&n,&k);
		int len=0;
		FOR(i,0,n) {
			int x1,x2,y1,y2;scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
			++x2;++y2;
			y[len]=y1;node[len++]=Lan(x1,y1,y2,1);
			y[len]=y2;node[len++]=Lan(x2,y1,y2,-1);
		}
		std::sort(y,y+len);std::sort(node,node+len);
		int ylen=std::unique(y,y+len)-y;
		//FOR(i,0,ylen) printf("y[%d]=%d\n",i,y[i]);
		//FOR(i,0,len) printf("node[%d] x:%d y1;%d y2:%d v:%d\n",i,node[i].x,node[i].y1,node[i].y2,node[i].v);
		build(1,0,ylen-2);
		//print(1,0,ylen-2);
		ll ans=0;
		FOR(i,0,len) {
			if (i) ans+=(ll)sum[1][k]*(node[i].x-node[i-1].x);
			L=std::lower_bound(y,y+ylen,node[i].y1)-y;
			R=std::lower_bound(y,y+ylen,node[i].y2)-y-1;
			val=node[i].v;
			//printf("L:%d R:%d l:%d r:%d\n",node[i].y1,node[i].y2,y[L],y[R]);
			update(1,0,ylen-2);
		}
		printf("Case %d: %lld\n",kase,ans);
	}


#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}