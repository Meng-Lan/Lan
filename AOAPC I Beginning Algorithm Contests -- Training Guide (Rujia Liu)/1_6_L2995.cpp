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
typedef std::pair<int, int> P;
#define FOR(i,init,len) for(int i=(init);i<(len);++i)
#define For(i,init,len) for(int i=(init);i<=(len);++i)
#define mp std::make_pair
ll Factorial(ll i) { return i > 1 ? i*Factorial(i - 1) : 1; }
ll Combination(ll n, ll r) {
	if (n - r < r) r = n - r;
	ll ansn = 1, ansr = 1;
	for (ll i = n - r + 1; i <= n; ++i) ansn *= i;
	for (ll j = 1; j <= r; ++j) ansr *= j;
	return ansn / ansr;
}
ll gcd(ll a, ll b) { return b ? gcd(b, a%b) : a; }
ll lcm(ll a, ll b) { return a / gcd(a, b)*b; }
std::vector<int> Eratosthenes(const int len, int *vis) {
	memset(vis, 0, sizeof(int)*len);
	std::vector<int> prime;
	int m = (int)sqrt(len + 0.5);
	For(i, 2, m) if (!vis[i]) for (int j = i*i; j < len; j += i) vis[j] = 1;
	FOR(i, 2, len) if (!vis[i]) prime.push_back(i);
	return prime;
}
void phi_table(int n, int *phi) {
	For(i, 2, n) phi[i] = 0;
	phi[1] = 1;
	For(i, 2, n) if (!phi[i])
		for (int j = i; j <= n; j += i) {
			if (!phi[j]) phi[j] = j;
			phi[j] = phi[j] / i*(i - 1);
		}
}

const int maxn = 10;
int n;
char in[6][maxn][maxn];
char pos[maxn][maxn][maxn];

void get(int k, int i, int j, int len, int &x, int &y, int &z) {
	if (k == 0) { x = j; y = i; z = len; }
	if (k == 1) { x = len; y = i; z = n - j - 1; }
	if (k == 2) { x = n - j - 1; y = i; z = n - len - 1; }
	if (k == 3) { x = n - len - 1; y = i; z = j; }
	if (k == 4) { x = j; y = len; z = n - i - 1; }
	if (k == 5) { x = j; y = n - len - 1; z = i; }
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	while (scanf("%d", &n) == 1 && n) {
		memset(pos, '#', sizeof(pos));
		FOR(j, 0, n) FOR(i, 0, 6) FOR(k, 0, n) scanf(" %c", &in[i][j][k]);
		FOR(i, 0, 6) FOR(j, 0, n) FOR(k, 0, n) if (in[i][j][k] == '.') {
			FOR(l, 0, n) {
				int x, y, z;
				get(i, j, k, l, x, y, z);
				pos[x][y][z] = '.';
			}
		}
		/*
		FOR(z, 0, n) {
			FOR(y, 0, n) {
				FOR(x, 0, n) putchar(pos[x][y][z]);
				putchar(' ');
			}
			putchar('\n');
		}
		*/
		for (;;) {
			int done = true;
			FOR(i, 0, 6) FOR(j, 0, n) FOR(k, 0, n) if (in[i][j][k] != '.') {
				FOR(l, 0, n) {
					int x, y, z;
					get(i, j, k, l, x, y, z);
					if (pos[x][y][z] == '.') continue;
					if (pos[x][y][z] == '#') {
						pos[x][y][z] = in[i][j][k];
						break;
					}
					if (pos[x][y][z] == in[i][j][k]) break;
					//printf("i:%d j:%d k:%d l:%d x:%d y:%d z:%d\n", i, j, k, l, x, y, z);
					pos[x][y][z] = '.';
					done = false;
				}
			}
			if (done) break;
		}
		int ans = 0;
		FOR(i, 0, n) FOR(j, 0, n) FOR(k, 0, n) if (pos[i][j][k] != '.') ++ans;
		printf("Maximum weight: %d gram(s)\n", ans);
	}



#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}

/*
3
.R. YYR .Y. RYY .Y. .R.
GRB YGR BYG RBY GYB GRB
.R. YRR .Y. RRY .R. .Y.
2
ZZ ZZ ZZ ZZ ZZ ZZ
ZZ ZZ ZZ ZZ ZZ ZZ
0
*/