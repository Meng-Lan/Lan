#include<iostream>
#include<cstdio>
using namespace std;
const int maxn = 1e6 + 10;
int num[maxn];
int main() {
	long long  n, k;
	cin >> n >> k;
	for (int i = 0; i < n; i++)
		scanf("%d", num + i);
	long long cnt = k;
	for (long long i = 1; i < cnt; i++)
		cnt -= i;
	printf("%d\n", num[cnt - 1]);
	return 0;
}