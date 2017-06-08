#include<iostream>
#include<cstdio>
using namespace std;
const int maxn = 5e5 + 5;
int num[maxn];
int main() {
	int n;
	while (cin >> n) {
		long long sum = 0, ans = 0;
		int left = 0, right = 0;
		for (int i = 0; i < n; i++) {
			scanf("%d", num + i);
			for (int j = left; num[j] < 0 && j < right; j++) {
				sum -= num[j];
				left++;
			}
			if (sum > ans)
				ans = sum;
			if (sum <= 0) {
				sum = num[i];
				left = right = i;
				continue;
			}
			sum += num[i];
			right = i;
		}
		if (sum > ans)
			ans = sum;
		for (int i = 0; i < left; i++) {
			sum += num[i];
			if (sum > ans)
				ans = sum;
			if (sum <= 0)
				break;
		}
		for (int j = left; num[j] < 0 && j < right; j++) {
			sum -= num[j];
			left++;
		}
		if (sum > ans)
			ans = sum;
		cout << left << "  " << right << endl;
		cout << ans << endl;
	}
	return 0;
}