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

const int maxn = 1010;
char s[maxn];
int d[maxn], h[maxn][maxn];

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int T; scanf("%d", &T);
	while (T--) {
		scanf(" %s", s + 1);
		int len = strlen(s + 1);
		memset(h, 0, sizeof(h));
		For(i, 1, len) {
			h[i][i] = 1;
			int l = std::min(i-1, len - i);
			For(j, 1, l) if (s[i - j] == s[i + j]) h[i - j][i + j] = 1; else break;
			l = std::min(i, len - i);
			FOR(j, 0, l) if (s[i - j] == s[i + j + 1]) h[i - j][i + j + 1] = 1; else break;
		}
		d[0] = 0;
		For(i, 1, len) for (int j = i; j >= 1; --j) {
			if (j == i) d[j] = d[j - 1] + 1;
			else if (h[j][i]) d[i] = std::min(d[i], d[j - 1] + 1);
		}
		printf("%d\n", d[len]);
	}



#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}