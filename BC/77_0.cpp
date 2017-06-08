#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
using namespace std;
long long num[1005];
long long temp[1005];
int main() {
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		long long ans = 0;
		for (int i = 0; i < n; i++)
			scanf("%lld", num + i);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				ans ^= num[i];
			cout << ans << endl;
			temp[i] = ans;
		}
		ans = 0;
		for (int i = 0; i < n; i++)
			ans ^= temp[i];
		cout << ans << endl;
	}
	return 0;
}