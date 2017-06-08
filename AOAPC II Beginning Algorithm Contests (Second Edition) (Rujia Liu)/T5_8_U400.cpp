#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
#include<string>
#include<algorithm>
using namespace std;
const int maxcol = 60;
const int maxn = 105;
string failnames[maxn];
void print(const string&s, int len, char extra) {
	cout << s;
	for (int i = 0; i < len - s.length(); i++)
		cout << extra;
}
int main() {
	int n;
	while (cin>>n) {
		int M = 0;
		for (int i = 0; i < n; i++) {
			cin >> failnames[i];
			M = max(M, (int)failnames[i].length());
		}
		int cols = (maxcol - M) / (M + 2) + 1;
		int rows = (n - 1) / cols + 1;
		print("", maxcol, '-');
		cout << endl;
		sort(failnames, failnames + n);
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				int idx = j*rows + i;
				if (idx < n) print(failnames[idx], j == cols - 1 ? M : M + 2, ' ');
			}
			cout << endl;
		}
	}
	return 0;
}