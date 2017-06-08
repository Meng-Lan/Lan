#include<iostream>
#include<cstdio>
int num[10005];
inline void swap(int x, int y) {
	int temp = num[x];
	num[x] = num[y];
	num[y] = temp;
}
int main() {
	int n;
	using std::cin;
	using std::cout;
	using std::endl;
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> num[i];
	unsigned int ans = 0;
	while (n > 1) {
		int min = 0, minn = 1;
		if (num[min] > num[minn])
			swap(min, minn);
		for (int i = 2; i < n; i++)
			if (num[i] < num[min]) {
				swap(minn, min);
				swap(min, i);
			}
			else if (num[i] < num[minn])
				swap(minn, i);
		num[min] += num[minn];
		ans += num[min];
		swap(minn, n - 1);
		n--;
	}
	cout << ans << endl;
	return 0;
}