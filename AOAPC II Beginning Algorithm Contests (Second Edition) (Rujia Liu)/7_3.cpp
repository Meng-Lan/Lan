#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<vector>
#include<map>
#include<set>
#include<utility>
#include<queue>
#include<stack>
#include<algorithm>
#include<cstdlib>
using namespace std;
void print_subset(int n, int *A, int cur) {
	for (int i = 0; i < cur; i++)
		printf("%d ", A[i]);
	putchar('\n');
	int s = cur ? A[cur - 1] + 1 : 0;
	for (int i = s; i < n; i++) {
		A[cur] = i;
		print_subset(n, A, cur + 1);
	}
}
int main() {
	int A[10];
	print_subset(5, A, 0);
	return 0;
}