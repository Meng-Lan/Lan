#include<iostream>
using namespace std;
typedef long long ll;
int num[100];
ll c(ll n, ll m) {
	memset(num, 0, sizeof(num));
	if (m == 0)
		return 1;
	ll temp = 1, temp2 = 1;;
	if (m > n - m)
		m = n - m;
	for (int i = 0; i < m; i++) {
		temp *= (n - i);
		for (int j = 1; j <= m; j++)
			if (temp%j == 0 && !num[j]) {
				temp /= j;
				num[j] = 1;
			}
	}
	for (int i = 0; i < m; i++)
		if (!num[m - i])
			temp2 *= (m - i);
	return temp / temp2;
}
int main() {
	ll ans = 0;
	cout << c(6,3) << endl;
	for (int i = 20; i <= 39; i += 2) {
		ans += c(i, 39 % i);
		cout << "C(" << i << "," << 39 % i << ")=" << c(i, 39 % i) << endl;
	}
	cout << ans << endl;
	return 0;
}