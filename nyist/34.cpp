#include<iostream>
int main() {
	int a, b, c;
	std::cin >> a >> b >> c;
	int off = 0;
	for (int i = 0; i <= 105; i++)
		if (i % 3 == a&&i%5 == b && i%7 == c) {
			std::cout << i << std::endl;
			off = 1;
			break;
		}
	if (!off)
		std::cout << "No answer\n";
	return 0;
}