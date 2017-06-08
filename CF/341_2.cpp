#include<iostream>
#include<cstdio>
int z[2005], f[2005];
int main() {
	using std::cin;
	using std::cout;
	using std::endl;
	int n;
	cin >> n;
	int x, y;
	int *p = &z[1002];
	int ans = 0;
	for (int i = 0; i < n; i++) {
		cin >> x >> y;
		p[x - y]++;
		f[x + y]++;
	}
	for (int i = 0; i < 2005; i++) {
		if (z[i] > 1) {
			ans += (z[i] *( z[i] - 1)) / 2;
			//cout << ans << "--" << endl;
		}
		if (f[i] > 1) {
			ans += (f[i] * (f[i] - 1)) / 2;
			//cout << ans << "--" << endl;
		}
	}
	cout << ans << endl;
	return 0;
}