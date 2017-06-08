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
int n, m;
char s[maxn][maxn];

bool check(int x, int y) {
	return x >= 0 && x < n&&y >= 0 && y < m;
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	scanf("%d%d", &n, &m);
	FOR(i, 0, n) scanf(" %s", s[i]);
	FOR(i, 0, n) FOR(j, 0, m) if (s[i][j] == '?') {
		int cnt = 0;
		FOR(k, 0, 8) {
			int x = i + dx[k];
			int y = j + dy[k];
			if (check(x, y) && s[x][y] == '*') ++cnt;
			s[i][j] = '0' + cnt;
		}
	}
	FOR(i, 0, n) printf("%s\n", s[i]);

#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}