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

const int maxn = 1e6 + 10;
const int eps = 1e-9;
int w, vh, n, s;
struct Lan {
	double l, r, h;
	Lan(double l, double r, double h) :l(l), r(r), h(h) {}
	Lan() :Lan(0, 0, 0) {}
};
std::vector<Lan> v;
int in[maxn];

bool check(int m) {
	double l = v[0].l, r = v[0].r;
	FOR(i, 1, n) {
		double t = (v[i].h - v[i - 1].h)*vh / (double)m;
		l -= t, r += t;
		l = std::max(l, v[i].l), r = std::min(r, v[i].r);
		if (l > r&&std::abs(l - r) > eps) return false;
	}
	return true;
}

int solve() {
	int l = 0, r = s - 1;
	while (l < r) {
		int m = l + (r - l + 1) / 2;
		//printf("L:%d M:%d R:%d\n", l, m, r);
		if (check(in[m])) l = m;
		else r = m - 1;
	}
	return l;
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int T; scanf("%d", &T);
	assert(T >= 0);
	while (T--) {
		scanf("%d%d%d", &w, &vh, &n);
		assert(w >= 1); assert(vh >= 1); assert(n >= 1);
		v.clear();
		double x, y;
		FOR(i, 0, n) {
			scanf("%lf%lf", &x, &y);
			v.emplace_back(Lan(x, x + w, y));
		}
		scanf("%d", &s);
		assert(s >= 1);
		FOR(i, 0, s) scanf("%d", in + i);
		std::sort(in, in + s);
		int ans = solve();
		if (check(in[ans])) printf("%d\n", in[ans]);
		else printf("IMPOSSIBLE\n");
	}


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}