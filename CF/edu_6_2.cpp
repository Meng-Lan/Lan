#include<iostream>
int main() {
	int a, b;
	std::cin >> a >> b;
	int num[10] = { 6,2,5,5,4,5,6,3,7,6 };
	int sum = 0;
	int temp;
	for (int i = a; i <= b; i++) {
		temp = i;
		while (temp) {
			sum += num[temp % 10];
			temp /= 10;
		}
	}
	std::cout << sum << std::endl;
	return 0;
}