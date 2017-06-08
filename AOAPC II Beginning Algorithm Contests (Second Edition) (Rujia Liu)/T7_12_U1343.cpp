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
const int maxn = 24;
const int line[4][7]{{0,2,6,11,15,20,22},
					{1,3,8,12,17,21,23},
					{10,9,8,7,6,5,4},
					{19,18,17,16,15,14,13}};
const int rev[8]= { 5, 4, 7, 6, 1, 0, 3, 2 };
const int center[8] = { 6, 7, 8, 11, 12, 15, 16, 17 };
int maxd;
struct Lan{
	int m[maxn];
	Lan() {
		memset(m, 0, sizeof(m));
	}
	Lan(Lan &t) {
		memcpy(m, t.m, sizeof(m));
	}
	void transfer(int t) {
		if (t < 4)
			for (int i = 5; i >=0; i--)
				swap(m[line[t][6]], m[line[t][i]]);
		else
			for (int i = 0; i < 7; i++)
				swap(m[line[rev[t]][6]], m[line[rev[t]][i]]);
	}
	bool ans() {
		for (int i = 1; i < 8; i++)
			if (m[center[i]] != m[center[0]])
				return false;
		return true;
	}
	int diff(int i) {
		int cnt = 0;
		for (auto &t : center)
			if (m[t] != i)
				cnt++;
		return cnt;
	}
}start;
char ans[1000];

int h() {
	return min(min(start.diff(1), start.diff(2)), start.diff(3));
}

bool dfs(int d) {
	if (start.ans()) {
		ans[d] = '\0';
		printf("%s\n", ans);
		return true;
	}
	if (d+h()>maxd) return false;
	for (int i = 0; i < 8; i++) {
		ans[d] = 'A' + i;
		start.transfer(i);
		if (dfs(d + 1)) return true;
		start.transfer(rev[i]);
	}
	return false;
}
int main() {
	for (;;) {
		for (int i = 0; i < 24; i++) {
			cin >> start.m[i];
			if (start.m[i] == 0)
				return 0;
		}
		if(start.ans())
			printf("No moves needed\n");
		else for (maxd = 1;; maxd++) {
			if (dfs(0)) break;
		}
		printf("%d\n", start.m[6]);
	}
	return 0;
}