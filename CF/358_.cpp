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

const int maxn = 1005;
char s[maxn], t[maxn];
int n, m, k;

int get_equal(int &si, int &ti) {
	int ans = 0;
	while (si < n&&ti < m&&s[si++] == t[ti++]) ++ans;
	return ans;
}

int main() {
	scanf("%d%d%d", &n, &m, &k);
	scanf(" %s %s", s, t);
	int ans = 0, temp = 0;
	int L, R;
	for (int i = 0; i < n; ++i) {
		//if (n - i < ans) break;
		for (int j = 0; j < m; ++j) {
			//if (m - j < ans) break;
			if (s[i] == t[j]) {
				temp = 0, L = i, R = j;
				for (int l = 0; l < k; ++l)
					temp += get_equal(L, R);
				ans = max(ans, temp);
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}