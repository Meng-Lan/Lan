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

void getTLE() {
	std::vector<int> v;FOR(i,0,v.size()+1) v.push_back(i);
}

const int maxn=1e5+10;
struct Event {
	int x1,x2,y1,y2,z1,z2;
	void input() { scanf("%d%d%d%d%d%d",&x1,&y1,&z1,&x2,&y2,&z2); }
}evt[maxn];

struct Lan {
	int x,y1,y2,v;
	Lan(int x,int y1,int y2,int v) :x(x),y1(y1),y2(y2),v(v) {}
	Lan() :Lan(0,0,0,0) {}
	bool operator<(const Lan &rhs)const { return x<rhs.x; }
}node[maxn<<1];

int sum[maxn<<3][12],addv[maxn<<3],y[maxn<<1],n,k;
int cnt=0;
void build(int rt,int l,int r) {
	//printf("rt:%d l:%d r:%d\n",rt,l,r);
	sum[rt][0]=y[r+1]-y[l];addv[rt]=0;++cnt;
	if (l==r) return;
	int m=l+(r-l)/2;
	build(rt<<1,l,m);
	build(rt<<1|1,m+1,r);
}

void pushup(int rt,int l,int r) {
	if(rt>(maxn<<3)) getTLE();
	memset(sum[rt],0,sizeof(sum[rt]));
	if (l==r) sum[rt][std::min(11,addv[rt])]=y[r+1]-y[l];
	else FOR(i,0,12) sum[rt][std::min(11,i+addv[rt])]+=sum[rt<<1][i]+sum[rt<<1|1][i];
}

int L,R,v;
void update(int rt,int l,int r) {
	//printf("rt:%d l:%d r:%d sum:%d add:%d\n",rt,l,r,sum[rt][k],addv[rt]);
	if (rt>(maxn<<3)) getTLE();
	if (L<=l&&r<=R) addv[rt]+=v;
	else {
		int m=l+(r-l)/2;
		if (L<=m) update(rt<<1,l,m);
		if (R>m) update(rt<<1|1,m+1,r);
	}
	pushup(rt,l,r);
}

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	scanf("%d%d",&n,&k);FOR(i,0,n) evt[i].input();
	//if(n>=maxn) getTLE();
	//n=100000;k=10;
	//FOR(i,0,n) { evt[i].x1=evt[i].y1=evt[i].z1=1;evt[i].x2=evt[i].y2=i<<1|1;evt[i].z2=(i&1)^2; }
	ll ans=0;
	For(i,1,2) {
		int len=0;
		FOR(j,0,n) if (evt[j].z1<=i&&evt[j].z2>=i+1) {
			//printf("x1:%d y1:%d z1:%d x2:%d y2:%d z2:%d\n",evt[j].x1,evt[j].y1,evt[j].z1,evt[j].x2,evt[j].y2,evt[j].z2);
			node[len]=Lan(evt[j].x1,evt[j].y1,evt[j].y2,1);y[len++]=evt[j].y1;
			node[len]=Lan(evt[j].x2,evt[j].y1,evt[j].y2,-1);y[len++]=evt[j]. y2;
		}
		std::sort(y,y+len);std::sort(node,node+len);
		int ylen=std::unique(y,y+len)-y;
		//printf("#1 len:%d ylen:%d\n",len,ylen);
		//FOR(j,0,n) printf("#2 x:%d y1:%d y2:%d v:%d\n",node[j].x,node[j].y1,node[j].y2,node[j].v);
		//FOR(j,0,ylen) printf("#3 y[%d]=%d\n",j,y[j]);
		if(ylen-2<0) continue;
		build(1,0,ylen-2);
		FOR(j,0,len) {
			//printf("node[%d] x:%d y1:%d y2:%d v:%d\n",j,node[j].x,node[j].y1,node[j].y2,node[j].v);
			if(node[j].y1==node[j].y2) continue;
			if (j) ans+=(ll)sum[1][k]*(node[j].x-node[j-1].x);
			L=std::lower_bound(y,y+ylen,node[j].y1)-y;
			R=std::lower_bound(y,y+ylen,node[j].y2)-y-1;
			v=node[j].v;
			update(1,0,ylen-2);
		}
	}
	printf("%lld\n",ans);

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}