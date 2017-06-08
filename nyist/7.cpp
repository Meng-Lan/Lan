#include<iostream>
#include<cstdio>
#include<algorithm>
const int max = 105;
int x[max], y[max];
int main() {
	int n;
	std::cin >> n;
	while (n--) {
		int m;
		std::cin >> m;
		for (int i = 0; i < m; i++)
			std::cin >> x[i] >> y[i];
		std::sort(x, x + m);
		std::sort(y, y + m);
		int sum = 0;
		for (int i = 0; i < m / 2; i++)
			sum += x[m - i - 1] - x[i] + y[m - i - 1] - y[i];
		std::cout << sum << std::endl;
	}
	return 0;
}