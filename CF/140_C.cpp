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

const int INF=1e9;
const int maxn=1e5+10;
std::map<int,int> count;
std::priority_queue<P> q;
int n,x;
struct Lan {
	std::vector<int> num;
	Lan(std::vector<int> vi) :num(vi){}
};
std::vector<Lan> Log;

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	scanf("%d",&n);
	FOR(i,0,n) { scanf("%d",&x);count[x]++; }
	for(auto &t:count) q.push(P(t.second,t.first));
	int ans=0;
	while (q.size()>=3) {
		P tmp[3];
		FOR(i,0,3) { tmp[i]=q.top();q.pop(); }
		std::vector<int> t={ tmp[0].second,tmp[1].second,tmp[2].second };
		Log.push_back(Lan(t));
		++ans;
		FOR(i,0,3) if (tmp[i].first>1) q.push(P(tmp[i].first-1,tmp[i].second));
	}
	printf("%d\n",ans);
	for (auto &t:Log) {
		std::sort(t.num.begin(),t.num.end());
		printf("%d %d %d\n",t.num[2],t.num[1],t.num[0]);
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}