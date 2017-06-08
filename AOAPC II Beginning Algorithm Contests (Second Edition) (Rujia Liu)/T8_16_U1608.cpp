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

const int maxn = 200000 + 5;
int in[maxn], n, L[maxn], R[maxn];
map<int, int> m;

bool query(int bgn, int end) {
	if (end - bgn < 1) return true;
	int l = bgn, r = end;
	while (l <= r) {
		if (l <= r) {
			if (L[l]<bgn&&R[l]>end)
				if (query(bgn, l - 1) && query(l + 1, end)) return true;
				else return false;
				//逻辑不好，写成 return query(bgn,l-1)&&query(l+1,end); 显然好很多
			else ++l;
		}
		if (l <= r) {
			if (L[r]<bgn&&R[r]>end)
				if (query(bgn, r - 1) && query(r + 1, end)) return true;
				else return false;
			else --r;
		}
	}
	return false;
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		FOR(i, n) scanf("%d", in + i);
		memset(L, -1, (n + 1)*sizeof(int));
		memset(R, 0x3f, (n + 1)*sizeof(int));
		m.clear();
		FOR(i, n)
			if (m.find(in[i]) != m.end()) {
				auto &t = m[in[i]];
				R[t] = i;
				L[i] = t;
				t = i;
			}
			else
				m[in[i]] = i;
		if (query(0, n - 1)) printf("non-boring\n");
		else printf("boring\n");
	}
	return 0;
}