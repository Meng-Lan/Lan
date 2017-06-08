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

std::map<std::string, int> m;
std::string s;
std::vector<P> v;
std::vector<std::string> vs;

void getv() {
	v.clear(); vs.clear();
	int l = 0, r = 0;
	int len = s.size();
	while (r < len) {
		if (islower(s[r])) ++r;
		else {
			v.push_back(P(l, r)); vs.push_back(s.substr(l, r - l));
			while (r < len) if (!islower(s[r])) ++r; else break;
			l = r;
		}
		//printf("r:%d\n", r);
	}
	v.push_back(P(l, r)); vs.push_back(s.substr(l, r - l));
}

bool sta(int l, int r) {
	while (l < r) if (s[l] == ' ') ++l; else return false;
	return true;
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	while (std::getline(cin,s)) {
		int l = 0, r = 0;
		m.clear();
		do {
			if (s == "####") break;
			getv();
			//FOR(i, 0, v.size()) { printf("%d %d\n", v[i].first, v[i].second); cout << vs[i] << '\n'; }
			FOR(i, 0, v.size() - 1) if (sta(v[i].second, v[i + 1].first)) {
				++m[vs[i] + " " + vs[i + 1]];
			}
		} while (getline(cin, s));
		std::pair<std::string, int> ans;
		bool ok = 0;
		for (auto &t : m) {
			if (!ok) {
				ans.first = t.first; ans.second = t.second; ok = 1;
			}
			else if (t.second > ans.second || t.second == ans.second&&t.first < ans.first) {
				ans.first = t.first; ans.second = t.second;
			}
		}
		cout << ans.first << ':' << ans.second << '\n';
	}

#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}