#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<map>
#include<string>
#include<iostream>
#include<vector>
#include<utility>
#include<set>
using namespace std;
char A[15], B[15];
void print_permutation(const int &n, int cur) {
	if (cur == n) {
		for (int i = 0; i < n; i++)
			putchar(A[i]);
		putchar('\n');
	}
	else
		for (int i = 0; i < n; i++)
			if (!i || B[i] != B[i - 1]) {
				int c1 = 0, c2 = 0;
				for (int j = 0; j < cur; j++) if (A[j] == B[i]) c1++;
				for (int j = 0; j < n; j++) if (B[j] == B[i]) c2++;
				if (c1 < c2) {
					A[cur] = B[i];
					print_permutation(n, cur + 1);
				}
			}
}
int main() {
	scanf("%s", B);
	int n = strlen(B);
	sort(B, B + n);
	print_permutation(n, 0);
	return 0;
}