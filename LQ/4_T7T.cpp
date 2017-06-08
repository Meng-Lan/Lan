#include<iostream>
#include<cstring>
using namespace std;
int main() {
	int n;
	cin >> n;
	int max = 0;
	int temp = n;
	for (int i = 0; temp; i++) {
		temp >>= 1;
		max++;
	}
	temp = n;
	int tp = 0;
	for (int i = 0; temp; i++) {
		if (temp & 1)
			tp++;
		temp >>= 1;
	}
	temp = (1 << max) - n;
	int tp2 = 0;
	for (int i = 0; temp; i++) {
		if (temp & 1)
			tp2++;
		temp >>= 1;
	}
	if (max + tp2 < max + tp - 2)
		cout << max + tp2 << endl;
	else
		cout << max + tp - 2 << endl;
	return 0;
}