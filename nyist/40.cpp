#include<iostream>
inline int gcd(int a, int b) {
	return b ? gcd(b, a%b) : a;
}
int main() {
	int n;
	std::cin >> n;
	while (n--) {
		int a, b;
		std::cin >> a >> b;
		std::cout <<gcd(a,b)<<" "<< a*b / gcd(a, b) << std::endl;
	}
	return 0;
}