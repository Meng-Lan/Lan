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
typedef std::pair<int, int> P;
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

const int maxn = 50010;
P in[maxn];

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int n; scanf("%d", &n);
	FOR(i, 0, n) scanf("%d%d", &in[i].first, &in[i].second);
	std::sort(in, in + n, [](const P &s, const P &t) {return s.first < t.first || s.first == t.first&&s.second < t.second; });
	P tmp; int ans = 0;
	FOR(i, 0, n) if (in[i].second - in[i].first > ans) {
		if (in[i].second > tmp.second&&tmp.second >= in[i].first) ans = std::max(ans, tmp.second - in[i].first);
		else if (in[i].first >= tmp.first&&in[i].second <= tmp.second) ans = std::max(ans, in[i].second - in[i].first);
		if (in[i].second - in[i].first > tmp.second - in[i].first) tmp = in[i];
	}
	printf("%d\n", ans);


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}