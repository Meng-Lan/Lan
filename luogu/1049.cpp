#include<cstdio>
#include<iostream>
#include<algorithm>
const int maxn = 20005;
int dp[maxn], c[35];
using std::cin;
using std::cout;
using std::endl;
using std::max;
int main() {
	int v, n;
	cin >> v >> n;
	for (int i = 0; i < n; i++)
		cin >> c[i];
	for (int i = 0; i < n; i++)
		for (int j = v; j >= c[i]; j--)
			dp[j] = max(dp[j], dp[j - c[i]] + c[i]);
	/*for (int i = 0; i <= v; i++)
		cout << dp[i] << endl;*/
	cout << v - dp[v] << endl;
	return 0;
}