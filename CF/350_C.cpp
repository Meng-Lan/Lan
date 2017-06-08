#include<iostream>
#include<cstdio>
#include<map>
using namespace std;
const int maxn = 2e5 + 10;
int  b[maxn],c[maxn];
map<int, int> a;
int main() {
	int n, m;
	int temp;

	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &temp);
		a[temp]++;
	}
	scanf("%d", &m);
	for (int i = 0; i < m; i++)
		scanf("%d", b + i);
	for (int i = 0; i < m; i++)
		scanf("%d", c + i);
	int num = 0;
	long long maxp = 0;
	long long cnt = 0, t = 0, sum=0;
	for (int i = 0; i < m; i++) {
		t = sum = 0;
		if (a[b[i]]) {
			t = a[b[i]];
			sum += a[b[i]];
		}
		if (a[c[i]]) {
			sum += a[c[i]];
		}
		if (t > maxp) {
			maxp = t;
			num = i;
			cnt = sum;
		}
		else if (t == maxp&&sum > cnt) {
			cnt = sum;
			num = i;
		}
	}
	printf("%d\n", num + 1);
	return 0;
}