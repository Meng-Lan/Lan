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
typedef int State[9];
const int maxn = 1000000;
State st[maxn], goal= { 1,2,3,8,0,4,7,6,5 };
int dist[maxn];
/*int vis[362880], face[9];
void init() {
	face[0] = 1;
	for (int i = 1; i < 9; i++)
		face[i] = face[i - 1] * i;
}
int try_to_insert(int s) {
	int code = 0;
	for (int i = 0; i < 9; i++) {
		int cnt = 0;
		for (int j = i+1; j < 9; j++)
			if (st[s][j] < st[s][i]) cnt++;
		code += face[8 - i] * cnt;
	}
	if (vis[code]) return 0;
	return vis[code] = 1;
}*/
set<int> vis;
void init_set() {
	vis.clear();
}
int try_to_insert(int s) {
	int v = 0;
	for (int i = 0; i < 9; i++) v += v * 10 + st[s][i];
	if (vis.count(v)) return 0;
	vis.insert(v);
	return 1;
}
const int dx[] = { -1,1,0,0 };
const int dy[] = { 0,0,-1,1 };
int bfs() {
	init_set();
	int front = 1, rear = 2;
	while (front < rear) {
		State &s = st[front];
		if (memcmp(goal, s, sizeof(s))==0) return front;
		int z;
		for (z = 0; z < 9; z++) if (!s[z]) break;
		int x = z / 3, y = z % 3;
		for (int i = 0; i < 4; i++) {
			int newx = x + dx[i];
			int newy = y + dy[i];
			int newz = newx * 3 + newy;
			if (newx >= 0 && newx < 3 && newy >= 0 && newy < 3) {
				State &t = st[rear];
				memcpy(&t, &s, sizeof(s));
				t[newz] = s[z];
				t[z] = s[newz];
				dist[rear] = dist[front] + 1;
				if (try_to_insert(rear)) rear++;
			}
		}
		front++;
	}
	return 0;
}
int main() {
	string s;
	cin >> s;
	for (int i = 0; i < s.size(); i++)
		st[1][i] = s[i] - '0';
	int ans = bfs();
	printf("%d\n", dist[ans]);
	return 0;
}