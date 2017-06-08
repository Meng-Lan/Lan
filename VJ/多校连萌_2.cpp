#include<iostream>
#include<algorithm>
int main() {
	int n, k, l, c, d, p, nl, np;
	std::cin >> n >> k >> l >> c >> d >> p >> nl >> np;
	int m = std::min(k*l / nl, c*d);
	m = std::min(m, p / np);
	std::cout << m / n << std::endl;
	return 0;
}