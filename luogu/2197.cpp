#include<iostream>
#include<cstdio>
int main() {
	int n;
	using std::cin;
	using std::cout;
	using std::endl;
	cin >> n;
	double ans = 1.0, temp;
	while (n--) {
		cin >> temp;
		ans *= temp;
	}
	printf("%.6f\n", ans);
	return 0;
}