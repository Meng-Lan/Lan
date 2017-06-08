#include<cstdio>
#include<iostream>
#include<cstring>
const int maxn = 91;
long long dp[maxn];
int main() {
	using std::cin;
	using std::cout;
	using std::endl;
	dp[0] = 1;
	dp[1] = 2;
	for (int i = 2; i < maxn; i++) 
		dp[i] = dp[i - 1] + dp[i - 2];
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		int ans = 0;
		int i = 1;
		for (; n - dp[i] > 0; i++)
			n -= dp[i];
		cout << i << endl;
	}
	return 0;
}