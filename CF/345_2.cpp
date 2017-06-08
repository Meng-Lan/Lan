#include<iostream>
#include<cstdio>
#include<algorithm>
int num[1005];
using namespace std;
int main() {
	int n, temp;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> temp;
		num[temp]++;
	}
	int cnt = 0;
	int ans = 0;
	do
	{
		cnt = 0;
		for (int i = 0; i < 1005; i++)
			if (num[i]) {
				num[i]--;
				cnt++;
			}
		if (cnt)
			ans += cnt - 1;
	} while (cnt>1);
	cout << ans << endl;
	return 0;
}