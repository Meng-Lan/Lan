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

const int maxn = 10010;
int n, in[maxn];

inline int find(const int &bgn,const int &x) {
	For(i, bgn, n) if (in[i] == x) return i;
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		For(i, 1, n) scanf("%d", in + i);
		std::vector<P> ans;
		int cnt = 1;
		FOR(i, 1, n) {
			int idx = find(cnt, i);
			if (idx != cnt) {
				if (n - idx + 1 >= idx - cnt) {
					int left = cnt, right = idx, len = idx - cnt;
					//printf("left:%d right:%d len:%d\n", left, right, len);
					ans.push_back(mp(left, right + len - 1));
					FOR(i, 0, len) std::swap(in[left++], in[right++]);
				}
				else {
					int left = ((idx - cnt) & 1) ? cnt : cnt + 1;
					int right = left + (idx - left + 1) / 2;
					int len = right - left;
					//printf("left:%d right:%d len:%d\n", left, right, len);
					ans.push_back(mp(left, right + len - 1));
					FOR(i, 0, len) std::swap(in[left++], in[right++]);
					idx = find(cnt, i);
					left = cnt, right = idx, len = idx - cnt;
					//printf("left:%d right:%d len:%d\n", left, right, len);
					ans.push_back(mp(left, right + len - 1));
					FOR(i, 0, len) std::swap(in[left++], in[right++]);
				}
			}
			++cnt;
			//For(i, 1, n) printf("%d ", in[i]); putchar('\n');
		}
		printf("%d\n", ans.size());
		for (auto &t : ans) printf("%d %d\n", t.first, t.second);
	}

#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}