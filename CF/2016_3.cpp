#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
#include<utility>
#include<algorithm>
typedef std::pair<int, int> P;
#define maxn 100005
P num[maxn];
inline double D(double a, double b, double c, double x0, double y0) {
	return (a*x0 + b*y0 + c)*(a*x0 + b*y0 + c) / (a*a + b*b);
}
int main() {
	int n;
	std::cin >> n;
	for (int i = 0; i < n; i++)
		scanf("%d%d", &num[i].first, &num[i].second);
	std::sort(num, num + n);
	P one = num[n / 2];
	P two = num[(n / 2) + 1];
	double k = (one.second - two.second) / (one.first - two.first);
	int temp = (n/2)+1;
	for (int i = n/2+2; i < n; i++)
		if ((one.second - num[i].second) / (one.first - num[i].first) == k)
			if (num[i].second < two.second) {
				two = num[i];
				temp = i;
			}
	P san = num[0];
	std::cout << k;
	double a = -k, b = 1, c = k*two.first - two.second, d = D(a, b, c, san.first, san.second);
	int tp = 0;
	for (int i= 0; i < n; i++)
		if (D(a, b, c, num[i].first, num[i].second) < d)
			if (i != (n / 2) && i != temp && (two.second - num[i].second) / (two.first - num[i].first) != k) {
				tp = i;
				san = num[i];
			}
	int m[3];
	m[0] = n / 2;
	m[1] = temp;
	m[2] = tp;
	//std::cout << n / 2 << " " << temp << " " << i;
	std::sort(m, m + 3);
	for (int j = 0; j < 3; j++)
		std::cout << m[j] << " ";
	return 0;
}