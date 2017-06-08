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

const int maxn = 505;
int in[maxn], n, ans[maxn], tmp[maxn];
P len[maxn];

int exchange() {
	int  cnt = 0;
	For(i, 1, n) if (ans[i] != i) {
		tmp[ans[i]] = tmp[i];
		ans[tmp[i]] = ans[i];
		++cnt;
	}
	return cnt;
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	while (scanf("%d", &n) == 1 && n) {
		memset(len, 0, sizeof(len));
		FOR(i, 0, n) scanf("%d", in + i);
		FOR(i, 0, n) FOR(j, 0, n) if (in[(i + j) % n] == j + 1) ++len[i].first;
		FOR(i, 0, n) FOR(j, 0, n) if (in[(i - j + n) % n] == j + 1) ++len[i].second;
		//FOR(i, 0, n) printf("%d# %d %d\n", i, len[i].first, len[i].second);
		int cnt = maxn;
		FOR(i, 0, n) {
			if ((n - len[i].first) / 2 < cnt) {
				FOR(j, 0, n) {
					ans[j + 1] = in[(i + j) % n];
					tmp[ans[j + 1]] = j + 1;
				}
				cnt = std::min(cnt, exchange());
			}
			if ((n - len[i].second) / 2 <= cnt) {
				FOR(j, 0, n) {
					ans[j + 1] = in[(i - j + n) % n];
					tmp[ans[j + 1]] = j + 1;
				}
				cnt = std::min(cnt, exchange());
			}
			//printf("#%d cnt:%d\n", i, cnt);
		}
		printf("%d\n", cnt);
	}

#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}