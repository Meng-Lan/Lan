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

const int INF = 1e9;
int s, n;
std::vector<int> in;

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	while (scanf("%d", &s) == 1 && s) {
		scanf("%d", &n);
		std::vector<int> ms;
		int Max = 0;
		FOR(i, 0, n) {
			int sum; scanf("%d", &sum); in.clear(); in.reserve(sum);
			FOR(j, 0, sum) { int t; scanf("%d", &t); in.push_back(t); }
			std::sort(in.begin(), in.end());
			int len = s*in.back() + 10;
			std::vector<int> d(len, INF);
			d[0] = 0;
			FOR(j, 0, in.size())
				for (int l = 0; l < s; ++l)
					for (int k = len - in[j] - 1; k >= 0; --k) d[k + in[j]] = std::min(d[k + in[j]], d[k] + 1);
			int cnt = 0;
			for (; cnt < len; ++cnt) if (d[cnt]>s) break;
			if (cnt > Max) { Max = cnt; ms = in; }
			else if (cnt == Max&&in.size() < ms.size()) ms = in;
			else if (cnt == Max&&in.size() == ms.size()) for (int j = ms.size() - 1; j >= 0; --j) {
				if (in[j] < ms[j]) { ms = in; break; }
				if (ms[j] < in[j]) break;
			}
		}
		printf("max coverage =%4d :", Max-1);
		for (auto &t : ms) printf("%3d", t); putchar('\n');
	}



#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}