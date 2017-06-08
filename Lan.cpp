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

const int maxn = 500;
char s[maxn];
int sa[maxn], t[maxn], t2[maxn], c[maxn], n;

void build_sa(int m) {
	int i, *x = t, *y = t2;

	FOR(i, 0, m) c[i] = 0;
	FOR(i, 0, n) c[x[i] = s[i]]++;
	FOR(i, 1, m) c[i] += c[i - 1];
	for (int i = n - 1; i >= 0; --i) sa[--c[x[i]]] = i;
	cout << "SA:"; FOR(i, 0, n) cout << sa[i] << ' '; cout << '\n';
	cout << "X:"; FOR(i, 0, n) cout << x[i] << ' '; cout << '\n';

	for (int k = 1; k <= n; k <<= 1) {
		int p = 0;
		for (int i = n - k; i < n; ++i) y[p++] = i;
		FOR(i, 0, n) if (sa[i] >= k) y[p++] = sa[i] - k;
		cout << "Y:"; FOR(i, 0, n) cout << y[i] << ' '; cout << '\n';

		FOR(i, 0, m) c[i] = 0;
		FOR(i, 0, n) c[x[y[i]]]++;
		FOR(i, 1, m) c[i] += c[i - 1];
		for (int i = n - 1; i >= 0; --i) sa[--c[x[y[i]]]] = y[i];
		cout << "SA:"; FOR(i, 0, n) cout << sa[i] << ' '; cout << '\n';

		std::swap(x, y);
		p = 1; x[sa[0]] = 0;
		FOR(i, 1, n)
			x[sa[i]] = y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + k] == y[sa[i] + k] ? p - 1 : p++;
		cout << "X:"; FOR(i, 0, n) cout << x[i] << ' '; cout << '\n';
		if (p >= n) break;
		m = p;
	}
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int m = 0;
	cin >> s>>m;
	n = strlen(s);
	build_sa(m);


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}