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
typedef pair<ll, ll> P;
#define mp make_pair
int main() {
	int T, kase = 0;
	scanf("%d", &T);
	while (T--) {
		ll n, v1, s1, v2, s2;
		scanf("%lld%lld%lld%lld%lld", &n, &s1, &v1, &s2, &v2);
		vector<P> v;
		v.push_back(mp(n / s1, 1));
		v.push_back(mp(n / s2, 2));
		v.push_back(mp((s1 + s2) / 2, 3));
		sort(v.begin(), v.end());
		/*for (auto &t : v)
			cout << t.first << "  " << t.second << endl;*/
		int off = v[0].second;
		ll ans = 0, temp = 0, len;
		switch (off) {
		case 1:
			len = n / s1;
			for (int i = 0; i <= len; i++) {
				temp = i*v1 + ((n - i*s1) / s2)*v2;
				ans = max(ans, temp);
			}
			break;
		case 2:
			len = n / s2;
			for (int i = 0; i <= len; i++) {
				temp = i*v2 + ((n - i*s2) / s1)*v1;
				ans = max(ans, temp);
			}
			break;
		case 3:
			if (s2*v1 >= s1*v2) {
				for (int i = 0; i < s1; i++) {
					temp = i*v2 + ((n - i*s2) / s1)*v1;
					ans = max(ans, temp);
				}
			}
			else {
				for (int i = 0; i < s2; i++) {
					temp = i*v1 + ((n - i*s1) / s2)*v2;
					ans = max(ans, temp);
				}
			}
			break;
		}
		printf("Case #%d: %lld\n", ++kase, ans);
	}
	return 0;
}