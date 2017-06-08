#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
int num[3 * 100001];
int lf[150000], rgt[150000];
int main() {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", num + i);
	int left = 0, right = n - 1, l, r;
	l = r = 0;
	int temp = num[0];
	if (num[0] == num[n - 1]) {
		for (; left <= right;) {
			while (num[left] != temp&&left < n)
				left++;
			while (num[right] != temp&&right >= 0)
				right--;
			lf[l++] = left++;
			rgt[r++] = right++;
			std::cout << left<<"  "<<right;
		}
		std::cout << l << std::endl;
		for (int i = 0; i < r + l; i++) {
			if (i < l)
				printf("%d", lf[i]);
			else
				printf("%d", rgt[i - l]);
			if (i < l)
				printf(" %d\n", lf[i]);
			else
				printf(" %d\n", rgt[i - l]);
		}
	}
	else
		std::cout << -1 << std::endl;
	return 0;
}