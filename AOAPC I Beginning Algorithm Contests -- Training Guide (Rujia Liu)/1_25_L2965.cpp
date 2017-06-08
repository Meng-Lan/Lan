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

const int maxn = 24;
std::map<int, int> m;
int A[maxn], n;
char s[1000];

int bitcount(int i) { return i == 0 ? 0 : bitcount(i / 2) + (i & 1); }

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	while (scanf("%d", &n) == 1&&n) {
		memset(A, 0, sizeof(A));
		FOR(i, 0, n) {
			scanf(" %s", s);
			int len = strlen(s);
			FOR(j, 0, len) A[i] ^= (1 << (s[j] - 'A'));
		}

		m.clear();
		int n1 = n / 2, n2 = n - n1;
		FOR(i, 0, (1 << n1)) {
			int x = 0;
			FOR(j, 0, n1) if (i&(1 << j)) x ^= A[j];
			if (!m.count(x) || bitcount(m[x]) < bitcount(i)) m[x] = i;
		}

		int ans = 0;
		FOR(i, 0, (1 << n2)) {
			int x = 0;
			FOR(j, 0, n2) if (i&(1 << j)) x ^= A[n1 + j];
			if (m.count(x) && bitcount(ans) < bitcount(m[x]) + bitcount(i)) ans = (i << n1) ^ m[x];
		}

		printf("%d\n", bitcount(ans));
		FOR(i, 0, n) if (ans&(1 << i)) printf("%d ", i + 1);
		putchar('\n');
	}



#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}