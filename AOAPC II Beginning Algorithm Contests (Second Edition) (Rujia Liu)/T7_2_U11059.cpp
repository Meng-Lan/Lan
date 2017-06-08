#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn = 20;
int num[maxn];
int main() {
	int n, kase = 0;
	while (scanf("%d", &n) == 1) {
		long long ans = 0;
		for (int i = 0; i < n; i++)
			scanf("%d", num + i);
		for (int i = 0; i < n; i++)
			for (int j = i; j < n; j++) {
				long long temp = num[i];
				for (int k = i + 1; k <= j; k++)
					temp *= num[k];
				ans = max(ans, temp);
			}
		printf("Case #%d: The maximum product is %lld.\n\n", ++kase, ans);
	}
	return 0;
}