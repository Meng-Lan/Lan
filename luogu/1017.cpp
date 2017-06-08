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
typedef long long ll;
typedef pair<int, int> P;
#define mp make_pair
const int maxn = 256;
char ans[maxn];

char trans(int n) {
	return (n < 10) ? (n + '0') : (n -10+ 'A');
}

int main() {
	int n, base;
	scanf("%d%d", &n, &base);
	printf("%d=", n);
	int i = 0;
	while (n) {
		int mod = n%base;
		mod = mod < 0 ? (mod - base) : mod;
		ans[i++] = trans(mod);
		n = (n - mod) / base;
	}
	while (i--)
		printf("%c", ans[i]);
	printf("(base%d)", base);
	return 0;
}