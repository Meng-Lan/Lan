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

const int maxn = 10005;
int e[maxn], vis[maxn], p, q, r, s;
std::vector<int> prime;

void Eratosthenes() {
	int m = sqrt(maxn + 0.5);
	memset(vis, 0, sizeof(vis));
	For(i, 2, m) if (!vis[i]) for (int j = i*i; j < maxn; j += i) vis[j] = 1;
	FOR(i, 2, maxn) if (!vis[i]) prime.push_back(i);
}

void add_inter(int n, int d) {
	FOR(i, 0, prime.size()) {
		while (n%prime[i] == 0) {
			e[i] += d;
			n /= prime[i];
		}
		if (n == 1) return;
	}
}

void add_fatcorial(int n, int d) {
	For(i, 1, n) add_inter(i, d);
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	Eratosthenes();
	while (scanf("%d%d%d%d", &p, &q, &r, &s) == 4) {
		memset(e, 0, sizeof(e));
		add_fatcorial(p, 1);
		add_fatcorial(p - q, -1);
		add_fatcorial(q, -1);
		add_fatcorial(r, -1);
		add_fatcorial(r - s, 1);
		add_fatcorial(s, 1);
		double ans = 1;
		FOR(i, 0, prime.size()) ans *= pow(prime[i], e[i]);
		printf("%.5f\n", ans);
	}


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}