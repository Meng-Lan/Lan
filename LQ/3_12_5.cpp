#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>

using namespace std;

int fun(int n, int m)  // fun(n, m)表示将整数 n 划分为最大数不超过 m 的划分
{
	if (n == 1 || m == 1)
		return 1;
	if (n < m)
		return fun(n, n);
	if (n > m)     // 此时将问题转化为两部分  1.划分中含有 m；   2.划分中不含 m
		return fun(n - m, m) + fun(n, m - 1);
	if (n == m)// 此时也是两部分，如果含有 m 则只有一种只含有 m 的划分，如果不含有 m 则转化为最大数不超过 m-1 的划分
		return 1 + fun(n, m - 1);
}

int main()
{
	int T, n;
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &n);
		printf("%d\n", fun(n, n));
	}
	return 0;
}