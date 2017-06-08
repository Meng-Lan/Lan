#include<iostream>
#include<cstdio>
#include<algorithm>
int main() {
	int n;
	using std::cin;
	using std::cout;
	using std::endl;
	cin >> n;
	long long min = 10000000000, ans = 0, temp;
	for (int i = 0; i < n; i++) {
		cin >> temp;
		if (temp < min&&(temp & 1))
			min = temp;
		ans += temp;
	}
	if (ans & 1) {
		ans -= min;
		cout << ans << endl;
	}
	else
		cout << ans << endl;
	return 0;
}