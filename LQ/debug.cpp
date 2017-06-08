#include<iostream>
#include<stdio.h>
int road[100][100];
int main() {
	int n;
	std::cin >> n;
	int a, b, c;
	for (int i = 0; i < n; i++) {
		std::cin >> a >> b;
		std::cin >> road[a][b];
	}
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++)
			std::cout << road[i][j] << " ";
		std::cout << std::endl;
	}
	return 0;
}