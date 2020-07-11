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
const double pi=acos(-1);
const double eps=1e-6;
int x[maxn],y[maxn],c[maxn],n;
struct PCS {
	double len,angle,c;
	void trans(int x,int y,int cost) {
		len=sqrt(pow(x,2)+pow(y,2));
		angle=atan2(y,x);
		c=cost;
	}
	bool operator<(const PCS &rhs)const { return angle<rhs.angle; }
}dot[maxn];

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	int T;scanf("%d",&T);
	while(T--) {
		ll left=0,right=0;
		scanf("%d",&n);
		FOR(i,0,n) scanf("%d%d%d",x+i,y+i,c+i);
		FOR(i,0,n) dot[i].trans(x[i],y[i],c[i]),right+=c[i];
		//FOR(i,0,n) printf("i:%d angle:%f len:%f\n",i,dot[i].angle,dot[i].len);
		std::sort(dot,dot+n);
		FOR(i,n,n<<1) dot[i]=dot[i-n];
		int m=n<<1;
		//FOR(i,0,n) printf("i:%d angle:%f len:%f\n",i,dot[i].angle,dot[i].len);
		int l=0,r=0;
		double rangle=0.0;
		//printf("pi:%f\n",pi);
		//printf("diff:%f\n",dot[1].angle-dot[0].angle);
		while(r<n&&dot[r].angle-dot[l].angle<=pi) {
			left+=dot[r].c;
			right-=dot[r].c;
			++r;
		}
		//printf("l:%d r:%d\n",l,r);
		ll ans=left*right;
		while(l<n) {
			left-=dot[l].c;
			right+=dot[l].c;
			++l;
			if(r==n&&dot[l].angle-dot[0].angle>pi) break;
			while(r<n&&dot[r].angle-dot[l].angle<=pi) {
				left+=dot[r].c;
				right-=dot[r].c;
				++r;
			}
			//printf("l:%d r:%d\n",l,r);
			ans=std::max(ans,left*right);
		}
		printf("%lld\n",ans);
	}


#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}