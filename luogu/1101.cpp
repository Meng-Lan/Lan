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
typedef std::pair<int, int> P;
#define FOR(i,init,len) for(int i=(init);i<(len);++i)
#define For(i,init,len) for(int i=(init);i<=(len);++i)
#define mp std::make_pair
ll Factorial(ll i) { return i > 1 ? i*Factorial(i - 1) : 1; }
ll Combination(ll n, ll r) {
	if (n - r < r) r = n - r;
	ll ansn = 1, ansr = 1;
	for (int i = n - r + 1; i <= n; ++i) ansn *= i;
	for (int j = 1; j <= r; ++j) ansr *= j;
	return ansn / ansr;
}
ll gcd(ll a, ll b) { return b ? gcd(b, a%b) : a; }
ll lcm(ll a, ll b) { return a*b / gcd(a, b); }

const int maxn = 105;
const int dx[] = { -1,-1,0,1,1,1,0,-1 };
const int dy[] = { 0,-1,-1,-1,0,1,1,1 };
char s[maxn][maxn];
const char tmp[] = "yizhong";
int n,vis[maxn][maxn];

inline bool check(int x, int y, int idx) { return x >= 0 && x < n&&y >= 0 && y < n&&s[x][y] == tmp[idx]; }

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	scanf("%d", &n); FOR(i, 0, n) scanf(" %s", s[i]);
	FOR(i, 0, n) FOR(j, 0, n) if (s[i][j] == 'y') FOR(k, 0, 8) {
		int ok = true;
		int x = i, y = j;
		FOR(l, 1, 7) if (!check(x += dx[k], y += dy[k], l)) { ok = false; break; }
		x = i; y = j;
		if (ok) { vis[x][y] = 1; FOR(l, 1, 7) vis[x += dx[k]][y += dy[k]] = 1; }
	}
	FOR(i, 0, n) {
		FOR(j, 0, n) if (vis[i][j]) putchar(s[i][j]);
		else putchar('*'); putchar('\n');
	}


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}

/*
8        
qyizhong 
gydthkjy 
nwidghji 
orbzsfgz 
hhgrhwth 
zzzzzozo 
iwdfrgng 
yyyygggg
*/