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

const int maxn = 100010;
int n, in[maxn];

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		FOR(i, 0, n) scanf("%d", in + i);
		ll sum = 0;
		int Max = 0, cnt = 1;
		FOR(i, 0, n - 1) {
			if (std::abs(in[i] - in[i + 1]) > Max) { Max =std::abs(in[i] - in[i + 1]); cnt = 1; }
			else if (std::abs(in[i] - in[i + 1]) == Max) ++cnt;
		}
		FOR(i, 0, n - 2) {
			if (std::abs(in[i] - in[i + 2]) > Max) sum += std::abs(in[i] - in[i + 2]);
			else {
				if ((std::abs(in[i] - in[i + 1]) == Max || std::abs(in[i + 1] - in[i + 2]) == Max) && cnt <= 2) {
					int t = 0;
					FOR(j, 0, i) t = std::max(t, std::abs(in[j] - in[j + 1]));
					t = std::max(t, std::abs(in[i] - in[i + 2]));
					FOR(j, i + 2, n - 1) t = std::max(t, std::abs(in[j] - in[j + 1]));;
					sum += t;
				}
				else sum += Max;
			}
		}
		Max = 0;
		FOR(i, 1, n - 1) Max = std::max(Max, std::abs(in[i] - in[i + 1]));
		sum += Max;
		Max = 0;
		FOR(i, 0, n - 2) Max = std::max(Max, std::abs(in[i] - in[i + 1]));
		sum += Max;
		cout << sum << '\n';
	}




#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}