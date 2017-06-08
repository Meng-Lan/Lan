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
	int m = sqrt(len + 0.5);
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

std::map<std::vector<int>, double> d;
char s[9][4][3];

double dp(std::vector<int> &cnt, int c) {
	if (c == 0) return 1;
	if (d.count(cnt) != 0) return d[cnt];
	double sum = 0;
	int tot = 0;
	FOR(i, 0, 9) if (cnt[i] > 0)
		FOR(j, i + 1, 9) if (cnt[j] > 0)
		if (s[i][cnt[i]-1][0] == s[j][cnt[j]-1][0]) {
			--cnt[i]; --cnt[j];
			sum += dp(cnt, c - 2);
			++cnt[i]; ++cnt[j]; ++tot;
		}
	if (tot == 0) return d[cnt] = 0;
	else return d[cnt] = sum / tot;
}

bool read_data() {
	FOR(i, 0, 9) FOR(j, 0, 4) if (scanf("%s", s[i][j]) != 1) return false;
	return true;
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	while (read_data()) {
		std::vector<int> cnt(9, 4);
		d.clear();
		printf("%.6f\n", dp(cnt, 36));
	}



#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}