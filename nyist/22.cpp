#include<cstdio>
#include<iostream>
const int max = 1005;
bool pri[max];
int main() {
	pri[0] = true;
	pri[1] = true;
	for (int i = 0; i < max; i++)
		if (!pri[i])
			for (int j = i + i; j < max; j += i)
				pri[j] = true;
	int m;
	
	std::cin >> m;
	while (m--) {
		int ans = 0, n, temp;
		std::cin >> n;
		while (n--) {
			std::cin >> temp;
			if (!pri[temp])
				ans += temp;
		}
		std::cout << ans << std::endl;
	}
	return 0;
}