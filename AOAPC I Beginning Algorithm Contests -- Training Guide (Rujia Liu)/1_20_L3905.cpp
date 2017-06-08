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

const int maxn = 1e5 + 10;
void updata(int x, int a, int w, double &L, double &R) {
	if (a == 0) {
		if (x <= 0 || x >= w) R = L - 1;
	}
	else if (a > 0) {
		L = std::max(L, -(double)x / a);
		R = std::min(R, double(w - x) / a);
	}
	else {
		L = std::max(L, (double)(w - x) / a);
		R = std::min(R, -(double)x / a);
	}
}

struct Event {
	double x;
	int type;
	Event(double x, int t) :x(x), type(t) {}
	Event() :Event(0, 0) {}
	bool operator <(const Event &rhs)const {
		return x < rhs.x || (x == rhs.x&&type > rhs.type);
	}
}events[maxn * 2];

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int T; scanf("%d", &T);
	while (T--) {
		int w, h, n, e = 0;
		scanf("%d%d%d", &w, &h, &n);
		FOR(i, 0, n) {
			int x, y, a, b;
			scanf("%d%d%d%d", &x, &y, &a, &b);
			double L = 0, R = 1e9;
			updata(x, a, w, L, R);
			updata(y, b, h, L, R);
			if (R > L) {
				events[e++] = Event(L, 0);
				events[e++] = Event(R, 1);
			}
		}
		std::sort(events, events + e);
		int cnt = 0, ans = 0;
		FOR(i, 0, e) {
			if (!events[i].type) ans = std::max(ans, ++cnt);
			else --cnt;
		}
		printf("%d\n", ans);
	}


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}