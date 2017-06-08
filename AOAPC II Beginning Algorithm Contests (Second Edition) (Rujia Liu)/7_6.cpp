#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<vector>
#include<map>
#include<set>
#include<utility>
#include<queue>
#include<stack>
#include<algorithm>
#include<cstdlib>
using namespace std;
typedef long long ll;
typedef pair<int, int> P;
const int maxn = 100;
ll ans[maxn], v[maxn];
ll maxd;
ll a, b;

ll gcd(ll a, ll b) {
	return (b>0) ? gcd(b, a%b) : a;
}

bool better(ll d) {
	for (ll i = d; i >= 0; i--)
		if (v[i] != ans[i])
			return ans[i] == -1 || v[i] < ans[i];
	return false;
}

ll get_first(ll aa, ll bb) {
	//cout << "get_first "<<aa<<" / "<<bb<<" = "<<((bb%aa) ? (bb / aa) + 1 : bb / aa) << endl;
	return (bb%aa) ? (bb / aa) + 1 : bb / aa;
}

bool dfs(ll d, ll from, ll aa, ll bb) {
	if (d == maxd) {
		if (bb%aa) return false;
		v[d] = bb / aa;
		if (better(d))
			memcpy(ans, v, sizeof(ll)*(d + 1));
		return true;
	}
	bool ok = false;
	from=max(from,get_first(aa, bb));
	for (ll i = from;; i++) {
		if (aa*i >= (maxd + 1 - d)*bb) break;
		v[d] = i;
		ll a2 = aa*i - bb;
		ll b2 = bb*i;
		ll g = gcd(a2, b2);
		if (dfs(d + 1, i + 1, a2 / g, b2 / g))
			ok = true;
	}
	return ok;
}

int main() {
	cin >> a >> b;
	bool ok = false;
	for (maxd = 1;; maxd++) {
		memset(ans, -1, sizeof(ans));
		if (dfs(0, get_first(a, b), a, b)) {
			ok = true;
			break;
		}
	}
	if (ok)
		for (int i = 0; i <= maxd; i++) {
			if (i)
				putchar(' ');
			cout << ans[i];
		}
	putchar('\n');
	return 0;
}