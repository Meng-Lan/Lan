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

int a, b, c, pos;

void go(int len, int step) {
	if (len <= 0) return;
	while (len--) printf(" %d", pos += step);
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int T; 
	while (scanf("%d", &T) != EOF) {
		while (T--) {
			scanf("%d%d%d", &a, &b, &c);
			assert(a >= 3); assert(b >= 3); assert(c >= 3);
			printf("0"); pos = 0;
			if (c % 3 == 0) {
				int len = c / 3;
				go(1, 2); go(len, 3);
				go(1, -1); go(len, -3);
				go(1, 2); go(len, 3);
				c = 0; b -= 2; a -= 1;
			}
			else if (c % 3 == 1) {
				int len = c / 3;
				go(len + 1, 3); go(1, -2);
				go(len, -3); go(1, 1);
				go(len, 3); go(1, 2);
				c = 0; a -= 1; b -= 2;
			}
			else if (c % 3 == 2) {
				int len = c / 3;
				go(len + 1, 3); go(1, -1);
				go(len, -3); go(1, -1);
				go(len + 1, 3); c = 0; a -= 2;
			}
			if (a > 1) go(a - 1, 1); a = 1;
			//if (b & 1) printf("\ntrue\n");
			if (b & 1) {
				int len = b / 2;
				go(len + 1, 2); go(1, -1); go(len, -2);
			}
			else {
				int len = b / 2;
				go(len, 2); go(1, 1); go(len, -2);
			}
			putchar('\n');
		}
	}

/*#ifdef MengLan
		printf("Time: %d\n", clock() - Beginning);
#endif // MengLan*/
		return 0;
	}