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
const int maxn = 10005;
int num[maxn],tmp[maxn];
int main() {
	int T;
	scanf("%d", &T);
	int x, m, c, k, kase = 0;
	while (T--) {
		scanf("%d%d%d%d", &x, &m, &k, &c);
		memset(num, 0, sizeof(num));
		memset(tmp, 0, sizeof(tmp));
		int t = x%k;
		int node = 0;
		num[node++] = t;
		while(!tmp[t]&&t){
			tmp[t] = node;
			t = t * 10 + x;
			t %= k;
			num[node++] = t;
		}
		if (c == num[(m+node-1)%node])
			printf("Case #%d:\n%s\n", ++kase, "Yes");
		else
			printf("Case #%d:\n%s\n", ++kase, "No");
	}
	return 0;
}