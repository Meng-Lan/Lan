#include<iostream>
#include<cstring>
using namespace std;
int main() {
	int n;
	cin >> n;
	while (n--) {
		int m;
		cin >> m;
		int temp = m, t1 = 0, t2 = 0;
		for (; temp; t1++) {
			if (temp & 1)
				t2++;
			temp >>= 1;
		}
		cout << t1 + t2 - 2 << endl;
	}
	return 0;
}