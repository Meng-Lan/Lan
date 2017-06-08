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

std::string A, B;
typedef std::pair<std::string, std::string> pss;
typedef std::pair<std::string, int> psi;
std::vector<pss> vs;
std::map<std::string, int> m1, m2;

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	cin >> A >> B;
	std::string s, t;
	while (cin >> s) { cin >> t; vs.push_back(mp(s, t)); }
	std::queue<psi> p, q; q.push(mp(A, 0)); p.push(mp(B, 0));
	m1[A] = 0; m2[B] = 0;
	int ans = -1, max1 = 0, max2 = 0; bool ok = false;
	while (!q.empty() && !p.empty()) {
		if (!q.empty()) {
			psi u = q.front(); q.pop();
			if (u.second + max2 >= 10) continue;
			FOR(i, 0, vs.size()) FOR(j, 0, u.first.size()) if (u.first.substr(j, vs[i].first.size()) == vs[i].first) {
				std::string tmp(u.first.begin(), u.first.begin() + j);
				tmp += vs[i].second; tmp += u.first.substr(j + vs[i].first.size());
				if (m2.find(tmp) != m2.end()) { ans = u.second + 1 + m2[tmp]; ok = true; break; }
				else m1[tmp] = u.second + 1;
				q.push(mp(tmp, u.second + 1)); max1 = std::max(max1, u.second + 1);
			}
		}
		if (!p.empty()) {
			psi u = p.front(); p.pop();
			if (u.second + max1 >= 10) continue;
			FOR(i, 0, vs.size()) FOR(j, 0, u.first.size()) if (u.first.substr(j, vs[i].second.size()) == vs[i].second) {
				std::string tmp(u.first.begin(), u.first.begin() + j);
				tmp += vs[i].first; tmp += u.first.substr(j + vs[i].second.size());
				if (m1.find(tmp) != m1.end()) { ans = u.second + 1 + m1[tmp]; ok = true; break; }
				else m2[tmp] = u.second + 1;
				p.push(mp(tmp, u.second + 1)); max2 = std::max(max2, u.second + 1);
			}
		}
	}
	if (ok) printf("%d\n", ans);
	else printf("NO ANSWER!\n");



#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}