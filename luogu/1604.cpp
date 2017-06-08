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

const int maxn = 2010;
char s[2][maxn], ans[maxn];
int n, num[256];

char i_c(int i) {
	return i >= 10 ? 'A' + i - 10 : '0' + i;
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan


	//FOR(i, 0, 36) printf("%c ", i_c(i));
	For(i, 0, 9) num['0' + i] = i;
	FOR(i, 0, 26) num['A' + i] = i + 10;
	scanf("%d %s %s", &n, s[0], s[1]);
	int len1 = strlen(s[0]), len2 = strlen(s[1]);
	int len = std::max(len1, len2);
	if (len1 < len2) {
		std::swap(s[0], s[1]);
		std::swap(len1, len2);
	}
	//cout << s[0] << '\n' << s[1] << endl;
	bool sta = false;
	int cnt = 0;
	for (int i = 1; i <= len1;++i) {
		int t = num[s[0][len1 - i]];
		if (len2 - i >= 0) t += num[s[1][len2 - i]];
		cnt += t;
		ans[len--] = i_c(cnt%n);
		cnt /= n;
		if (cnt) sta = true;
		else sta = false;
	}
	if (sta) {
		ans[len] = i_c(cnt);
		printf("%s\n", ans);
	}
	else printf("%s\n", ans + 1);


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}