#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<utility>
#include<queue>
#include<cstring>
using namespace std;
const int maxn = 100000 + 5;
const int INF = 1000000000;

struct Edge {
	int u, v, val;
	Edge(int u = 0, int v = 0, int val = 0) :u(u), v(v), val(val) {}
};
vector<Edge> edges;
vector<int> G[maxn];
int n, m, vis[maxn], d[maxn];

void add_edge(const int &u,const int &v,const int &val) {
	edges.push_back(Edge(u, v, val));
	G[u].push_back(edges.size() - 1);
}

void r_bfs() {
	//memset(d, 0, sizeof(d));
	memset(vis, 0, sizeof(vis));
	queue<int> q;
	q.push(n - 1);
	d[n - 1] = 0;
	vis[n - 1] = true;

	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (int i = 0; i < G[v].size(); i++) {
			int u = edges[G[v][i]].v;
			if (!vis[u]) {
				vis[u] = true;
				d[u] = d[v] + 1;
				q.push(u);
			}
		}
	}
}

vector<int> ans;

void bfs() {
	memset(vis, 0, sizeof(vis));
	vector<int> next;
	next.push_back(0);
	vis[0] = 1;
	ans.clear();
	for (int i = 0; i < d[0]; i++) {
		int color = INF;
		for (int j = 0; j < next.size(); j++) {
			int u = next[j];
			for (int k = 0; k < G[u].size(); k++) {
				Edge &t = edges[G[u][k]];
				if (d[t.v] + 1 == d[u]) {
					color = min(color, t.val);
				}
			}
		}
		ans.push_back(color);
		vector<int> next2;
		for (int j = 0; j < next.size(); j++) {
			int u = next[j];
			for (int k = 0; k < G[u].size(); k++) {
				Edge &t = edges[G[u][k]];
				if (d[u] == d[t.v] + 1 && !vis[t.v] && t.val == color) {
					vis[t.v] = true;
					next2.push_back(t.v);
				}
			}
		}
		next = next2;
	}
	printf("%d\n", ans.size());
	printf("%d", ans[0]);
	for (int i = 1; i < ans.size(); i++)
		printf(" %d", ans[i]);
	putchar('\n');
}
int main() {
	while (scanf("%d%d", &n, &m) == 2) {
		edges.clear();
		for (int i = 0; i < n; i++) G[i].clear();
		int u, v, val;
		for (int i = 0; i < m; i++) {
			scanf("%d%d%d", &u, &v, &val);
			add_edge(u - 1, v - 1, val);
			add_edge(v - 1, u - 1, val);
		}
		r_bfs();
		bfs();
	}
	return 0;
}