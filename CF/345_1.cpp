#include<iostream>
#include<cstdio>
using namespace std;
int main() {
	int a1, a2;
	cin >> a1 >> a2;
	if (a1 != a2)
		cout << (a1 + a2 ) / 2 + (a1 + a2 ) / 4 << endl;
	else
		cout << (a1 + a2 ) / 2 + (a1 + a2 - 1) / 4<< endl;
	return 0;
}