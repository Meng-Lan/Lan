#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<iostream>
#include<utility>
typedef std::pair<int, int> P;
P p[100010], temp[100010];
int num[100005];
inline int abs(int n) {
	return n >= 0 ? n : -n;
}
void mergearray(int left, int mid, int right) {
	int i = left, j = mid + 1;
	int m = mid, n = right;
	int k = 0;
	while (i <= m&&j <= n) {
		if (p[i].first <= p[j].first) {
			p[i].second += abs(i - k-left);
			temp[k++] = p[i++];
		}
		else {
			p[j].second += abs(j - k-left);
			temp[k++] = p[j++];
		}
	}
	while (i <= m) {
		p[i].second += abs(i - k-left);
		temp[k++] = p[i++];
	}
	while (j <= n) {
		p[j].second += abs(j - k-left);
		temp[k++] = p[j++];
	}
	for (int i = 0; i < k; i++)
		p[left+i] = temp[i];
}
void mergesort(int left, int right) {
	if (left < right) {
		int mid = (left + right) / 2;
		mergesort(left, mid);
		mergesort(mid+1, right);
		mergearray(left, mid, right);
	}
}
int main() {
	for (int i = 1; i < 100005; i++)
		num[i] += num[i - 1] + i;
	int n;
	std::cin >> n;
	for (int i = 0; i < n; i++)
		scanf("%d", &p[i].first);
	mergesort(0, n-1);
	unsigned long long ans = 0;
	for (int i = 0; i < n; i++) 
		ans += num[p[i].second];
	std::cout << ans << std::endl;
	return 0;
}