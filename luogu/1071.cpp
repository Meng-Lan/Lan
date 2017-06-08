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

const int maxn = 105;
char s[maxn], s2[maxn], t[maxn], ans[maxn];
int vis[1 << 8];
std::map<char, char> m;

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	scanf(" %s %s %s", s, s2, t);
	int len = strlen(s);
	bool ok = true;
	FOR(i, 0, len) {
		if (m[s[i]] == '\0') {
			if (vis[s2[i]]) { ok = false; break; }
			m[s[i]] = s2[i];
			vis[s2[i]] = 1;
		}
		else if (m[s[i]] != s2[i]) {
			ok = false; break;
		}
	}
	if (m.size() != 26) ok = false;
	if (ok) {
		len = strlen(t);
		FOR(i, 0, len) putchar(m[t[i]]);
		putchar('\n');
	}
	else printf("Failed\n");



#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}