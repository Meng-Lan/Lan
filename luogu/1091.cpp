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
ll lcm(ll a, ll b) { return a*b / gcd(a, b); }

std::vector<int> in, d1, d2;
int n;

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	scanf("%d", &n);
	int t;
	FOR(i, 0, n) { scanf("%d", &t); in.push_back(t); }
	d1.resize(in.size()); d2.resize(in.size(), -1);
	FOR(i, 0, n) { d1[i] = 1; FOR(j, 0, i) if(in[i]>in[j]) d1[i] = std::max(d1[i], d1[j] + 1); }
	for (int i = n - 1; i >= 0; --i) { d2[i] = 1; for (int j = n - 1; j > i; --j) if (in[j] < in[i]) d2[i] = std::max(d2[i], d2[j] + 1); }
	int ans = 0;
	FOR(i, 0, n) ans = std::max(ans, d1[i] + d2[i] - 1);
	printf("%d\n", n - ans);


#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}