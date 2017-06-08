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
#define FOR(i,init,len) for(int i=(init);i<(len);++i)
#define For(i,init,len) for(int i=(init);i<=(len);++i)
#define mp make_pair

const int maxn = 1e5 + 10;
int n, l, r, A[maxn];

inline int lowbit(int x) {
	return x&-x;
}

void add(int x, int v) {
	while (x <= n) {
		A[x] += v;
		x += lowbit(x);
	}
}

int sum(int x) {
	int ans = 0;
	while (x > 0) {
		ans += A[x];
		x -= lowbit(x);
	}
	return ans;
}

int main() {
	while (scanf("%d", &n) == 1 && n) {
		memset(A, 0, sizeof(A));
		FOR(i, 0, n) {
			scanf("%d%d", &l, &r);
			add(l, 1);
			add(r + 1, -1);
		}
		int cnt = 0;
		For(i, 1, n) {
			printf("%d%c", sum(i), i != n ? ' ' : '\n');
		}
	}
	return 0;
}