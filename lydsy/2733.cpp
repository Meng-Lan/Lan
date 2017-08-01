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
const int lgn=20;
int fa[maxn],rt[maxn],v[maxn],id[maxn],n,m,q;
int ls[maxn*lgn],rs[maxn*lgn],sum[maxn*lgn],sz;

int find(int x) { return x==fa[x]?x:fa[x]=find(fa[x]); }

void insert(int &k,int l,int r,int val) {
	if(!k) k=++sz;
	if(l==r) { sum[k]=1;return; }
	int m=l+(r-l)/2;
	if(val<=m) insert(ls[k],l,m,val);
	else insert(rs[k],m+1,r,val);
	sum[k]=sum[ls[k]]+sum[rs[k]];
}

int query(int k,int l,int r,int rnk) {
	if(l==r) return l;
	int m=l+(r-l)/2;
	if(rnk<=sum[ls[k]]) return query(ls[k],l,m,rnk);
	else return query(rs[k],m+1,r,rnk-sum[ls[k]]);
}

int merge(int x,int y) {
	if(!x) return y;
	if(!y) return x;
	ls[x]=merge(ls[x],ls[y]);
	rs[x]=merge(rs[x],rs[y]);
	sum[x]=sum[ls[x]]+sum[rs[x]];
	return x;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	scanf("%d%d",&n,&m);
	For(i,1,n) scanf("%d",v+i);
	For(i,1,n) fa[i]=i;
	int x,y;
	For(i,1,m) {scanf("%d%d",&x,&y);
		fa[find(x)]=find(y);
	}
	For(i,1,n) {
		insert(rt[find(i)],1,n,v[i]);
		id[v[i]]=i;
	}
	scanf("%d",&q);
	char cmd[2];
	while(q--) {
		scanf(" %s",cmd);scanf("%d%d",&x,&y);
		if(cmd[0]=='Q') {
			int p=find(x);
			if(y>sum[rt[p]]) { puts("-1");continue; }
			int t=query(rt[p],1,n,y);
			printf("%d\n",id[t]);
		}
		else {
			int p=find(x),q=find(y);
			if(p!=q) {
				fa[p]=q;
				rt[q]=merge(rt[p],rt[q]);
			}
		}
	}


#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}