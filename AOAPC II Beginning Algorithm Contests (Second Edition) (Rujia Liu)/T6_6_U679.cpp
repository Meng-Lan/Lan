#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
using namespace std;
#define lson rt<<1
#define rson rt<<1|1
int main() {
	int T, D, I;
	scanf("%d", &T);
	while(T--){
		int ans = 1;
		scanf("%d%d", &D, &I);
		for (int i = 0; i < D - 1; i++) {
			if (I & 1) {
				ans *= 2;
				I = (I + 1) >> 1;
			}
			else {
				ans = ans * 2 + 1;
				I /= 2;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}