#include<iostream>
int main() {
	int s;
	std::cin >> s;
	while (s--) {
		int n, m;
		std::cin >> n >> m;
		int ans = 0;
		for (int i = 1; i <= n; i++) {
			int temp = i;
			while (temp%m == 0) {
				temp /= m;
				ans++;
			}
		}
		std::cout << ans << std::endl;
	}
	return 0;
}