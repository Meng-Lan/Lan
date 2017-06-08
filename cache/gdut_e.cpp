#include<cstdio>
const int maxn = 1e6 + 5;
int num[maxn];
int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		int n;
		scanf("%d", &n);
		long long ans = 0, sum = 0;
		int max = 0, left = 0, right = 0;
		for (int i = 0; i < n;i++){
			scanf("%d", num + i);
			if (num[i] >= max || right - left>1) {
				right = i;
				ans += max*(right - left - 1) - sum;
				sum = 0;
				left = i;
			}
			else
