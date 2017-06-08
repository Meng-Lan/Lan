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

const int maxn = 1005;
struct Lan {
	int v, k, c, l;
	bool operator<(const Lan &t)const { return v < t.v; }
}in[maxn];
int n, s[maxn], d[maxn];

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	while (scanf("%d", &n) == 1 && n) {
		For(i, 1, n) scanf("%d%d%d%d", &in[i].v, &in[i].k, &in[i].c, &in[i].l);
		std::sort(in + 1, in + n + 1);
		s[0] = 0; For(i, 1, n) s[i] = s[i - 1] + in[i].l;
		For(i, 1, n) {
			d[i] = in[i].c*(s[i] - s[0]) + in[i].k;
			FOR(j, 1, i) d[i] = std::min(d[i], d[j] + in[i].c*(s[i] - s[j]) + in[i].k);
		}
		printf("%d\n", d[n]);
	}


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}