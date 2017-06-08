#include<iostream>
#include<cstdio>
int main() {
	int num;
	using std::cin;
	using std::cout;
	using std::endl;
	char str[10], str1[10];
	std::cin >> num >> str >> str1;
	if (str1[0] == 'm') {
		if (num == 31)
			cout << 7 << endl;
		else if (num == 30)
			cout << 11 << endl;
		else
			cout << 12 << endl;
	}
	else {
		if (num == 5 || num == 6)
			cout << 53 << endl;
		else
			cout << 52 << endl;
	}
	return 0;
}