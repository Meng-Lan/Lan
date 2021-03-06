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

const int maxn = 1005;
const int INF = 1e9;
int ans[maxn], in[maxn], n;

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	scanf("%d", &n);
	For(i, 1, n) ans[i] = INF;
	int len = -1;
	FOR(i, 0, 20) if ((n >> i) & 1) len = i;
	if (n == 2) len = 0;
	For(i, 0, len) {
		std::vector<int> out1, out2;
		For(j, 1, n) {
			if ((j >> i) & 1) out1.push_back(j);
			else out2.push_back(j);
		}
		cout << out1.size() << '\n';
		FOR(j, 0, out1.size()) printf("%d%c", out1[j], j == out1.size() - 1 ? '\n' : ' ');
		fflush(stdout);
		For(j, 1, n) scanf("%d", in + j);
		FOR(j, 0, out2.size()) ans[out2[j]] = std::min(ans[out2[j]], in[out2[j]]);

		cout << out2.size() << '\n';
		FOR(j, 0, out2.size()) printf("%d%c", out2[j], j == out2.size() - 1 ? '\n' : ' ');
		fflush(stdout);
		For(j, 1, n) scanf("%d", in + j);
		FOR(j, 0, out1.size()) ans[out1[j]] = std::min(ans[out1[j]], in[out1[j]]);
	}
	cout << "-1\n";
	For(i, 1, n) printf("%d%c", ans[i], i == n ? '\n' : ' ');
	fflush(stdout);


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}