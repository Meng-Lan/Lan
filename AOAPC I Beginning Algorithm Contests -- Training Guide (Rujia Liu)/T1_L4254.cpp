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

const int INF = 1e9;
struct Lan {
	int r, d, w;
	Lan(int r, int d, int w) :r(r), d(d), w(w) {}
	Lan() :Lan(0, 0, 0) {}
	bool operator<(const Lan &rhs) const {
		return d > rhs.d || d == rhs.d&&w < rhs.w;
	}
};
std::vector<Lan> v;
int n;

bool check(int m, const int end) {
	std::priority_queue<Lan> q;
	int cur = 0;
	For(i, v.begin()->r, end) {
		while (cur < v.size() && v[cur].r <= i) q.push(v[cur++]);
		int cnt = m;
		while (cnt && !q.empty()) {
			Lan t = q.top(); q.pop();
			//printf("m:%d i:%d r:%d d:%d w:%d\n", m, i, t.r, t.d, t.w);
			if (t.d <= i) return false;
			int work = std::min(cnt, t.w);
			t.w -= work;
			cnt -= work;
			if (t.w) q.push(t);
		}
		if (cur >= v.size() && q.empty()) return true;
	}
	return false;
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		int d, r, w, end = 0;
		v.clear();
		FOR(i, 0, n) {
			scanf("%d%d%d", &r, &d, &w);
			v.emplace_back(Lan(r, d, w));
			end = std::max(end, d);
		}
		std::sort(v.begin(), v.end(), [](const Lan &l, const Lan &r)
		{return l.r < r.r || l.r == r.r&&l.d < r.d; });
		//for (auto &t : v) printf("L:%d R:%d w:%d\n", t.r, t.d, t.w);
		int l = 0; r = INF;
		while (l < r) {
			int m = l + (r - l) / 2;
			if (check(m, end)) r = m;
			else l = m + 1;
		}
		printf("%d\n", l);
	}


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}