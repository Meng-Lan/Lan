#include<iostream>
#include<cstdio>
/*DP�������ã�sum������ʵ�ʣ����������м�ֵ����Ҫ�̶ȣ�ʵ��ֻ�м�ֵ*��Ҫ�̶�����Ϊ����ֵ��ֻ��Ҫsum����*/
int dp[30][30005], sum[30][30005];
int v[30], imp[30];
int max(int x, int y) {
	if (x >= y)
		return x;
	else
		return y;
}
int main() {
	int n, m;
	using std::cin;
	using std::cout;
	using std::endl;
	cin >> n >> m;
	for (int i = 0; i < m; i++)
		cin >> v[i] >> imp[i];
	for (int i = 0; i < m; i++) {
		for (int j = 1; j <= n; j++)
			if (j - v[i] < 0) {
				//dp[i + 1][j] = dp[i][j];
				sum[i + 1][j] = sum[i][j];
			}
			else {
				sum[i + 1][j] = max(sum[i][j], sum[i][j - v[i]] + v[i] * imp[i]);
			}
	}
	cout << sum[m][n] << endl;
	return 0;
}