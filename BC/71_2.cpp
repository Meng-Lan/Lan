#include<cstdio>
#include<cstring>
#include<iostream>
int main() {
	using std::cin;
	using std::cout;
	using std::endl;
	int t;
	cin >> t;
	while (t--) {
		long long n;
		cin >> n;
		long long ans = n;
		if (n == 3)
			;
		else
			ans += (n*(n - 1)*(n - 2)*(n - 3)) / 24;
		cout << ans << endl;
	}
	return 0;
}