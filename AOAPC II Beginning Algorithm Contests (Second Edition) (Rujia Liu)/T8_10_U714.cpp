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

const int maxn = 505;
int in[maxn],last[maxn];
int n,k;

ll find(ll x) {
	ll ans = 1, cnt = 0;
	FOR(i, n) if (cnt + in[i] <= x) cnt += in[i];
	else {
		++ans;
		cnt = in[i];
	}
	return ans;
}

void print(ll M) {
	ll done = 0;
	memset(last, 0, sizeof(last));
	int remain = k;
	for (int i = n - 1; i >= 0; --i) {
		if (done + in[i] > M || i + 1 < remain) {
			last[i] = 1; --remain; done = in[i];
		}
		else {
			done += in[i];
		}
	}
	FOR(i, n - 1) {
		printf("%d ", in[i]);
		if (last[i]) printf("/ ");
	}
	printf("%d\n", in[n - 1]);
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &k);
		int maxp = -1;
		ll tot = 0;
		FOR(i, n) {
			scanf("%d", in + i);
			tot += in[i];
			maxp = max(maxp, in[i]);
		}
		ll L = maxp, R = tot;
		while (L < R) {
			ll M = L + (R - L) / 2;
			if (find(M) <= k) R = M;
			else L = M + 1;
		}
		print(L);
	}
	return 0;
}