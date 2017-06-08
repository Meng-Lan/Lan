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

const int maxn = 15;
const int INF = 1e9;
int n, a, b, in[maxn], tmp[maxn];

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	scanf("%d%d%d", &n, &a, &b);
	FOR(i, 0, n) scanf("%d", in + i);
	int ans = 0;
	if (in[0] >= 0) {
		int cnt = (in[0] + 1) / b;
		if ((in[1] + 1) % b) ++cnt;
		ans += cnt;
		in[0] -= cnt*b; in[1] -= cnt*a; in[2] -= cnt*b;
	}
	if (in[n - 1] >= 0) {
		int &r = in[n - 1];
		int cnt = (r + 1) / b;
		if ((r + 1) % b) ++cnt;
		ans += cnt;
		r -= cnt*b; in[n - 2] -= cnt*a; in[n - 3] -= cnt*b;
	}
	int l = 1, r = n - 1;
	while (in[l] < 0 && l < r) ++l;
	while (in[r - 1]<0 && r>l) --r;
	int min = INF;
	int s = 1 << ((r - l) * 3);
	cout << s << '\n';
	FOR(i,0,s){
		memset(tmp, 0, sizeof(tmp));
		FOR(j,l,r){
			int cnt = s & 7;





#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}