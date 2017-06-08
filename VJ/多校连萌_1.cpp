#include<iostream>
#include<cstring>
char temp[105];
using namespace std;
int ans = 0, cnt = 0, tmp = 0, num[105];
void dfs(int off, int n, int left, int temp) {
	//cout << off << "  " << n << "  " << left << "  " << right << "  " << temp << endl;
	if (left >= cnt) {
		if (n)
			temp -= (n & 1);
		if (temp > ans)
			ans = temp;
		return;
	}
	/*if (n == 0) {
		if (off) {
			temp += num[left];
			if (temp > ans)
				ans = temp;
		}
		else {
			temp -= num[left];
			if (temp > ans)
				ans = temp;
		}
		return;
	}*/
	if (n >= (cnt - left - 1) && off) {
		for (int i = left; i < cnt; i++)
			temp += num[i];
		temp += (cnt - left - 1);
		temp -= ((n - (cnt - left - 1)) & 1);
		if (temp > ans)
			ans = temp;
		return;
	}
	if (off) {
		if (n)
			if (n - 1)
				dfs(off, n - 1, left + 1,  temp + num[left] + 1);
			else
				dfs(off, n - 1, left + 1,  temp + num[left]);
		dfs(!off, n, left + 1, temp + num[left]);
	}
	else {
		if (n)
			if (n - 1)
				dfs(off, n - 1, left + 1, temp - num[left] - 1);
			else
				dfs(off, n - 1, left + 1, temp - num[left]);
		dfs(!off, n, left + 1,  temp - num[left]);
	}
}
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
		/*tmp = n;
		for (int i = 0; i <= n; i++)
			tmp += num[i];
		ans = tmp;
		for (int i = 0; i <= cnt - n; i++) {
			tmp = tmp - num[i] + num[i + n + 1];
			if (tmp > ans)
				ans = tmp;
		}*/
		/*for (int i = 0; i <= cnt; i++)
			cout << num[i] << "  ";
		putchar('\n');*/
		dfs(1, n, 0, 0);
		cout << ans << endl;
	}
	return 0;
}
/*
FFTFTFFTFFFFTFFF
3
*/