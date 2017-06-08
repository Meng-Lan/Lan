#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<map>
#include<queue>
#include<cstdio>
using namespace std;
const int maxn = 1e3 + 10;
int main() {
	int t, kase=0;
	while (cin >> t&&t) {
		printf("Scenario #%d\n", ++kase);
		map<int, int> team;
		int n, x;
		for (int i = 0; i < t; i++) {
			cin >> n;
			while (n--) {
				scanf("%d", &x);
				team[x] = i;
			}
		}
		queue<int> q, q2[maxn];
		for (;;) {
			char cmd[10];
			scanf("%s", cmd);
			if (cmd[0] == 'S') break;
			else if (cmd[0] == 'D') {
				int t = q.front();
				printf("%d\n", q2[t].front());
				q2[t].pop();
				if (q2[t].empty()) q.pop();
			}
			else if (cmd[0] == 'E') {
				scanf("%d", &x);
				if (q2[team[x]].empty())
					q.push(team[x]);
				q2[team[x]].push(x);
			}
		}
		printf("\n");
	}
	return 0;
}