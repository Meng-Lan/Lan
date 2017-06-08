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

const int maxn = 110;
int p1, p2, p3;
char s[maxn];

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	scanf("%d%d%d %s", &p1, &p2, &p3, s);
	int len = strlen(s);
	FOR(i, 0, len) {
		if (s[i] != '-') putchar(s[i]);
		else {
			char bgn = s[i - 1], end = s[i + 1];
			if (!(isdigit(bgn) && isdigit(end) || islower(bgn) && islower(end))) { putchar(s[i]); continue; }
			if (bgn + 1 == end) { continue; }
			if (end <= bgn) { putchar('-'); continue; }
			if (p3 == 1) {
				if (isdigit(bgn) && p1 != 3) FOR(j, bgn + 1, end) FOR(k, 0, p2) putchar(j);
				else if (isalpha(bgn) && p1 == 1) FOR(j, tolower(bgn) + 1, tolower(end)) FOR(k, 0, p2) putchar(j);
				else if (isalpha(bgn) && p1 == 2) FOR(j, toupper(bgn) + 1, toupper(end)) FOR(k, 0, p2) putchar(j);
				else if(p1==3) FOR(j, bgn + 1, end) FOR(k, 0, p2) putchar('*');
			}
			else if (p3 == 2) {
				if (isdigit(bgn) && p1 != 3) for (int j = end - 1; j > bgn; --j) FOR(k, 0, p2) putchar(j);
				else if (isalpha(bgn) && p1 == 1) for (int j = tolower(end) - 1; j > tolower(bgn); --j) FOR(k, 0, p2) putchar(j);
				else if (isalpha(bgn) && p1 == 2) for (int j = toupper(end) - 1; j > toupper(bgn); --j) FOR(k, 0, p2) putchar(j);
				else if(p1==3) FOR(j, bgn + 1, end) FOR(k, 0, p2) putchar('*');
			}
		}
	}
	putchar('\n');

#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}