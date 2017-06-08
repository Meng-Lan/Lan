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
const int maxn = 30;
vector<int> vi[maxn];
int A[maxn],B[maxn],vis[maxn];
int n,Min;
char ans[maxn];
void dfs(int cur, int k) {
	if (cur == n&&k < Min) {
		Min = k;
		for (int i = 0; i < n; i++)
			ans[i] = A[i] + 'A';
	}
	else for (int i = 0; i < 26; i++)
		if (vis[i]) {
			int ok = 1;
			for (int j = 0; j < cur; j++)
				if (i == A[j]) {
					ok = 0;
					break;
				}
			if (ok) {
				A[cur] = i;
				B[i] = cur;
				int kt = 0, non = 0;
				int sta = 1;
				for (int j = 0; j <= cur; j++)
					if (vi[A[j]].size()) {
						non = 0;
						for (const auto &t : vi[A[j]])
							if (B[t] != -1)
								kt = max(kt, abs(B[A[j]] - B[t]));
							else
								non++;
						if (kt >= Min || non >= Min) {
							sta = 0;
							break;
						}
						kt = max(kt, non);
					}
				if (!sta) {
					B[i] = -1;
					continue;
				}
				dfs(cur + 1, max(k, kt));
				B[i] = -1;
			}
		}
}
int main() {
	string s;
	while (getline(cin, s) && s[0] != '#') {
		n = 0;
		for (auto &t : vi)
			t.clear();
		for (int i = 0; i < s.size(); i++) {
			char beg = s[i++];
			while (s[++i] != ';'&&i != s.size())
				vi[beg - 'A'].push_back(s[i]-'A');
		}
		memset(vis, 0, sizeof(vis));
		for (auto &t : s)
			if (isalpha(t))
				vis[t - 'A'] = 1;
		for (auto &t : vis)
			if (t)
				++n;
		Min = n;
		memset(B, -1, sizeof(B));
		dfs(0, 0);
		for (int i = 0; i < n; i++)
			printf("%c ", ans[i]);
		printf("-> %d\n", Min);
	}
	return 0;
}
/*
A:EHD;B:EDF;F:BCZ;H:ACZ
#
*/