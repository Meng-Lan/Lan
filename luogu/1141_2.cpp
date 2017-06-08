#define  _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
#include<queue>
struct lan {
	int x, y;
	lan(int a, int b) {
		x = a;
		y = b;
	}
};
std::queue<lan> que;
char str[1005][1005];
int num[1005][1005][2], sum[100005];
int main() {
	int n, m;
	using std::cin;
	using std::cout;
	using std::endl;
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		scanf("%s", &str[i]);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			num[i][j][0] = str[i][j] - '0';
	/*for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cout << num[i][j][0];
		cout << endl;
	}*/
	int x, y, tx, ty, cnt = 0, count = 0;
	for (int i = 0; i < m; i++) {
		cin >> x >> y;
		x--;
		y--;
		if (num[x][y][1]) {
			printf("%d\n", sum[num[x][y][1]]);
		}
		else {
			cnt++;
			count = 0;
			que.push(lan(x, y));
			for (; !que.empty();) {
				lan &temp = que.front();
				que.pop();
				if (!num[temp.x][temp.y][1])
					if (num[temp.x][temp.y][0]) {
						count++;
						num[temp.x][temp.y][1] = cnt;
						if (temp.x + 1 < n)
							if (!num[temp.x + 1][temp.y][0] && !num[temp.x + 1][temp.y][1])
								que.push(lan(temp.x + 1, temp.y));
						if (temp.x - 1 >= 0)
							if (!num[temp.x - 1][temp.y][0] && !num[temp.x - 1][temp.y][1])
								que.push(lan(temp.x - 1, temp.y));
						if (temp.y + 1 < n)
							if (!num[temp.x][temp.y + 1][0] && !num[temp.x][temp.y + 1][1])
								que.push(lan(temp.x, temp.y + 1));
						if (temp.y - 1 >= 0)
							if (!num[temp.x][temp.y - 1][0] && !num[temp.x][temp.y - 1][1])
								que.push(lan(temp.x, temp.y - 1));
					}
					else {
						count++;
						num[temp.x][temp.y][1] = cnt;
						if (temp.x + 1 < n)
							if (num[temp.x + 1][temp.y][0] && !num[temp.x + 1][temp.y][1])
								que.push(lan(temp.x + 1, temp.y));
						if (temp.x - 1 >= 0)
							if (num[temp.x - 1][temp.y][0] && !num[temp.x - 1][temp.y][1])
								que.push(lan(temp.x - 1, temp.y));
						if (temp.y + 1 < n)
							if (num[temp.x][temp.y + 1][0] && !num[temp.x][temp.y + 1][1])
								que.push(lan(temp.x, temp.y + 1));
						if (temp.y - 1 >= 0)
							if (num[temp.x][temp.y - 1][0] && !num[temp.x][temp.y - 1][1])
								que.push(lan(temp.x, temp.y - 1));
					}
			}
			sum[cnt] = count;
			printf("%d\n", count);
		}
	}
	return 0;
}