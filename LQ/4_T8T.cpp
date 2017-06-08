#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
#include<cstring>
char str[100005];
int main() {
	int l;
	scanf("%s%d", str, &l);
	int ans = 0, temp = 0, count = 0;
	for (int i = 0; i < l; i++)
		if (str[i] - '0')
			ans++;
	count = ans;
	int len = strlen(str);
	len -= l;
	for (int i = 1; i < len; i++) {
		if (str[i - 1] - '0')
			count--;
		if (str[i + l-1] - '0')
			count++;
		if (count > ans) {
			temp = i;
			ans = count;
		}
	}
	std::cout << '[' << temp+1 << ',' << temp + l << "] " << (double)ans / l << std::endl;
	return 0;
}