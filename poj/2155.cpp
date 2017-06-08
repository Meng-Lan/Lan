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

const int maxn = 1e3 + 5;
int A[maxn][maxn], n, q;

inline int lowbit(int x) {
	return x&-x;
}

void add(int x, int y) {
	for (int i = x; i <= n; i += lowbit(i))
		for (int j = y; j <= n; j += lowbit(j))
			A[i][j] += 1;
}

int sum(int x, int y) {
	int cnt = 0;
	for (int i = x; i > 0; i -= lowbit(i))
		for (int j = y; j > 0; j -= lowbit(j))
			cnt += A[i][j];
	return cnt;
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &q);
		char s[10];
		memset(A, 0, sizeof(A));
		FOR(i, 0, q) {
			scanf(" %s", s);
			if (s[0] == 'C') {
				int x1, x2, y1, y2;
				scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
				add(x1, y1);
				add(x1, y2 + 1);
				add(x2 + 1, y1);
				add(x2 + 1, y2 + 1);
			}
			if (s[0] == 'Q') {
				int x, y;
				scanf("%d%d", &x, &y);
				printf("%d\n", sum(x, y) % 2);
			}
		}
		if (T) puts("");
	}



#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}