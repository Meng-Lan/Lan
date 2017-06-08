#include<iostream>
#include<cstdio>
#define maxn 100
int num[maxn][maxn];
int main() {
	int n;
	using std::cin;
	using std::cout;
	using std::endl;
	cin >> n;
	int sum = 0, x = 0, y = n - 1;
	num[x][y] = ++sum;
	while (sum < n*n) {
		while (x + 1 < n&&!num[x + 1][y])
			num[++x][y] = ++sum;
		while (y - 1 >= 0 && !num[x][y - 1])
			num[x][--y] = ++sum;
		while (x - 1 >= 0 && !num[x - 1][y])
			num[--x][y] = ++sum;
		while (y + 1 < n&&!num[x][y + 1])
			num[x][++y] = ++sum;
		//cout << sum;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cout << num[i][j] << "\t";
		cout << endl;
	}
	return 0;
}