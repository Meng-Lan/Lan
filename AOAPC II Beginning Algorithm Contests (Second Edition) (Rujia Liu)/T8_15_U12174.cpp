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

const int maxn = 100000 + 5;
int in[3*maxn], ok[2*maxn], cnt[maxn];

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		int s, n;
		scanf("%d%d", &s, &n);
		fill(in, in + 2 * s + n + 1, -1);
		FOR(i, n) scanf("%d", in + i + s);
		//FOR(i, n) printf("%d ", in[i + s]); putchar('\n');
		fill(ok, ok + s + n + 1, 0);
		fill(cnt, cnt + s + n + 1, 0);
		int tot = 0;
		for (int i = 0; i < s + n + 1; ++i) {
			if (tot == s) ok[i] = 1;
			if (i < s&&tot == i) ok[i] = 1;
			if (i > n&&tot == s + n - i) ok[i] = 1;
			if (i == s + n) break;
			if (in[i] != -1 && --cnt[in[i]] == 0) --tot;
			if (in[i + s] != -1 && cnt[in[i + s]]++ == 0) ++tot;
		}
		int ans = 0;
		FOR(i, s) {
			int valid = 1;
			for (int j = i; j < s + n + 1; j += s)
				if (!ok[j]) valid = 0;
			if (valid) ++ans;
		}
		if (ans == n + 1) ans = s;
		printf("%d\n", ans);
	}
	return 0;
}