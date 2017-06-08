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
const double eps = 1e-8;
int n, cnt[maxn], vis[maxn];

struct Node {
	int x, y, z, p;
	void input() {
		scanf("%d%d%d%d", &x, &y, &z, &p);
	}
}in[maxn];

struct Lan {
	int x, y, dis;
	Lan(int x, int y, int dis) :x(x), y(y), dis(dis) {}
	Lan() :Lan(0, 0, 0.0) {}
	bool operator<(const Lan &rhs)const {
		return dis < rhs.dis;
	}
};
std::vector<Lan> v;

inline int pow2(int t) {
	return t*t;
}

inline double distance(const Node &l, const Node &r) {
	return pow2(l.x - r.x) + pow2(l.y - r.y) + pow2(l.z - r.z);
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	while (scanf("%d", &n) == 1 && n) {
		FOR(i, 0, n) in[i].input();
		//FOR(i, 0, n) printf("#%d x:%d y:%d z:%d p:%d\n", i, in[i].x, in[i].y, in[i].z, in[i].p);
		v.clear();
		FOR(i, 0, n) FOR(j, i + 1, n) {
			v.emplace_back(i, j, distance(in[i], in[j]));
		}
		std::sort(v.begin(), v.end());
		P ans(0, 0);
		for (auto &t : cnt) t = 1;
		int i = 0;
		//for (auto &t : v) printf("dis:%d x:%d y:%d\n", t.dis, t.x, t.y);
		while (i < v.size()) {
			int b = i;
			while (i < v.size() && v[i].dis == v[b].dis) {
				Lan &t = v[i];
				if (in[t.x].p != in[t.y].p) {
					--cnt[t.x]; --cnt[t.y];
				}
				else {
					++cnt[t.x]; ++cnt[t.y];
				}
				++i;
			}
			int Count = 0;
			//printf("#%d->%d:\n", b, i);
			FOR(j, 0, n) {
				//printf("%d:%d\n", j, cnt[j]);
				if (cnt[j] < 0) ++Count;
			}
			if (Count > ans.first) ans = P(Count, v[b].dis);
		}
		printf("%d\n%.4f\n", ans.first, sqrt(ans.second));
	}



#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}