#include<iostream>
#include<cstdio>
#include<algorithm>
#include<map>
#include<vector>
#include<string>
#include<set>
using namespace std;
int main() {
	int T;
	cin >> T;
	while (T--) {
		int n;
		cin >> n;
		vector<int> temp,temp2,zero;
		temp.resize(n);
		zero.resize(n);
		for (int i = 0; i < n; i++)
			zero[i] = 0;
		set<vector<int>> sv;
		for (int i = 0; i < n; i++) {
			cin >> temp[i];
		}
		sv.insert(temp);
		temp2 = temp;
		for (int t=0;t<1000;t++) {
			for (int i = 0; i < n; i++)
				temp2[i] = abs(temp[i%n] - temp[(i + 1) % n]);
			if (temp2 == zero) {
				cout << "ZERO\n";
				break;
			}
			else if (sv.count(temp2)) {
				cout << "LOOP\n";
				break;
			}
			sv.insert(temp2);
			temp = temp2;
		}
	}
	return 0;
}