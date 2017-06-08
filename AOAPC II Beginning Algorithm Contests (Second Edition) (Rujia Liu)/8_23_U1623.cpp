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

const int maxn = 1000010;
int n, m, ans[maxn], L[maxn], t;

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		bool ok = true;
		memset(ans, 0, sizeof(int)*(m + 2));
		memset(L, 0, sizeof(int)*(n + 2));
		std::set<int> si;
		For(i, 1, m) {
			scanf("%d", &t);
			if (!ok) continue;
			if (t) {
				ans[i] = -1;
				auto it = si.lower_bound(L[t]);
				if (it == si.end()) {
					ok = false; continue;
				}
				else {
					ans[*it] = t; L[t] = i;
					si.erase(it);
				}
			}
			else si.insert(i);
		}
		if (ok) {
			printf("YES\n");
			int cnt = 0;
			For(i, 1, m) if (ans[i] >= 0) {
				if (cnt++) putchar(' ');
				printf("%d", ans[i]);
			}
			putchar('\n');
		}
		else printf("NO\n");
	}



#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}