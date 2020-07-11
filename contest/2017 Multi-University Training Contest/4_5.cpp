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
typedef std::pair<ll,ll> P;
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

const int maxn=6e4+10;
ll d[6][maxn],in[6];
ll k;

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	int T;scanf("%d",&T);
	while(T--) {
		scanf("%lld",&k);
		For(i,1,4) scanf("%lld",in+i);
		memset(d,-1,sizeof(d));
		int mod=std::min(in[1],in[2])*2;
		std::priority_queue<P,std::vector<P>,std::greater<P>> q;
		q.push(P(0,2));d[2][0]=0;
		while(!q.empty()) {
			P u=q.top();q.pop();
			ll dir=u.second%4+1;
			ll dis=u.first+in[u.second];
			if(d[dir][dis%mod]==-1||d[dir][dis%mod]>dis) {
				d[dir][dis%mod]=dis;
				q.push(P(dis,dir));
			}
			dir=(u.second-2+4)%4+1;
			dis=u.first+in[dir];
			if(d[dir][dis%mod]==-1||d[dir][dis%mod]>dis) {
				d[dir][dis%mod]=dis;
				q.push(P(dis,dir));
			}
		}
		ll ans=(~0ull)>>1;
		//cout<<ans<<endl;
		FOR(i,0,mod) {
			ll res=d[2][i];
			if(res==-1) continue;
			res+=std::max(0ll,((k-res+mod-1)/mod)*mod);
			while(res<k) res+=mod;
			ans=std::min(ans,res);
		}
		cout<<ans<<'\n';
	}


#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}