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

const int maxn = 55;
int n, k, d[maxn*maxn][maxn];
struct Lan {
	int x, y;
	Lan(int x = 0, int y = 0) :x(x), y(y) {}
	bool operator<(const Lan &t) { return y*t.x>t.y*x; }
	void input() { cin >> x >> y; }
}in[maxn];



int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int T; scanf("%d", &T);
	For(kase,1,T) {
		scanf("%d%d", &n, &k);
		FOR(i, 0, n) in[i].input();
		std::sort(in, in + n);
		memset(d, -1, sizeof(d));
		d[0][0] = 0;
		FOR(i, 0, n)for (int j = 2500; j >= 0; --j) for (int l = k - 1; l >= 0; --l)
			if (d[j][l] >= 0) d[j + in[i].y][l + 1] = std::max(d[j + in[i].y][l + 1], d[j][l] + (j * 2 + in[i].y)*in[i].x);
		int ans = 0;
		For(i, 0, 2500) ans = std::max(ans, d[i][k]);
		printf("Case %d: %d\n", kase, ans);
	}



#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}