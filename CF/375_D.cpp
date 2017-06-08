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

const int dx[] = { 1,0,-1,0 };
const int dy[] = { 0,1,0,-1 };
const int maxn = 55;
char s[maxn][maxn];
int n, m, k, idx, vis[maxn][maxn], cnt;
struct Info {
	int idx, cnt, x, y;
	Info(int idx = 0, int cnt = 0, int x = 0, int y = 0) :idx(idx), cnt(cnt), x(x), y(y) {}
	bool operator<(const Info &rhs) const {
		return cnt < rhs.cnt;
	}
};
std::vector<Info> info;

bool check(int x, int y) {
	return x >= 0 && x <= (n + 1) && y >= 0 && y <= (m + 1);
}

void dfs(int x, int y, int op) {
	if (op == 1 && s[x][y] == '.') {
		vis[x][y] = idx; ++cnt;
	}
	if (op == 2) s[x][y] = '*';
	FOR(i, 0, 4) {
		int tx = x + dx[i], ty = y + dy[i];
		if (op == 1 && check(tx, ty) && s[tx][ty] == '.' && !vis[tx][ty])
			dfs(tx, ty, op);
		else if (op == 2 && check(tx, ty) && s[tx][ty] == '.')
			dfs(tx, ty, op);
	}
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	memset(s, '.', sizeof(s));
	cin >> n >> m >> k;
	For(i, 1, n) scanf(" %s", s[i] + 1);
	idx = 1;
	For(i, 1, n) {
		if (s[i][1] == '.')dfs(i, 1, 1);
		if (s[i][m] == '.')dfs(i, m, 1);
	}
	For(i, 1, m) {
		if (s[1][i] == '.')dfs(1, i, 1);
		if (s[n][i] == '.')dfs(n, i, 1);
	}
	For(i, 1, n) For(j, 1, m) if (s[i][j] == '.' && !vis[i][j]) {
		++idx; cnt = 0; dfs(i, j, 1);
		info.push_back(Info(idx, cnt, i, j));
	}
	//For(i, 0, n) { For(j, 0, m) printf("%2d", vis[i][j]); putchar('\n'); }
	std::sort(info.begin(), info.end());
	int ans = 0;
	FOR(i, 0, k) info.pop_back();
	for (auto &t : info) {
		ans += t.cnt;
		dfs(t.x, t.y, 2);
	}
	cout << ans << '\n';
	For(i, 1, n) printf("%s\n", s[i] + 1);


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}