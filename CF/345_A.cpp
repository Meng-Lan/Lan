#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<sstream>
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
const int maxn = 105;
int num[maxn];
int main() {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", num + i);
	int Min, Max;
	for (int i = 0; i < n; i++) {
		if (num[i] == 1)
			Min = i;
		if (num[i] == n)
			Max = i;
	}
	int left = min(Min, Max);
	int right = max(Min, Max);
	int ans = max(n - left - 1, right);
	printf("%d\n", ans);
	return 0;
}