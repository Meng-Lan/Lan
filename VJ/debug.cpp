#include<iostream>
#include<cstring>
char temp[105];
using namespace std;
int ans = 0, cnt = 0, tmp = 0, num[105];
int main() {
	int n;
	cin >> temp >> n;
	int len = strlen(temp);
	int t = 0;
	for (int i = 0; i < len; i++)
		if (temp[i] == 'T')
			t++;
	if (t == n)
		cout << len << endl;
	else if (t < n)
		cout << len - ((t - n) & 1) << endl;
	else {
		for (int i = 0; i < len; i++)
			if (temp[i] == 'T') {
				num[cnt++] = tmp;
				tmp = 0;
			}
			else
				tmp++;
		num[cnt++] = tmp;
		while (t >= n) {
			int tp[2] = { 100,0 };
			for (int i = 1; i < cnt - 1; i++)
				if (num[i] < tp[0]) {
					tp[0] = num[i];
					tp[1] = i;
				}
			num[tp[1] - 1] = num[tp[1] - 1] + num[tp[1] + 1] - num[tp[1]];
			for (int i = tp[1]; i < cnt - 2; i++)
				num[i] = num[i + 2];
			cnt -= 2;
			t -= 2;
		}
		ans = 0;
		for (int i = 0; i < cnt; i++)
			ans += num[i];
		cout << ans + t - ((n - t) & 1) << endl;
	}
	return 0;
}