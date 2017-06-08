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
#define mp make_pair
int main() {
	int T;
	scanf("%d", &T);
	int a, b, d, n;
	while (T--) {
		scanf("%d%d%d%d", &a, &b, &d, &n);
		int len = min(n, 5);
		int t = 0;
		for (int i = 0; i < len; i++)
			t = t * 10 + a;
		int tmp = t*b;
		//cout << tmp << endl;
		vector<int> num;
		num.clear();
		for (int i = 0; tmp; i++) {
			num.push_back(tmp % 10);
			tmp /= 10;
		}
		int ans = 0;
		if (d == num[0])
			ans++;
		if ((a*b >= 10 && n >= 2 || n >= 3) && num[1] == d)
			ans++;
		if ((n >= 2 || a*b >= 10) && d == num[num.size() - 1])
			ans++;
		if ((n >= 4 || a*b >= 10 && n >= 3) && num[2] == d)
			ans += (n + (num.size() - len)) - 3;
		printf("%d\n", ans);
	}
	return 0;
}