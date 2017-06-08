#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
#include<cstring>
const int maxn = 100;
char str[maxn];
int main() {
	scanf("%s", str);
	int len = strlen(str);
	int k = 0;
	for (int i = 1; i < len;i++)
		if (str[i] == str[0]) {
			if (len%i != 0)
				continue;
			for (int j = 0; j < i; j++)
				for (int l = 1; l < len / i; l++)
					if (str[j] != str[j + l*i])
						continue;
			k = i;
			break;
		}
	if (!k)
		k = len+1;
	printf("%d\n", k);
	return 0;
}