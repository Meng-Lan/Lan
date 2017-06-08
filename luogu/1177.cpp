#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
int num[100000 + 5];
void swap(int x, int y) {
	int temp = num[x];
	num[x] = num[y];
	num[y] =temp;
}
void qsort(int left, int right) {
	if (left >= right)
		return;
	int mid = num[(left + right) / 2];
	int i = left, j = right;
	for (; i <= j;) {
		while (num[i] < mid&&i<right)
			i++;
		while (num[j] > mid&&j>left)
			j--;
		if (i <= j) {
			swap(i, j);
			i++;
			j--;
		}
	}
	qsort(left, j);
	qsort(i, right);
}
int main() {
	int n;
	std::cin >> n;
	for (int i = 0; i < n; i++)
		scanf("%d", &num[i]);
	qsort(0, n - 1);
	for (int i = 0; i < n; i++)
		printf("%d ", num[i]);
	return 0;
}
