#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<sstream>
#include<vector>
#include<map>
#include<set>
#include<utility>
#include<queue>
#include<stack>
#include<algorithm>
#include<cmath>
#include<functional>
#include<cstdlib>
using namespace std;
typedef long long ll;
typedef pair<int, int> P;
#define FOR(i,len) for(int i=0;i<(len);++i)
#define For(i,len) for(int i=0;i<=(len);++i)
#define rep(i,init,len) for(int i=(init);i<(len);++i)
#define mp make_pair
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

const int maxn = 1024 + 5;
char s[maxn][maxn];

int main() {
	int n;
	while (scanf("%d", &n) == 1 && n) {
		for (int i = 1; i <= n; ++i) scanf(" %s", s[i] + 1);
		vector<int> win, lose;
		for (int i = 2; i <= n; ++i) {
			if (s[1][i] == '1') win.push_back(i);
			else lose.push_back(i);
		}
		int nt = n;
		while (nt > 1) {
			vector<int> win2, lose2, Final;
			for (auto &i : lose) {
				bool ok = false;
				for (auto &j : win)
					if (j > 0 && s[j][i]=='1') {
						win2.push_back(j);
						printf("%d %d\n", i, j);
						j = 0;
						ok = true;
						break;
					}
				if (!ok) Final.push_back(i);
			}

			bool first = false;
			for (auto &t : win) {
				if (t > 0)
					if (!first) {
						printf("1 %d\n", t);
						first = true;
					}
					else Final.push_back(t);
			}

			for (int i = 0; i < Final.size(); i += 2) {
				int j = Final[i], k = Final[i + 1];
				printf("%d %d\n", j, k);
				int keep = s[j][k] == '1' ? j : k;
				if (s[1][keep] == '1') win2.push_back(keep);
				else lose2.push_back(keep);
			}
			win = win2;
			lose = lose2;
			nt >>= 1;
		}
	}
	return 0;
}