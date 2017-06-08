#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<sstream>
#include<vector>
#include<map>
#include<set>
#include<utility>
#include<queue>
#include<stack>
#include<algorithm>
#include<cstdlib>
using namespace std;
typedef long long ll;
typedef pair<int, int> P;
#define FOR(i,len) for(int i=0;i<(len);++i)
#define For(i,len) for(int i=0;i<=(len);++i)
#define rep(i,init,len) for(int i=(init);i<(len);++i)
#define mp make_pair
ll Factorial(ll i) { return i > 1 ? i*Factorial(i - 1) : 1; }

ll Combination(ll n, ll r) {
	if (n - r < r) r = n - r;
	ll ansn = 1, ansr = 1;
	for (int i = n - r + 1; i <= n; ++i) ansn *= i;
	for (int j = 1; j <= r; ++j) ansr *= j;
	return ansn / ansr;
}

inline char get_char(int i) {
	return i >= 26 ? ('a' + (i - 26)) : 'A' + i;
}

int main() {
	int n;
	while (scanf("%d", &n) == 1 && n) {
		printf("2 %d %d\n", n, n);
		FOR(i, n) {
			FOR(j, n)
				putchar(get_char(j));
			putchar('\n');
		}
		putchar('\n');
		FOR(i, n) {
			FOR(j, n)
				putchar(get_char(i));
			putchar('\n');
		}
		putchar('\n');
	}
	return 0;
}