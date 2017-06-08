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

queue<int> q;
set<int> si;

int main() {
	int n, m;
	scanf("%d%d", &m, &n);
	int t, cnt = 0;
	for (int i = 0; i < n; i++) {
		scanf("%d", &t);
		if (si.count(t))
			continue;
		else {
			if (q.size() == m) {
				si.erase(q.front());
				q.pop();
			}
			q.push(t);
			si.insert(t);
			cnt++;
		}
	}
	printf("%d\n", cnt);
	return 0;
}