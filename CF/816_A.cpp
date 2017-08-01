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

std::string s;

bool check(std::string &s) {
	int l=0,r=s.size()-1;
	while (l<r) if (s[l]!=s[r]) return false;else { l++;r--; }
	return true;
}

int c2n(char c) { return c-'0'; }

char n2c(int n) { return n+'0'; }

std::string getnext(std::string s) {
	int h=c2n(s[0])*10+c2n(s[1]),m=c2n(s[3])*10+c2n(s[4]);
	++m;
	if (m>=60) { ++h;m-=60; }
	if (h>23) h-=24;
	s[0]=n2c(h/10);s[1]=n2c(h%10);s[3]=n2c(m/10);s[4]=n2c(m%10);
	return s;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	cin>>s;
	int ans=0;
	while (!check(s)) {
		s=getnext(s);++ans;
		//cout<<s<<endl;
	}
	cout<<ans<<endl;


#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}