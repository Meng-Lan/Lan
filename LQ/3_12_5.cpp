#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>

using namespace std;

int fun(int n, int m)  // fun(n, m)��ʾ������ n ����Ϊ����������� m �Ļ���
{
	if (n == 1 || m == 1)
		return 1;
	if (n < m)
		return fun(n, n);
	if (n > m)     // ��ʱ������ת��Ϊ������  1.�����к��� m��   2.�����в��� m
		return fun(n - m, m) + fun(n, m - 1);
	if (n == m)// ��ʱҲ�������֣�������� m ��ֻ��һ��ֻ���� m �Ļ��֣���������� m ��ת��Ϊ����������� m-1 �Ļ���
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