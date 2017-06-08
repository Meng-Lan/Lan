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

typedef std::pair<std::string, int> psi;
const int maxn = 22;
std::vector<std::string> vs;
P G[maxn][maxn];
int n, vis[maxn], d[maxn];
char start;

int dfs(int i, int bgn) {
	int ans = 0;
	bool find = false;
	FOR(j, 0, n) if (G[i][j].first&&vis[j] < 2 && vs[j].size() - bgn - G[i][j].second>0) {
		++vis[j];
		ans = std::max(ans, dfs(j, G[i][j].second));
		find = true;
		--vis[j];
	}
	if (find) return ans + vs[i].size() - bgn;
	else return vs[i].size() - bgn;
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	std::string s;
	scanf("%d", &n);
	FOR(i, 0, n) { cin >> s; vs.push_back(s); }scanf(" %c", &start);
	FOR(i, 0, n) FOR(j, 0, n) {
		for (int k = vs[i].size() - 1; k > 0; --k) if (vs[i][k] == vs[j][0] && vs[i].size() - k < vs[j].size()) {
			int ok = true;
			for (int l = 0; l < vs[i].size() - k; ++l) if (vs[i][k + l] != vs[j][l]) { ok = false; break; }
			if (ok) { G[i][j] = mp(vs[j].size() - vs[i].size() + k, vs[i].size() - k); break; }
		}
	}
	//FOR(i, 0, n) FOR(j, 0, n) if(G[i][j].first) printf("I:%d J:%d Len:%d Start:%d\n",i,j, G[i][j].first, G[i][j].second);
	int ans = 0;
	FOR(i, 0, n) if (vs[i][0] == start) {
		++vis[i]; ans = std::max(ans, dfs(i, 0)); --vis[i];
	}
	printf("%d\n", ans);


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}