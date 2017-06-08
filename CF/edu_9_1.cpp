#include<cstdio>
#include<iostream>
#include<cstring>
char str[50][10];
int main() {
	int n, p;
	std::cin >> n >> p;
	long long ans = 0;
	int temp = 0;
	for (int i = 0; i < n; i++)
		std::cin >> str[i];
	for (int i = n - 1; i >= 0; i--) {
		if (strcmp(str[i], "halfplus") == 0) {
			if (ans) {
				ans <<= 1;
				ans++;
				temp++;
			}
			else {
				ans++;
				temp++;
			}
		}
		else if (strcmp(str[i], "half")==0) {
			ans <<= 1;
		}
	}
	std::cout << ans*p - temp*p/2 << std::endl;
	return 0;
}