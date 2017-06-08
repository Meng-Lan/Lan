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

const int mod = 1000000007;
const int maxn = 2010;
const int maxp = 100;
ll prime[1000], primenum;
void PRIME(ll Max_Prime) {
	primenum = 0;
	prime[primenum++] = 2;
	for (ll i = 3; i <= Max_Prime; i += 2)
		for (ll j = 0; j<primenum; j++)
			if (i%prime[j] == 0)break;
			else if (prime[j]>sqrt((double)i) || j == primenum - 1)
			{
				prime[primenum++] = i;
				break;
			}
}

typedef ll Matrix[maxn][maxn];

int rank(Matrix A, int m, int n) {
	int i = 0, j = 0, k, r, u;
	while (i < m && j < n)
	{
		r = i;
		for (k = i; k < m; k++)
			if (A[k][j])
			{
				r = k; break;
			}
		if (A[r][j])
		{
			if (r != i)
				for (k = 0; k <= n; k++) std::swap(A[r][k], A[i][k]);
			for (u = i + 1; u < m; u++) if (A[u][j])
				for (k = i; k <= n; k++) A[u][k] ^= A[i][k];
			i++;
		}
		j++;
	}
	return i;
}

Matrix A;

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	PRIME(2000);
	int T; cin >> T;
	For(kase, 1, T) {
		int n, maxp = 0;
		long long x;
		cin >> n;
		memset(A, 0, sizeof A);
		for (int i = 0; i < n; i++)
		{
			cin >> x;
			for (int j = 0; j < primenum; j++)
				while (x % prime[j] == 0)
				{
					maxp = std::max(maxp, j);
					x /= prime[j];
					A[j][i] ^= 1;
				}
		}
		int r = rank(A, maxp + 1, n);
		ll ans = 1;
		FOR(i, 0, n - r) { ans *= 2; ans %= mod; }
		cout << "Case #" << kase << ":\n" << ans - 1 << "\n";
	}



#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}