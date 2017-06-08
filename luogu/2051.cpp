#include<cstdio>
#include<iostream>
#include<cstring>
char str[100][100005], ans[105];
int main() {
	int n;
	using std::endl;
	std::cin >> n;
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		std::cin >> str[i];
		if ((str[i][4] >= 'a'&&str[i][4] <= 'z')
			|| (str[i][4] >= 'A'&&str[i][4] <= 'Z')
			|| (str[i][4] >= '0'&&str[i][4] <= '9'))
			ans[cnt++] = str[i][4];
	}
	ans[cnt] = '\0';
	std::cout << "AABDACABBC\n";
	std::cout << ans << endl;
	return 0;
}