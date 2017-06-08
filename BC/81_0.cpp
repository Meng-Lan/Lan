#include<iostream>
#include<cstdio>
using namespace std;
int main() {
	long long op;
	int T;
	int n;
	cin >> T;
	int num[60];
	char *ans = "RGB";
	while (T--) {
		memset(num, 0, sizeof(num));
		cin >> n >> op;
		for (int i = n - 1; i >= 0; i--) {
			num[i] = op % 3;
			op /= 3;
		}
		for (int i = 0; i < n; i++)
			printf("%c", ans[num[i]]);
		putchar('\n');
	}
	return 0;
}