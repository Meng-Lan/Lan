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

const int maxn = 11000;
const int sigma_size = 26;
const int maxs = 150 + 10;;
std::map<std::string, int> ms;
struct AhoCorasickAutomata {
	int ch[maxn][sigma_size];
	int val[maxn];
	int f[maxn];
	int last[maxn];
	int cnt[maxs];
	int sz;

	void init() {
		sz = 1; val[0] = 0;
		memset(ch[0], 0, sizeof(ch[0]));
		memset(cnt, 0, sizeof(cnt));
		ms.clear();
	}

	int idx(char c) {
		return c - 'a';
	}

	void insert(char *P, int v) {
		int n = strlen(P);
		int u = 0;
		FOR(i, 0, n) {
			int c = idx(P[i]);
			if (!ch[u][c]) {
				ch[u][c] = sz;
				memset(ch[sz], 0, sizeof(ch[sz]));
				val[sz] = 0;
				++sz;
			}
			u = ch[u][c];
		}
		val[u] = v;
		ms[std::string(P)] = v;
	}

	void getFail() {
		std::queue<int> q;
		f[0] = 0;
		FOR(c, 0, sigma_size) {
			int u = ch[0][c];
			if (u) {
				f[u] = 0; q.push(u); last[u] = 0;
			}
		}

		while (!q.empty()) {
			int r = q.front(); q.pop();
			FOR(c, 0, sigma_size) {
				int u = ch[r][c];
				if (!u) {
					ch[r][c] = ch[f[r]][c]; continue;
				}
				q.push(u);
				int v = f[r];
				while (v && !ch[v][c]) v = f[v];
				f[u] = ch[v][c];
				last[u] = val[f[u]] ? f[u] : last[f[u]];
			}
		}
	}

	void count(int j) {
		if (j) {
			cnt[val[j]]++;
			count(last[j]);
		}
	}

	void find(char *T) {
		int n = strlen(T);
		int j = 0;
		FOR(i, 0, n) {
			int c = idx(T[i]);
			//while (j && !ch[j][c]) j = f[j];
			j = ch[j][c];
			if (val[j]) count(j);
			else if (last[j]) count(last[j]);
		}
	}
}ac;
char s[1000001], t[151][80];
int n;

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	while (scanf("%d", &n) == 1 && n) {
		ac.init();
		For(i, 1, n) {
			scanf("%s", t[i]);
			ac.insert(t[i], i);
		}
		ac.getFail();
		scanf("%s", s);
		ac.find(s);
		int best = -1;
		For(i, 1, n) best = std::max(best, ac.cnt[i]);
		printf("%d\n", best);
		For(i, 1, n) {
			if (ac.cnt[ms[std::string(t[i])]] == best) printf("%s\n", t[i]);
		}
	}

#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}