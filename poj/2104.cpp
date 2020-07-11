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
int n,m,in[maxn],root[maxn],sz,l,r,k;
struct Node { int l,r,sum; }t[maxn*40];
std::vector<int> v;

int getid(int x) { return std::lower_bound(v.begin(),v.end(),x)-v.begin()+1; }

void update(int l,int r,int  &x,int y,int pos) {
	t[++sz]=t[y];t[sz].sum++;x=sz;
	if(l==r) return;
	int m=l+(r-l)/2;
	if(pos<=m) update(l,m,t[x].l,t[y].l,pos);
	else update(m+1,r,t[x].r,t[y].r,pos);
}

int query(int l,int r,int x,int y,int k) {
	if(l==r) return l;
	int m=l+(r-l)/2;
	int diff=t[t[y].l].sum-t[t[x].l].sum;
	if(diff>=k) return query(l,m,t[x].l,t[y].l,k);
	else return query(m+1,r,t[x].r,t[y].r,k-diff);
}

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	scanf("%d%d",&n,&m);
	For(i,1,n) scanf("%d",in+i),v.push_back(in[i]);
	std::sort(v.begin(),v.end());
	v.erase(std::unique(v.begin(),v.end()),v.end());
	For(i,1,n) update(1,n,root[i],root[i-1],getid(in[i]));
	FOR(i,0,m) {
		scanf("%d%d%d",&l,&r,&k);
		printf("%d\n",v[query(1,n,root[l-1],root[r],k)-1]);
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}