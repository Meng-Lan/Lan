#include<iostream>
#include<cstdio>
int main() {
	int n;
	std::cin >> n;
	int sum = 0;
	sum += (n / 5);
	if (n % 5)
		sum++;
	std::cout << sum << std::endl;
	return 0;
}