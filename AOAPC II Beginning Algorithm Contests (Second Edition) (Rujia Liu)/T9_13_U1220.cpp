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

const int maxn = 210;
std::vector<int> sons[maxn];
std::map<std::string, int> Id;
std::vector<std::string> vs;
int d[maxn][2], f[maxn][2], n;

int ID(std::string &s) {
	if (Id.find(s) != Id.end()) return Id[s];
	vs.push_back(s);
	return Id[s] = vs.size() - 1;
}

int dp(int u, int z) {
	int &ans = d[u][z];
	if (ans >= 0) return ans;
	if (sons[u].empty()) return ans = z;
	ans = z;
	if (z) FOR(i, 0, sons[u].size()) { ans += dp(sons[u][i], 0); if (!f[sons[u][i]][0]) f[u][z] = 0; }
	else FOR(i, 0, sons[u].size()) {
		ans += std::max(dp(sons[u][i], 1), dp(sons[u][i], 0));
		if (dp(sons[u][i], 1) == dp(sons[u][i], 0)) f[u][z] = 0;
		if (dp(sons[u][i], 1) > dp(sons[u][i], 0) && !f[sons[u][i]][1]) f[u][z] = 0;
		else if (dp(sons[u][i], 1) < dp(sons[u][i], 0) && !f[sons[u][i]][0]) f[u][z] = 0;
	}
	return ans;
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	//std::ios::sync_with_stdio(false);
	while (cin >> n&&n) {
		vs.clear(); Id.clear(); For(i, 0, n) sons[i].clear();
		std::string s, t;
		cin >> s; ID(s);
		FOR(i, 0, n - 1) { cin >> s >> t; sons[ID(t)].push_back(ID(s)); }
		memset(d, -1, sizeof(d)); memset(f, 1, sizeof(f));
		printf("%d ", std::max(dp(0, 0), dp(0, 1)));
		if (dp(0, 0) == dp(0, 1)) printf("No\n");
		else if (dp(0, 0) > dp(0, 1) && !f[0][0]) printf("No\n");
		else if (dp(0, 0) < dp(0, 1) && !f[0][1]) printf("No\n");
		else printf("Yes\n");
	}

#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}