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
int in[maxn], n, m, k, count[1005], size;

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int T; scanf("%d", &T);
	For(kase, 1, T) {
		memset(count, 0, sizeof(count)); size = 0;
		scanf("%d%d%d", &n, &m, &k);
		in[0] = 1, in[1] = 2, in[2] = 3;
		FOR(i, 3, n) in[i] = (in[i - 3] + in[i - 2] + in[i - 1]) % m + 1;
		int ans = maxn, l = 0, r = 0;
		while (r<n) if (in[r] <= k) {
			if (!count[in[r]]) ++size; ++count[in[r]];
			if (size == k) {
				while (l <= r && (in[l]>k || count[in[l]] > 1)) { if (in[l] <= k) --count[in[l]]; ++l; }
				ans = std::min(ans, r - l + 1); --size; --count[in[l++]];
			}
			++r;
		}
		else ++r;
		printf("Case %d: ", kase);
		if (ans == maxn) printf("sequence nai\n");
		else printf("%d\n", ans);
	}


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}