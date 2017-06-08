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

struct Lan {
	int len, d;
	Lan(int len, int d) :len(len), d(d) {}
	Lan() :Lan(0, 0) {}
	bool operator<(const Lan &rhs)const {
		return d < rhs.d || d == rhs.d&&len < rhs.len;
	}
};
int n;
std::vector<Lan> v;

int solve(int from, int to) {
	int cur = 0, cnt = 0, max1 = 0, max2 = 0;
	while (cur < n) {
		if (cur == from) ++cur;
		if (cur >= n) break;
		cnt += v[cur].len;
		max2 = std::max(max2, cnt - v[cur].d);
		if (max2 > max1) std::swap(max2, max1);
		if (cur == to) {
			cnt += v[from].len;
			max2 = std::max(max2, cnt - v[from].d);
			if (max2 > max1) std::swap(max2, max1);
		}
		++cur;
	}
	return max1 + max2;
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		v.clear();
		int len, d;
		FOR(i, 0, n) {
			scanf("%d%d", &len, &d);
			v.emplace_back(Lan(len, d));
		}
		std::sort(v.begin(), v.end());
		int ans = solve(-1, -1);
		FOR(i, 0, n) FOR(j, i + 1, n) ans = std::min(ans, solve(i, j));
		printf("%d\n", ans);
	}



#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}