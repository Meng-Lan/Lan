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

const int maxn = 20;
const int maxm = 105;
int n, m, edge[maxn][2], light, cnt[maxn], top = -1;
std::string in[maxn];

int d[maxn][2], vis[maxn][2];

int dp(int b, int lr) {
	if (b == top) {
		int tmp;
		if (!lr) tmp= edge[b][0];
		else tmp= m + 1 - edge[b][1];
		//printf("b:%d lr:%d top:%d\n", b, lr,tmp);
		return tmp;
	}
	if (vis[b][lr]) return d[b][lr]; vis[b][lr] = 1;
	int &ans = d[b][lr];
	if (!lr) {
		ans = std::min(dp(b - 1, 0) + edge[b][0] * 2 + 1, dp(b - 1, 1) + m + 2);
	}
	else {
		ans = std::min(dp(b - 1, 0) + m + 2, dp(b - 1, 1) + (m + 1 - edge[b][1]) * 2 + 1);
	}
	//printf("b:%d lr:%d ans:%d\n", b, lr, ans);
	return ans;
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	scanf("%d%d", &n, &m);
	FOR(i,0,n) cin >> in[i];
	FOR(i, 0, n) for (auto &t : in[i]) if (t == '1') { ++light; ++cnt[i]; }
	if (!light) {
		puts("0"); return 0;
	}
	FOR(i, 0, n) {
		int l = maxm, r = 0;
		FOR(j, 0, in[i].size()) if (in[i][j] == '1') {
			l = std::min(j, l); r = std::max(r, j);
		}
		if (cnt[i]) {
			edge[i][0] = r; edge[i][1] = l;
		}
		else {
			edge[i][0] = 0; edge[i][1] = m + 1;
		}
	}
	FOR(i,0,n) if (cnt[i]) { top = i; break; }
	//FOR(i, 0, n) printf("#%d cnt:%d\n", i, cnt[i]);
	//FOR(i, 0, n) printf("#%d L:%d R:%d\n", i, edge[i][0], edge[i][1]);
	cout << dp(n - 1, 0) << endl;


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}