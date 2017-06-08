#include<cstdio>
#include<iostream>
#include<algorithm>
const int maxn = 105;
int dp[maxn*10], c[maxn], w[maxn];
using std::cin;
using std::cout;
using std::endl;
using std::max;
int main() {
	int t, m;
	cin >> t >> m;
	for (int i = 0; i < m; i++)
		cin >> c[i] >> w[i];
	for (int i = 0; i < m; i++)
		for (int j = t; j >= c[i]; j--)
			dp[j] = max(dp[j], dp[j - c[i]] + w[i]);
	int ans = 0;
	for (int i = 0; i <= t; i++)
		if (dp[i] > ans)
			ans = dp[i];
	cout << ans << endl;
	return 0;
}