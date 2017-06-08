#include<iostream>
int main() {
	int n;
	using std::cin;
	using std::cout;
	using std::endl;
	cin >> n;
	char c;
	int x;
	for (int i = 0; i < n; i++) {
		cin >> c >> x;
		if (c == 'W')
			if (x == 1)
				cout << 'C' << 'H' << 2 * x + 2 << endl;
			else
				cout << 'C' << x << 'H' << 2 * x + 2 << endl;
		else if (c == 'X')
			cout << 'C' << x << 'H' << 2 * x << endl;
		else if (c == 'Q')
			cout << 'C' << x << 'H' << 2 * x - 2 << endl;
	}
	return 0;
}