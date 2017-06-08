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

const int maxn = 1005;
int n;
P in[maxn];
double dist[maxn][maxn], d[maxn][maxn];

double complace(int i, int j) {
	return sqrt((double)(in[i].first - in[j].first)*(in[i].first - in[j].first) + (double)(in[i].second - in[j].second)*(in[i].second - in[j].second));
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	while (scanf("%d", &n) == 1 && n) {
		For(i, 1, n) scanf("%d%d", &in[i].first, &in[i].second);
		For(i, 1, n) For(j, 1, n) dist[i][j] = complace(i, j);
		for (int i = n - 1; i >= 2; --i)
			FOR(j, 1, i) {
			if (i == n - 1) d[i][j] = dist[i][n] + dist[j][n];
			else d[i][j] = std::min(d[i + 1][j] + dist[i + 1][i], d[i + 1][i] + dist[i + 1][j]);
		}
		printf("%.2f\n", d[2][1] + dist[2][1]);
	}


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}