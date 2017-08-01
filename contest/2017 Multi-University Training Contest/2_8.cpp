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

const int maxn=105;
const int maxm=maxn*maxn;
int n,m,pos[maxn],sta[maxn][2],top;
std::vector<P> col[maxm];

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	int T;scanf("%d",&T);
	while(T--) {
		scanf("%d%d",&n,&m);
		int all=((n*(n+1))>>1)*((m*(m+1))>>1),cnt;
		ll ans=0;
		FOR(i,0,n*m) col[i].clear();
		FOR(i,0,n) FOR(j,0,m) { int x;scanf("%d",&x);col[x].push_back(P(i,j)); }
		FOR(i,0,n*m) if(col[i].size()) {
			int x=col[i][0].first;
			cnt=((x*(x+1))>>1)*((m*(m+1))>>1);
			memset(pos,-1,(m+1)*sizeof(int));
			for(int j=0,len=col[i].size();j<len;) {
				int x=col[i][j].first;
				for(;j<len&&col[i][j].first==x;++j) pos[col[i][j].second]=x;
				int add=0,sum=0;top=-1;
				for(int k=0;k<m;++k) {
					int w=1,h=x-pos[k];
					for(;top>=0&&sta[top][1]>=h;--top) {
						w+=sta[top][0];
						add-=sta[top][0]*sta[top][1];
					}
					sta[++top][0]=w;
					sta[top][1]=h;
					add+=w*h;
					sum+=add;
				}
				int diff=(j<len?col[i][j].first:n)-x;
				cnt+=diff*sum+((diff*(diff-1))>>1)*((m*(m+1))>>1);
			}
			ans+=all-cnt;
		}
		printf("%.9f\n",(double)ans/all);
	}


#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}