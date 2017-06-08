#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<string>
#include<sstream>
#include<queue>
#include<vector>
using namespace std;
//debug了一整個晚上，結果發現，終點位置沒有標記成true，欸，這個血的教訓啊
struct Node {
	int r, c, dir;
	Node(int r=0, int c=0, int dir=0) :r(r), c(c), dir(dir) {}
};
string name;
const int maxn = 15;
const char *dirs = "NESW";
const char *turns = "FLR";
int d[maxn][maxn][5];
Node p[maxn][maxn][5];
bool has_edge[maxn][maxn][5][4];
bool mp[maxn][maxn];
int r0, c0, r1, c1, r2, c2, dir;
char t_dir;

int dir_id(char c) {
	return strchr(dirs, c) - dirs;
}
int turn_id(char c) {
	return strchr(turns, c) - turns;
}

const int dr[] = { -1,0,1,0 };
const int dc[] = { 0,1,0,-1 };

Node walk(const Node &u, int turn) {
	int dir = u.dir;
	if (turn == 1) dir = (dir + 3) % 4;
	if (turn == 2) dir = (dir + 1) % 4;
	return Node(u.r + dr[dir], u.c + dc[dir], dir);
}

void print_ans(Node u) {
	vector<Node> nodes;
	for (;;) {
		nodes.push_back(u);
		if (d[u.r][u.c][u.dir] == 0) break;
		u = p[u.r][u.c][u.dir];
	}
	nodes.push_back(Node(r0, c0, dir));
	int cnt = 0;
	for (int i = nodes.size() - 1; i >= 0; i--) {
		if (cnt % 10 == 0) putchar(' ');
		printf(" (%d,%d)", nodes[i].r, nodes[i].c);
		if (++cnt % 10 == 0)
			putchar('\n');
	}
	if (nodes.size() % 10 != 0) putchar('\n');
}

bool inside(int r, int c) {
	return mp[r][c];
}
void solve(Node &t) {
	queue<Node> q;
	memset(d, -1, sizeof(d));
	d[t.r][t.c][t.dir] = 0;
	q.push(t);
	while (!q.empty()) {
		Node u = q.front();
		q.pop();
		if (u.r == r2&&u.c == c2) {
			print_ans(u);
			return;
		}
		for (int i = 0; i < 3; i++) {
			Node v = walk(u, i);
			if (has_edge[u.r][u.c][u.dir][i] && inside(v.r, v.c) && d[v.r][v.c][v.dir] < 0) {
				d[v.r][v.c][v.dir] = d[u.r][u.c][u.dir] + 1;
				p[v.r][v.c][v.dir] = u;
				q.push(v);
			}
		}
	}
	printf("  No Solution Possible\n");
}
bool read_input() {
	getline(cin, name);
	if (name=="END") return false;
	scanf("%d%d %c %d%d", &r0, &c0, &t_dir, &r2, &c2);
	memset(p, 0, sizeof(p));
	memset(has_edge, 0, sizeof(has_edge));
	memset(mp, 0, sizeof(mp));
	mp[r2][c2] = true;
	int r, c;
	string temp, s;
	getline(cin, s);
	while (getline(cin, s)) {
		stringstream ss(s);
		ss >> r;
		if (r == 0) break;
		ss >> c;
		mp[r][c] = true;
		while (ss >> temp) {
			if (temp == "*")
				break;
			for (int i = 1; i < temp.size(); i++) {
				has_edge[r][c][dir_id(temp[0])][turn_id(temp[i])] = true;
			}
		}
	}
	Node t = walk(Node(r0, c0, dir_id(t_dir)), 0);
	std::cout << name << std::endl;
	solve(t);
	return true;
}
int main() {
	while (read_input());
	return 0;
}