#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
int F[65][3400], ans[3400], in[65][3][2];
using std::cin;
using std::cout;
using std::endl;
using std::max;
int main() {
	int n, m;
	cin >> n >> m;
	n /= 10;
	int v, p, q;
	memset(in, -1, sizeof(in));
	/*for (int i = 0; i < 65; i++)
		for (int j = 0; j < 3; j++)
			cout << in[i][j][0] << " " << in[i][j][1] << endl;*/
	for (int i = 1; i <= m; i++) {
		cin >> v >> p >> q;
		if (q == 0) {
			in[i][0][0] = v / 10;
			in[i][0][1] = p*v;
		}
		else
			for (int i = 1; i < 3; i++)
				if (in[q][i][0] == -1) {
					in[q][i][0] = v / 10;
					in[q][i][1] = p*v;
					break;
				}
	}
	for (int i = 1; i <= m; i++) {
		if (in[i][1][0] != -1)
			for (int k = 1; k < 3 && in[i][k][0] != -1; k++)
				for (int j = n - in[i][0][0]; j >= in[i][k][0]; j--)
					F[i][j] = max(F[i][j], F[i][j - in[i][k][0]] + in[i][k][1]);
	}
	for (int i = 1; i <= m; i++)
		if (in[i][0][0] != -1)
			for (int j = n; j >= in[i][0][0]; j--)
				if (in[i][1][0] != -1)
					for (int k = j; k >= in[i][0][0]; k--)
						ans[j] = max(ans[j], ans[j - k] + F[i][k - in[i][0][0]] + in[i][0][1]);
				else
					ans[j] = max(ans[j], ans[j - in[i][0][0]] + in[i][0][1]);
	/*cout << "cnt:" << cnt << endl;
	for (int i = 0; i <= cnt; i++) {
		for (int j = 0; j < 3; j++)
			cout << in[i][j][0] << "  " << in[i][j][1] << endl;
		for (int j = 0; j < n; j++)
			cout << F[i][j] << " ";
		cout << endl;
	}*/
	int max = 0;
	for (int i = 0; i <= n; i++)
		if (ans[i] > max)
			max = ans[i];
	cout << max << endl;
	return 0;
}