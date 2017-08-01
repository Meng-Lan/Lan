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

const int maxn=5e5+10;
const int mod=1e9+7;
int a[maxn],b[maxn],vis[maxn],next[maxn],n,kase;

int find(int i) {
	if(b[i]>0) return i;
	else return next[i]=find(next[i]);
}

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	while(scanf("%d",&n)==1&&n) {
		std::priority_queue<P> q;++kase;
		For(i,1,n) { scanf("%d",&a[i]);q.push(move(P(a[i]-i,i))); }
		For(i,1,n) { int x;scanf("%d",&x);b[x]++; }
		For(i,1,n+n) next[i]=i-1;b[0]=1;
		ll ans=0;
		For(i,n+1,n+n) {
			for(;;) {
				P t=q.top();
				int idx=find(t.second);
				if(idx==0) { q.pop();continue; }
				//printf("%d %d\n",t.first,t.second);
				ans+=t.first;ans%=mod;q.push(move(P(t.first-i,i)));
				--b[idx];
				//printf("#%d ans:%lld idx:%d\n",i,ans,idx);
				break;
			}
		}
		cout<<ans<<endl;
	}


#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}