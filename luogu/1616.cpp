#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<iostream>
#include<algorithm>
const int maxn = 100010;
int dp[maxn], temp[maxn], c[maxn], w[maxn];
using std::cin;
using std::cout;
using std::endl;
using std::max;
int main() {
	int t, m, tc, tw;
	cin >> t >> m;
	for (int i = 0; i < m; i++) {
		scanf("%d%d", &tc, &tw);
		if (temp[tc] < tw)
			temp[tc] = tw;
	}
	int cnt = 0;
	for (int i = 0; i <= 10000; i++)
		if (temp[i]) {
			c[cnt] = i;
			w[cnt++] = temp[i];
		}
	for (int i = 0; i < cnt; i++)
		for (int j = c[i]; j <= t; j++)
			dp[j] = max(dp[j], dp[j - c[i]] + w[i]);
	cout << dp[t] << endl;
	return 0;
}