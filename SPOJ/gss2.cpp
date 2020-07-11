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

const int maxn=1e5+10;
int in[maxn],n,q;
struct Question {
	int l,r,id;
	void input() { scanf("%d%d",&l,&r); }
	bool operator<(const Question &rhs)const { return r<rhs.r||r==rhs.r&&l<rhs.l; }
}qs[maxn];
struct Lan {
	ll ms,s,add,pre;
}tree[maxn<<2];
ll ans[maxn];
int pre[maxn],pos[maxn*2];

void pushdown(int rt) {
	Lan &root=tree[rt],&ls=tree[rt<<1],&rs=tree[rt<<1|1];
	if(root.add||root.pre) {
		ls.ms=std::max(ls.ms,ls.s+root.pre);
		ls.pre=std::max(ls.pre,ls.add+root.pre);
		ls.add+=root.add;
		ls.s+=root.add;
		rs.ms=std::max(rs.ms,rs.s+root.pre);
		rs.pre=std::max(rs.pre,rs.add+root.pre);
		rs.add+=root.add;
		rs.s+=root.add;
		root.add=root.pre=0;
	}
}

void maintain(int rt) {
	Lan &root=tree[rt],&ls=tree[rt<<1],&rs=tree[rt<<1|1];
	root.ms=std::max(ls.ms,rs.ms);
	root.s=std::max(ls.s,rs.s);
}

void update(int rt,int l,int r,int x,int y,int v) {
	if(x<=l&&r<=y) {
		Lan &root=tree[rt];
		root.s+=v;root.add+=v;
		root.ms=std::max(root.ms,root.s);
		root.pre=std::max(root.pre,root.add);
		return;
	}
	int m=l+(r-l)/2;
	pushdown(rt);
	if(x<=m) update(rt<<1,l,m,x,y,v);
	if(m<y) update(rt<<1|1,m+1,r,x,y,v);
	maintain(rt);
}

ll query(int rt,int l,int r,int x,int y) {
	if(l>y||r<x) return 0;
	if(x<=l&&r<=y) return tree[rt].ms;
	int m=l+(r-l)/2;
	pushdown(rt);
	maintain(rt);
	return std::max(query(rt<<1,l,m,x,y),query(rt<<1|1,m+1,r,x,y));
}

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	scanf("%d",&n);
	For(i,1,n) { scanf("%d",in+i);pre[i]=pos[in[i]+maxn];pos[in[i]+maxn]=i; }
	//For(i,1,n) printf("#%d pre:%d pos:%d\n",i,pre[i],pos[in[i]+maxn]);
	scanf("%d",&q);
	FOR(i,0,q) { qs[i].input();qs[i].id=i; }
	std::sort(qs,qs+q);
	int l=0;
	For(i,1,n) {
		update(1,1,n,pre[i]+1,i,in[i]);
		while(l<q&&qs[l].r==i) {
			ans[qs[l].id]=std::max(0ll,query(1,1,n,qs[l].l,qs[l].r));
			//printf("id:%d l:%d r:%d ans:%d\n",qs[l].id,qs[l].l,qs[l].r,ans[qs[l].id]);
			++l;
		}
	}
	FOR(i,0,q) printf("%lld\n",ans[i]);


#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}