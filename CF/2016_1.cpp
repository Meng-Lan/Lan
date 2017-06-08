#include<iostream>
#include<cstdio>
#include<cstring>
int num[100];
int main() {
	int n;
	using std::cin;
	using std::cout;
	using std::endl;
	cin >> n;
	int cnt;
	for (cnt = 0; n; cnt++) {
		num[cnt] = n & 1;
		n=n >> 1;
	}
	int ok = 0;
	for (; cnt >= 0; cnt--)
		if (num[cnt]) {
			if (ok++)
				cout << " ";
			cout << cnt + 1;
		}
	cout << endl;
	return 0;
}