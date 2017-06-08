#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
#include<cstring>
const int maxn = 100;
char str[maxn];
int main() {
	int T; scanf("%d", &T);
	while (T--) {
		int ans = 0, temp = 0;
		scanf("%s", str);
		int len = strlen(str);
		for (int i = 0; i < len; i++)
			if (str[i] == 'X')
				temp = 0;
			else if (str[i] == 'O')
				ans += (++temp);
		printf("%d\n", ans);
	}
	return 0;
}