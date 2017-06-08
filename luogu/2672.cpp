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
#include<algorithm>
#include<functional>
#include<ctime>
#include<cassert>
using std::cin;
using std::cout;
using std::endl;
typedef long long ll;
typedef std::pair<int, int> P;
typedef std::pair<ll, int> Pll;
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
int n, vis[maxn];
P in[maxn];
std::map<int, int> m;

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	scanf("%d", &n);
	FOR(i, 0, n) scanf("%d", &in[i].first);
	FOR(i, 0, n) m[in[i].first] = std::max(m[in[i].first], i);
	FOR(i, 0, n) scanf("%d", &in[i].second);
	std::priority_queue<Pll> q1, q2;
	FOR(i, 0, n) q2.push(mp((ll)in[i].first * 2 + in[i].second, i));
	ll ans = q2.top().first;
	printf("%lld\n", ans);
	int Max = in[q2.top().second].first;
	For(i, 0, m[in[q2.top().second].first]) if (i != q2.top().second) q1.push(mp(in[i].second, i));
	int left = m[in[q2.top().second].first] + 1; q2.pop(); vis[left - 1] = 1;
	FOR(i, 1, n) {
		while (!q2.empty() && vis[q2.top().second]) q2.pop();
		while (!q1.empty() && vis[q1.top().second]) q1.pop();
		if (!q2.empty()) {
			int right, t;
			if (!q1.empty() && q1.top().first >= q2.top().first - 2 * Max) {
				ans += q1.top().first;
				right = m[in[q1.top().second].first];
				t = q1.top().second; vis[t] = 1; q1.pop();
			}
			else {
				ans += q2.top().first - 2 * Max;
				right = m[in[q2.top().second].first];
				Max = in[q2.top().second].first;
				t = q2.top().second; vis[t] = 1; q2.pop();
			}
			if (right >= left) For(j, left, right) if (j != t) q1.push(mp(in[i].second, i));
		}
		else {
			const Pll &t = q1.top();
			ans += t.first;
			vis[q1.top().second] = 1; q1.pop();
		}
		printf("%lld\n", ans);
	}

#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}