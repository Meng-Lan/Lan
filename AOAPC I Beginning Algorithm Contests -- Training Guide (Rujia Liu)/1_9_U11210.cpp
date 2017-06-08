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
std::vector<int> Eratosthenes(const int len, int *vis) {
	memset(vis, 0, sizeof(int)*len);
	std::vector<int> prime;
	int m = (int)sqrt(len + 0.5);
	For(i, 2, m) if (!vis[i]) for (int j = i*i; j < len; j += i) vis[j] = 1;
	FOR(i, 2, len) if (!vis[i]) prime.push_back(i);
	return prime;
}
void phi_table(int n, int *phi) {
	For(i, 2, n) phi[i] = 0;
	phi[1] = 1;
	For(i, 2, n) if (!phi[i])
		for (int j = i; j <= n; j += i) {
			if (!phi[j]) phi[j] = j;
			phi[j] = phi[j] / i*(i - 1);
		}
}

const char *mahjong[] = {
	"1T","2T","3T","4T","5T","6T","7T","8T","9T",
	"1S","2S","3S","4S","5S","6S","7S","8S","9S",
	"1W","2W","3W","4W","5W","6W","7W","8W","9W",
	"DONG","NAN","XI","BEI","ZHONG","FA","BAI" };
const int maxn = 10;
char s[maxn];
int c[34];


int NO(char *s) {
	FOR(i, 0, 34) if (strcmp(mahjong[i], s) == 0) return i;
	return -1;
}

bool search(int dep) {
	FOR(i,0,34)
		if (c[i] >= 3) {
			if (dep == 3) return true;
			c[i] -= 3;
			if (search(dep + 1)) return true;
			c[i] += 3;
		}
	FOR(i, 0, 27) if (i % 9 <= 6 && c[i] >= 1 && c[i + 1] >= 1 && c[i + 2] >= 1) {
		if (dep == 3) return true;
		--c[i]; --c[i + 1]; --c[i + 2];
		if (search(dep + 1)) return true;
		++c[i]; ++c[i + 1]; ++c[i + 2];
	}
	return false;
}

bool check() {
	FOR(i, 0, 34) {
		if (c[i] >= 2) {
			c[i] -= 2;
			if (search(0)) return true;
			c[i] += 2;
		}
	}
	return false;
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int kase = 0;
	bool ok;
	int mj[14];
	while (scanf(" %s", s) == 1) {
		if (s[0] == '0') break;
		printf("Case %d:", ++kase);
		mj[0] = NO(s);
		FOR(i, 1, 13) {
			scanf(" %s", s);
			mj[i] = NO(s);
		}
		ok = false;
		FOR(i, 0, 34) {
			memset(c, 0, sizeof(c));
			FOR(i, 0, 13) ++c[mj[i]];
			if (c[i] >= 4) continue;
			++c[i];
			if (check()) {
				ok = true;
				printf(" %s", mahjong[i]);
			}
			--c[i];
		}
		if (!ok) printf(" Not ready");
		putchar('\n');
	}



#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}