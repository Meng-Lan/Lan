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
const int maxn = 10;
int n, maxd;
int start[maxn],ans[maxn];

void print(int *s) {
	for (int i = 0; i < n; i++)
		printf("%d ", s[i]);
	putchar('\n');
}

bool dfs(int d,int *s) {
	if (memcmp(ans, s, sizeof(int)*n) == 0) {
		//print(s); 
		return true;
	}
	if (d == maxd) return false;
	int h = 0;
	for (int i = 0; i < n - 1; i++)
		if (s[i] != s[i+1] - 1)
			h++;
	if (3 * d + h > 3 * maxd) {
		//printf("jz d:%d maxd:%d h:%d :", d,maxd,h);
		//print(s);
		return false;
	}
	int t[maxn];
	//cout << n << endl;
	for (int len = 1; len <= n / 2; len++)
		for (int begin = 0; begin <= n - len; begin++)
			for (int i = 0; i <= n-len; i++)
				if (i < begin) {
					//cout << len << "  " << begin << "  " << i << endl;
					memcpy(t, s, sizeof(int)*i);
					memcpy(t + i, s + begin, sizeof(int)*len);
					memcpy(t + i + len, s + i, sizeof(int)*(begin - i));
					if (n - begin - len>0)
						memcpy(t + begin + len, s + begin + len, sizeof(int)*(n - begin - len));
					/*for (int i = 0; i < n;i++)
						if (t[i] < 0) {
							printf("#1:  len:%d begin:%d i:%d s:", len, begin, i);
							print(s);
							printf("t:");
							print(t);
							break;
						}*/
					if (dfs(d + 1, t)) {
						//print(s); 
						return true;
					}
				}
				else if (i >= begin + len) {
					//cout << len << "  " << begin << "  " << i << endl;
					memcpy(t, s, sizeof(int)*begin);
					memcpy(t + begin, s + begin + len, sizeof(int)*(i - begin));
					memcpy(t + i, s + begin, sizeof(int)*len);
					if (n - i - len>0)
						memcpy(t + i + len, s + i + len, sizeof(int)*(n - i - len));
					/*for (int k = 0; k < n; k++)
						if (t[k] < 0) {
							printf("#2:  len:%d begin:%d i:%d s:", len, begin, i);
							print(s);
							printf("t:");
							print(t);
							break;
						}*/
					if (dfs(d + 1, t)) {
						//print(s); 
						return true;
					}
				}
	return false;
}

int main() {
	int kase = 0;
	while (scanf("%d", &n) == 1 && n) {
		for (int i = 0; i < n; i++)
			cin >> start[i];
		memset(ans, 0, sizeof(ans));
		for (int i = 0; i < n; i++)
			ans[i] = i + 1;
		if (memcmp(start, ans, sizeof(int)*n) == 0) {
			printf("Case %d: %d\n", ++kase, 0);
			continue;
		}
		for (maxd = 1;; maxd++) {
			if (maxd == n)
				break;
			if (dfs(0, start)) {
				printf("Case %d: %d\n",++kase, maxd);
				break;
			}
		}
	}
	return 0;
}