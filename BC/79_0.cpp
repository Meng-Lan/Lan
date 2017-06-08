#include<iostream>
#include<cstdio>
#include<string>
#include<set>
#include<vector>
#include<map>
#include<utility>
using namespace std;
typedef pair<int, int> P;
int main() {
	int T;
	cin >> T;
	while (T--) {
		int n, m;
		cin >> n>>m;
		int nn = ((n - 2) * 180) / n;
		int mm = ((m - 2) * 180) / n;
		int off = false;
		//cout << nn << "  " << mm << endl;
		for (int i = 0; i*nn <= 360; i++)
			if (((360 - i*nn) % mm) == 0) {
				//cout << i << endl;
				cout << "Yes\n";
				off = true;
				break;
			}
		if (!off)
			cout << "No\n";
	}
	return 0;
}