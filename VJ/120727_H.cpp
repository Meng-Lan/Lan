#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<sstream>
#include<fstream>
#include<vector>
#include<list>
#include<forward_list>
#include<deque>
#include<stack>
#include<queue>
#include<map>
#include<set>
#include<cmath>
#include<utility>
#include<numeric>
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

const int maxn = 100010;
int room[maxn], tmp[maxn];

int find(int x) {
	return room[x] = (room[x] == x ? x : find(room[x]));
}

bool merge(int x, int y) {
	tmp[x] = tmp[y] = 1;
	int fx = find(x), fy = find(y);
	if (fx == fy) return false;
	else {
		room[fx] = fy;
		return true;
	}
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int u, v;
	while (scanf("%d%d", &u, &v) == 2 && u != -1 && v != -1) {
		if (u == 0 && v == 0) {
			printf("Yes\n"); continue;
		}
		FOR(i, 0, maxn) room[i] = i; memset(tmp, 0, sizeof(tmp));
		int t = u;
		merge(u, v);
		bool sta = true;
		while (scanf("%d%d", &u, &v) == 2 && u&&v) {
			if (!merge(u, v)) sta = false;
		}
		t = find(t);
		FOR(i, 0, maxn) if (tmp[i] && find(i) != t) sta = false;
		if (sta) printf("Yes\n");
		else printf("No\n");
	}

#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}