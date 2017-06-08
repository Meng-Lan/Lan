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

const int maxn = 25;
int m, n, k, in[maxn][maxn];
struct Lan {
	int x, y, v;
	Lan(int x = 0, int y = 0, int v = 0) :x(x), y(y), v(v) {}
	bool operator<(const Lan &t)const {
		return v > t.v;
	}
};
std::vector<Lan> data;

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	scanf("%d%d%d", &m, &n, &k);
	For(j, 1, m) For(i, 1, n) { scanf("%d", in[j] + i); if (in[j][i]) data.push_back(Lan(i, j, in[j][i])); }
	std::sort(data.begin(), data.end());
	if (data.size() && data[0].y * 2 + 1 <= k) {
		int ans = data[0].v, Time = data[0].y + 1;
		FOR(i, 1, data.size()) {
			const Lan &t1 = data[i - 1], &t2 = data[i];
			int min = std::abs(t1.x - t2.x) + std::abs(t1.y - t2.y) + 1;
			if (min + t2.y + Time <= k) { ans += t2.v; Time += min; }
			else break;
		}
		printf("%d\n", ans);
	}
	else printf("0\n");
	



#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}