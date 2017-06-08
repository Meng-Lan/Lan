#include<iostream>
#include<cstdio>
int num[105];
int num1[105];
int main() {
	using std::cin;
	using std::cout;
	using std::endl;
	int n;
	cin >> n;
	int sum = 0, off = 0, temp = 0, cnt = 0;
	for (int i = 0; i < n; i++) {
		cin >> num[i];
		if (num[i]) {
			sum++;
			off = 1;
			num1[cnt++] = temp;
			temp = 0;
			temp++;
		}
		else if (off)
			temp++;
	}
	int lan = 1;
	for (int i = 1; i < cnt; i++)
		lan *= num1[i];
	if (sum == 0)
		cout << 0 << endl;
	else if (sum == 1)
		cout << 1 << endl;
	else
		cout << lan << endl;
	return 0;
}