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

const int maxn=10;
const int num[maxn][7]={
	{1,1,1,1,1,1,0},
	{0,0,1,1,0,0,0},
	{0,1,1,0,1,1,1},
	{0,1,1,1,1,0,1},
	{1,0,1,1,0,0,1},
	{1,1,0,1,1,0,1},
	{1,1,0,1,1,1,1},
	{0,1,1,1,0,0,0},
	{1,1,1,1,1,1,1},
	{1,1,1,1,1,0,1}
};
char s[maxn][maxn*maxn];

int getnum(int x,int y) {
	static int sta[maxn];
	memset(sta,0,sizeof(sta));
	sta[0]=s[x+1][y]=='X';
	sta[1]=s[x][y+1]=='X';
	sta[2]=s[x+1][y+3]=='X';
	sta[3]=s[x+4][y+3]=='X';
	sta[4]=s[x+6][y+1]=='X';
	sta[5]=s[x+4][y]=='X';
	sta[6]=s[x+3][y+1]=='X';
	FOR(i,0,maxn) FOR(j,0,7) {
		if(num[i][j]==sta[j]) {
			if(j==6) return i;
		}
		else break;
	}
	return -1;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	int T;scanf("%d",&T);
	while(T--) {
		FOR(i,0,7) scanf("%s",s+i);
		int a=getnum(0,0);
		int b=getnum(0,5);
		int c=getnum(0,12);
		int d=getnum(0,17);
		//printf("%d%d:%d%d\n",a,b,c,d);
		assert(a>=0&&b>=0&&c>=0&&d>=0);
		printf("%d%d:%d%d\n",a,b,c,d);
	}



#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}