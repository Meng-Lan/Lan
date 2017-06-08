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
	for (ll i = n - r + 1; i <= n; ++i) ansn *= i;
	for (ll j = 1; j <= r; ++j) ansr *= j;
	return ansn / ansr;
}
ll gcd(ll a, ll b) { return b ? gcd(b, a%b) : a; }
ll lcm(ll a, ll b) { return a*b / gcd(a, b); }

const int maxn = 105;
char s[maxn];
int d[maxn][maxn], n;

bool match(int i, int j) {
	if (s[i] == '(') return s[j] == ')';
	if (s[i] == '[') return s[j] == ']';
	return false;
}

void dp() {
	FOR(i, 0, n) { d[i][i] = 1; d[i + 1][i] = 0; }
	for (int i = n - 2; i >= 0; --i)
		for (int j = i + 1; j < n; ++j) {
			d[i][j] = n;
			if (match(i, j)) d[i][j] = std::min(d[i][j], d[i + 1][j - 1]);
			for (int k = i; k < j; ++k) d[i][j] = std::min(d[i][j], d[i][k] + d[k + 1][j]);
		}
}

void print(int i, int j) {
	if (i > j) return;
	if (i == j) {
		if (s[i] == '(' || s[i] == ')') printf("()");
		else printf("[]");
		return;
	}
	int ans = d[i][j];
	if (match(i, j) && ans == d[i + 1][j - 1]) { putchar(s[i]); print(i + 1, j - 1); putchar(s[j]); return; }
	for (int k = i; k < j; ++k) if (ans == d[i][k] + d[k + 1][j]) {
		print(i, k); print(k + 1, j); return;
	}
}

void readline(char* S) {
	fgets(S, maxn, stdin);
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int T; readline(s);
	sscanf(s, "%d", &T);
	readline(s);
	while (T--) {
		readline(s);
		n = strlen(s) - 1;
		memset(d, -1, sizeof(d));
		dp();
		print(0, n - 1); putchar('\n'); if (T) putchar('\n'); 
		readline(s);
	}

#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}