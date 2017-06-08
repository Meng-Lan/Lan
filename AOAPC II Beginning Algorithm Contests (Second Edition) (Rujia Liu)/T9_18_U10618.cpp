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

const int maxn = 80;
const char footch[] = ".LR";
enum Lan { UP, LEFT, RIGHT, DOWN };
char in[maxn], pos[1 << 8];
int n, d[maxn][4][4][3];
int action[maxn][4][4][3];

int energy(int a, int ta) {
	if (a == ta) return 3;
	if (a + ta == 3) return 7;
	return 5;
}

int energy(int i, int a, int b, int s, int f, int t, int &ta, int &tb) {
	ta = a, tb = b;
	if (f == 1) ta = t;
	else if(f==2) tb = t;
	if (ta == tb) return -1;
	if (ta == RIGHT&&tb == LEFT) return -1;
	if (a == RIGHT&&tb != b) return -1;
	if (b == LEFT&&ta != a) return -1;

	int e;
	if (f == 0) e = 0;
	else if (f != s) e = 1;
	else {
		if (f == 1) e = energy(a, ta);
		else e = energy(b, tb);
	}
	return e;
}

void updata(int i, int a, int b, int s, int f, int t) {
	int ta, tb;
	int e = energy(i, a, b, s, f, t, ta, tb);
	if (e < 0) return;
	int cost = d[i + 1][ta][tb][f] + e;
	int &ans = d[i][a][b][s];
	if (cost < ans) {
		ans = cost;
		action[i][a][b][s] = f * 4 + t;
	}
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	pos['U'] = 0; pos['L'] = 1; pos['R'] = 2; pos['D'] = 3;
	while (scanf(" %s", in) == 1 && in[0] != '#') {
		n = strlen(in);
		memset(d, 0, sizeof(d));
		for (int i = n - 1; i >= 0; --i)
			for (int a = 0; a < 4; ++a)
				for (int b = 0; b < 4; ++b) if (a != b)
					for (int s = 0; s < 3; ++s) {
						d[i][a][b][s] = 10 * n;
						if (in[i] == '.') {
							updata(i, a, b, s, 0, 0);
							for (int t = 0; t < 4; ++t) {
								updata(i, a, b, s, 1, t);
								updata(i, a, b, s, 2, t);
							}
						}
						else {
							updata(i, a, b, s, 1, pos[in[i]]);
							updata(i, a, b, s, 2, pos[in[i]]);
						}
					}
		int a = LEFT, b = RIGHT, s = 0;
		for (int i = 0; i < n; ++i) {
			int f = action[i][a][b][s] / 4;
			int t = action[i][a][b][s] % 4;
			printf("%c", footch[f]);
			s = f;
			if (f == 1) a = t;
			else if (f == 2) b = t;
		}
		putchar('\n');
	}

#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}