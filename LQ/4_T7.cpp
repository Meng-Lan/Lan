#include<iostream>
#include<string>
#include<sstream>
int num[10010];
using namespace std;
int main() {
	int N;
	cin >> N;
	string line;
	int temp;
	//cout << N << endl;
	for (int i = 0; i <= N; i++) {
		getline(cin, line);
		stringstream ss(line);
		while (ss >> temp)
			num[temp]++;
	}
	int m=1, n=1, off = 0;
	for (int i = 0; i < 10005; i++) {
		if (!off&&num[i])
			off = 1;
		if (off&&!num[i]&&num[i+1])
			m = i;
		if (num[i] > 1)
			n = i;
	}
	cout << m << " " << n << endl;
	return 0;
}