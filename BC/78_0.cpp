#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int main() {
	int t;
	cin >> t;
	while (t--) {
		long long temp[4];
		for (int i = 0; i < 4; i++)
			cin >> temp[i];
		sort(temp, temp + 4);
		if (temp[0] == 0) {
			cout << "No\n";
			continue;
		}
		/*for (int i = 0; i < 4; i++)
			cout << temp[i] << endl;*/
		long long maxn = temp[3];
		int off = 1;
		for (int i = 0; i < 3; i++) {
			maxn -= temp[i];
			if (maxn < 0) {
				off = 0;
				cout << "Yes\n";
				break;
			}
		}
		if (off)
			cout << "No\n";
	}
	return 0;
}