#include<iostream>
#include<cstdio>
#include<cctype>
#include<cstring>
using namespace std;
int main() {
	unsigned long long a = 1, b = 2, temp=0, aa, bb;
	cout << ~temp << endl;
	for (int i = 0; i < 88; i++) {
		a += b;
		temp = a;
		a = b;
		b = temp;
		cout << a << "  " << b << endl;
		aa = a;
		bb = b;
		for (int i = 0; i < 102; i++) {
			cout << aa / bb;
			aa %= bb;
			aa *= 10;
		}
		putchar('\n');
	}
	return 0;
}