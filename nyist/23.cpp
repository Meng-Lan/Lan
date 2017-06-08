#include<iostream>
int main() {
	int n;
	std::cin >> n;
	while (n--) {
		int N, M;
		std::cin >> N >> M;
		if (N % (M + 1))
			std::cout << "Win\n";
		else
			std::cout << "Lose\n";
	}
	return 0;
}