#include<iostream>
#include<cstdio>
#include<stack>
#include<string>
#include<sstream>
using namespace std;
const int maxn = 1e3 + 10;
int n, target[maxn];
int main() {
	while (scanf("%d", &n)&&n) {
		stack<int> si;
		int A, B;
		while (scanf("%d", &target[1]) && target[1]) {
			for (int i = 2; i <= n; i++)
				scanf("%d", target + i);
			A = B = 1;
			while (!si.empty())
				si.pop();
			int ok = 1;
			while (B <= n) {
				if (A == target[B]) {
					A++;
					B++;
				}
				else if (!si.empty() && si.top() == target[B]) {
					si.pop();
					B++;
				}
				else if (A <= n) {
					si.push(A++);
				}
				else {
					ok = 0;
					break;
				}
			}
			printf("%s\n", ok ? "Yes" : "No");
		}
		putchar('\n');
	}
	return 0;
}