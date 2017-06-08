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

const int maxn = 3e5 + 10;
const int maxnode = 4e5 + 10;
const int sigma_size = 26;
const int mod = 20071027;
int kase, n, d[maxn];
char s[maxn];
struct Trie {
	int ch[maxnode][sigma_size];
	int val[maxnode];
	int sz;
	Trie() {
		sz = 1;
		memset(ch[0], 0, sizeof(ch[0]));
	}
	int idx(char c) {
		return c - 'a';
	}

	void init() {
		sz = 1;
		memset(ch[0], 0, sizeof(ch[0]));
	}

	void insert(char *s, int v) {
		int u = 0, len = strlen(s);
		FOR(i, 0, len) {
			int c = idx(s[i]);
			if (!ch[u][c]) {
				memset(ch[sz], 0, sizeof(ch[sz]));
				val[sz] = 0;
				ch[u][c] = sz++;
			}
			u = ch[u][c];
		}
		val[u] = v;
	}

	ll query(char *s, int len, int i) {
		ll sum = 0;
		int u = 0;
		FOR(j, 0, len) {
			int c = idx(s[j]);
			if (ch[u][c]) {
				u = ch[u][c];
				if (val[u])
					sum += d[i + j + 1];
			}
			else break;
		}
		return sum;
	}
}trie;

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	while (scanf(" %s", s) == 1) {
		memset(d, 0, sizeof(d));
		trie.init();
		scanf("%d", &n);
		char str[105];
		FOR(i, 0, n) {
			scanf(" %s", str);
			trie.insert(str, 1);
		}
		int len = strlen(s); d[len] = 1;
		for (int i = len - 1; i >= 0; --i) {
			d[i] = trie.query(s + i, std::min(len - i, 100), i) % mod;
		}
		printf("Case %d: %d\n", ++kase, d[0]);
	}

#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}