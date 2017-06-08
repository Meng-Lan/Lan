#include<iostream>
int num[50005];
int minx(int x, int y) {
	int min = num[x];
	for (int i = x + 1; i <= y; i++)
		if (num[i] < min)
			min = num[i];
	return min;
}
int maxx(int x, int y) {
	int max = num[x];
	for (int i = x + 1; i <= y; i++)
		if (num[i] > max)
			max = num[i];
	return max;
}
int main() {
	using std::cin;
	using std::cout;
	using std::endl;
	long long ans = 0;
	int n, temp;
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> num[i];
	int min, max;
	for (int i = 0; i < n; i++)
		for (int j = i; j < n; j++) {
			min = minx(j - i, j);
			max = maxx(j - i, j);
			if (max - min == i)
				ans++;
		}
	cout << ans << endl;
	return 0;
}