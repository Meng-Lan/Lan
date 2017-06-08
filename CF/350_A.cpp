#include<iostream>
using namespace std;
int main() {
	int n;
	cin >> n;
	int min, max;
	min = max = n / 7*2;
	int mod = n % 7;
	if (mod <= 2)
		max += mod;
	else
		max += 2;
	if (mod >= 5)
		min += mod - 5;
	cout << min << " " << max << endl;
	return 0;
}