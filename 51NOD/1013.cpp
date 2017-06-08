#include<iostream>
#include<cstdio>
using namespace std;
typedef unsigned long long ull;
ull temp[100];
const ull MOD = 1000000007 * 2;
int main() {
	ull t = 3;
	temp[0] = 1;
	for (int i = 1; i < 64; i++) {
		temp[i] = t;
		t *= t;
		t %= MOD;
	}
	ull n, ans = 1;
	cin >> n;
	n += 1;
	for (int i = 1; n; i++) {
		if (n & 1)
			ans *= temp[i];
		n >>= 1;
		ans %= MOD;
	}
	cout << (ans - 1) / 2 << endl;
	return 0;
}