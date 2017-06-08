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

const int maxn = 300010;
int n, q;
P in[maxn];
std::deque<P> dq;

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	scanf("%d%d", &n, &q);
	int cnt = 0, l = 0;
	FOR(i, 0, q) {
		int t, x; scanf("%d%d", &t, &x);
		if (t == 1) {
			++cnt; ++in[x].second; dq.push_back(mp(x, in[x].second));
		}
		if (t == 2) {
			int len = in[x].second - in[x].first;
			cnt -= len; in[x].first = in[x].second;
		}
		if (t == 3) {
			if (x > l) {
				FOR(j, l, x) {
					P &u = dq[j];
					if (u.second > in[u.first].first) {
						++in[u.first].first; --cnt;
					}
				}
				l = x - 1;
			}
		}
		printf("%d\n", cnt);
	}


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}