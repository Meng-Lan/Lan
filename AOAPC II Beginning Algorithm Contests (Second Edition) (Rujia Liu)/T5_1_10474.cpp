#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn = 10005;
int num[maxn];
int main() {
	int n, q, kase = 0;
	while (cin >> n >> q&&n) {
		printf("CASE# %d:\n", ++kase);
		for (int i = 0; i < n; i++)
			scanf("%d", &num[i]);
		sort(num, num + n);
		int temp;
		while(q--){
			scanf("%d", &temp);
			int k = lower_bound(num, num + n, temp) - num;
			if (num[k] == temp&&k<n)
				printf("%d found at %d\n", temp, k + 1);
			else printf("%d not found\n", temp);
		}
	}
	return 0;
}