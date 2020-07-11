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

const ll N=1e12;
const int sqrtn=1e6+10;
const int mod=998244353;
int vis[sqrtn];
ll l,r,k,in[sqrtn];
//std::vector<int> ap[sqrtn];
int ta[sqrtn][33];
int top[sqrtn];
int sz,prime[sqrtn];

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	std::vector<int> pri=Eratosthenes(sqrtn,vis);
	for(auto &p:pri) prime[sz++]=p;
	assert(sz==pri.size());
	int T;scanf("%d",&T);
	while(T--) {
		scanf("%lld%lld%lld",&l,&r,&k);
		ll minus=r-l+1;
		for(ll i=l;i<=r;++i) in[i-l]=i;
		//For(i,0,minus) ap[i].clear();
		For(i,0,minus) top[i]=0;
		//printf("minus:%lld\n",minus);
		int len=floor(sqrt(r)+0.5);
		//for(auto &p:pri) {
		FOR(k,0,sz){
			const int &p=prime[k];
			if(p>len) break;
			ll ln=(l-1)/p,rn=r/p;
			if(ln==rn) continue;
			ll L=(l-1),R=r;
			while(L<R) {
				ll m=L+(R-L)/2;
				if(m/p>ln) R=m;
				else { L=m+1; }
			}
			//printf("L:%lld p:%d\n",L,p);
			assert(L%p==0);
			for(int i=(int)L-l;i<minus;i+=p) {
				ll &t=in[i];
				int cnt=0;
				while(t%p==0) { ++cnt;t/=p; }
				//ap[i].push_back(cnt);
				ta[i][top[i]]=cnt;++top[i];
				//assert(ap[i][ap[i].size()-1]==ta[i][top[i]-1]);
				//int j=top[i]-1;
				//printf("ap[%d][%d]=%d\n",i,j,ap[i][j]);
				//printf("ta[%d][%d]=%d\n",i,j,ta[i][j]);
			}
		}
		ll ans2=0;
		FOR(i,0,minus) {
			ll tmp2=1;
			//if(in[i]>1) ap[i].push_back(1);
			if(in[i]>1) { ta[i][top[i]]=1;++top[i]; }
			//assert(top[i]==ap[i].size());
			/*for(auto cnt:ap[i]) {
				tmp*=(ll)cnt*k+1;
				tmp%=mod;
			}*/
			FOR(j,0,top[i]) { tmp2*=ta[i][j]*k+1; tmp2%=mod; }
			/*FOR(j,0,top[i]) {
				printf("ap[%d][%d]=%d\n",i,j,ap[i][j]);
				printf("ta[%d][%d]=%d\n",i,j,ta[i][j]);
				assert(ap[i][j]==ta[i][j]);
			}*/
			//ans=(ans+tmp)%mod;
			ans2=(ans2+tmp2)%mod;
		}
		//printf("max:%d\n",max);
		printf("%lld\n",ans2);
	}


#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}