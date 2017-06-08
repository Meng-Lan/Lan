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
typedef std::pair<double, double> P;
#define FOR(i,init,len) for(int i=(init);i<(len);++i)
#define For(i,init,len) for(int i=(init);i<=(len);++i)
#define mp std::make_pair
ll Factorial(ll i) { return i > 1 ? i*Factorial(i - 1) : 1; }
ll Combination(ll n, ll r) {
	if (n - r < r) r = n - r;
	ll ansn = 1, ansr = 1;
	for (int i = n - r + 1; i <= n; ++i) ansn *= i;
	for (int j = 1; j <= r; ++j) ansr *= j;
	return ansn / ansr;
}
ll gcd(ll a, ll b) { return b ? gcd(b, a%b) : a; }
ll lcm(ll a, ll b) { return a*b / gcd(a, b); }

const int maxn = 100010;
const double eps = 1e-5;
int L, D, n;
P pos[maxn], lr[maxn];

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	while (scanf("%d%d%d", &L, &D, &n) == 3 && n) {
		double len;
		FOR(i, 0, n) {
			scanf("%lf%lf", &pos[i].first, &pos[i].second);
			if (D*D != pos[i].second*pos[i].second)
				len = sqrt(D*D - pos[i].second*pos[i].second);
			else len = 0.0;
			lr[i].first = pos[i].first - len; lr[i].second = pos[i].first + len;
		}
		int cnt = 0, l = 0, r = 0;
		std::sort(lr, lr + n, [](const P &s, const P &t) {return s.second < t.second || s.second == t.second&&s.first < t.first; });
		double min = 0;
		while (l < n) {
			min = lr[l++].second;
			while (l < n&&lr[l].first<= min) ++l;
			++cnt;
		}
		printf("%d\n", cnt);
	}

#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}