#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>  
#include<math.h>  
int num[1000000];
int main()
{
	int n, t, i;
	double sum;
	scanf("%d", &t);
	while (t--)
	{
		sum = 0;
		scanf("%d", &n);
		for (i = 1; i <= n; i++)
			if (num[i])
				sum += num[i];
			else
			sum += log10((double)i);
		printf("%d\n", (int)sum + 1);
	}

}