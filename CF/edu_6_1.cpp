#include<iostream>
int lan(int x) {
	if (x >= 0)
		return x;
	else
		return -x;
}
int max(int x, int y) {
	if (x >= y)
		return x;
	else
		return y;
}
int main() {
	int x, x1, y, y1;
	std::cin >> x >> y >> x1 >> y1;
	int x2 = lan(x - x1);
	int y2 = lan(y - y1);
	int m = max(x2, y2);
	std::cout << m << std::endl;
	return 0;
}