#include<iostream>
#include<cstdio>
int ai[105], dp[10005];
inline int max(int x, int y) {
	return x >= y ? x : y;
}
int main() {
	int n, m;
	using std::cin;
	using std::cout;
	using std::endl;
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		cin >> ai[i];
	int max = 0;
	for (int i = 0; i < n; i++) {
		for (int j = m; j >= 0; j--) {
			if (dp[j]) {
				dp[j + ai[i]] = dp[j] + dp[j + ai[i]];
				//dp[j]++;
			}
		}
		dp[ai[i]]++;
		/*if (max + ai[i] <= m)
			max += ai[i];
		for (int j = 0; j <= max; j++)
			cout << dp[j] << " ";
		cout << endl;*/
	}
	dp[0] = 1;
	cout << dp[m] << endl;
	return 0;
}