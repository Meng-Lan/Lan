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

int val, bgn, cnt, tmp, ans;
std::vector<P> vp;

bool cmp(int v,int sum) {
	FOR(i, 0, vp.size()) if (vp[i].first != val && (vp[i].first - bgn + v)*vp[i].second>sum) return false;
	return true;
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	scanf("%d%d%d", &val, &bgn, &cnt);
	vp.push_back(mp(bgn, cnt));
	int f, s;
	while (scanf("%d%d", &f, &s) == 2) {
		if (f == -1 && s == -1) break;
		P t = vp.back();
		int diff = (s - t.second) / (f - t.first);
		int len = f - t.first;
		For(i, 1, len) vp.push_back(mp(t.first + i, t.second + i*diff));
	}
	{
		int diff; scanf("%d", &diff);
		P t = vp.back();
		for (int i = 1; t.second - i*diff > 0; ++i) vp.push_back(mp(t.first + i, t.second - i*diff));
	}
	FOR(i, 0, vp.size()) if (vp[i].first == val) tmp = vp[i].second;
	//for (auto &t : vp) printf("sum:%d val:%d\n", t.first, t.second);
	for (int i = 0;; ++i) {
		int sum1 = (val + i - bgn)*tmp;
		int sum2 = (val - i - bgn)*tmp;
		if (cmp(i, sum1)) {
			ans = i; break;
		}
		if (cmp(-i, sum2)) {
			ans = -i; break;
		}
	}
	printf("%d\n", ans);



#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}