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

const int maxn=1e4+10;
struct Lan {
	int sum,pre,suf,ans;
	Lan(int sum,int pre,int suf,int ans) :sum(sum),pre(pre),suf(suf),ans(ans) {}
	Lan(int all) :Lan(all,all,all,all) {}
	Lan() :Lan(0) {}
	friend Lan operator+(const Lan &l,const Lan &r) {
		Lan res;
		res.pre=std::max(l.pre,l.sum+r.pre);
		res.suf=std::max(r.suf,r.sum+l.suf);
		res.sum=l.sum+r.sum;
		res.ans=std::max(l.suf+r.pre,std::max(l.ans,r.ans));
		return res;
	}
}tree[maxn<<2];
int in[maxn],n,q;

void build(int rt,int l,int r) {
	if(l==r) { tree[rt]=Lan(in[l]);return; }
	int m=l+(r-l)/2;
	build(rt<<1,l,m);
	build(rt<<1|1,m+1,r);
	tree[rt]=tree[rt<<1]+tree[rt<<1|1];
}

Lan query(int rt,int l,int r,int x,int y) {
	if(x>y) return Lan(0);
	if(x<=l&&r<=y) return tree[rt];
	int m=l+(r-l)/2;
	Lan ls,rs;
	if(x<=m) ls=query(rt<<1,l,m,x,y);
	if(y>m) rs=query(rt<<1|1,m+1,r,x,y);
	if(x<=m&&y>m) return ls+rs;
	if(x<=m) return ls;
	if(y>m) return rs;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	int T;scanf("%d",&T);
	while(T--) {
		scanf("%d",&n);
		For(i,1,n) scanf("%d",in+i);
		build(1,1,n);
		scanf("%d",&q);
		while(q--) {
			int x1,x2,y1,y2;
			scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
			if(y1<x2) printf("%d\n",query(1,1,n,x1,y1).suf+query(1,1,n,y1+1,x2-1).sum+query(1,1,n,x2,y2).pre);
			else {
				int ans=query(1,1,n,x2,y1).ans;
				ans=std::max(ans,query(1,1,n,x2,y1).suf+query(1,1,n,y1+1,y2).pre);
				ans=std::max(ans,query(1,1,n,x1,x2-1).suf+query(1,1,n,x2,y2).pre);
				printf("%d\n",ans);
			}
		}
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}