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

const int maxn = 2010;
int n, m, in[maxn];
std::vector<int*> t[maxn];

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	cin >> n >> m;
	std::deque<int*> dq;
	FOR(i, 0, n) {
		cin >> in[i];
		if (in[i] > m) dq.push_back(&in[i]);
		else t[in[i]].push_back(&in[i]);
	}
	int j = n / m, cnt = 0;
	if(t[m].size()>j)
		for (int i = t[m].size() - 1; i >= j; --i) {
			dq.push_front(t[m][i]);
			t[m].pop_back();
		}
	int need = 0;
	For(i, 1, m) if (t[i].size() < j) need += j - t[i].size();
	if (dq.size() < need) {
		FOR(i, 1, m) {
			if (t[i].size() > j)
				for (int k = t[i].size() - 1; k >= j; --k) {
					dq.push_back(t[i][k]);
					if (dq.size() == need) break;
				}
			if (dq.size() == need) break;
		}
	}
	For(i, 1, m) FOR(k,t[i].size(),j) {
		//cout << k << ' ' << j << ' ' << t[i].size() << '\n';
		*(dq.back()) = i;
		t[i].push_back(dq.back());
		dq.pop_back();
		//cout << k << ' ' << j << ' ' << t[i].size() << '\n';
		++cnt;
	}
	while (!dq.empty()) {
		*(dq.back()) = 1;
		dq.pop_back();
		++cnt;
	}
	cout << j << ' ' << cnt << '\n';
	FOR(i, 0, n) {
		if (i) cout << ' ';
		cout << in[i];
	}
	cout << '\n';

#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}