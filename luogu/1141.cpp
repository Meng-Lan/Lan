#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
char str[1005][1005];
int num[1005][1005];
int n, m, cnt, count, sum[100005];
int lan[1000005][2];
/*void bfs(int, int);*/
int main() {
	std::cin >> n >> m;
	for (int i = 0; i < n; i++)
		scanf("%s", &str[i]);
	int x, y, left=0, right=0;
	for (int i = 0; i < m; i++) {
		std::cin >> x >> y;
		if (x - 1 >= 0 && x - 1 < n&&y - 1 >= 0 && y - 1 < n) {
			x--;
			y--;
			if (num[x][y])
				std::cout << sum[num[x][y]] << std::endl;
			else {
				cnt++;
				count = 0;
				left = right = 0;
				lan[right][0] = x;
				lan[right++][1] = y;
				for (; left % 1000005 < right % 1000005;) {
					x = lan[left][0];
					y = lan[left][1];
					left++;
					if (!num[x][y])
						if (str[x][y] - '0') {
							num[x][y] = cnt;
							count++;
							if (x + 1 < n)
								if (!(str[x + 1][y] - '0')) {
									lan[right][0] = x + 1;
									lan[right++][1] = y;
								}
							if (x - 1 >= 0)
								if (!(str[x - 1][y] - '0')) {
									lan[right][0] = x - 1;
									lan[right++][1] = y;
								}
							if (y + 1 < n)
								if (!(str[x][y + 1] - '0')) {
									lan[right][0] = x;
									lan[right++][1] = y + 1;
								}
							if (y - 1 >= 0)
								if (!(str[x][y - 1] - '0')) {
									lan[right][0] = x;
									lan[right++][1] = y - 1;
								}
						}
						else {
							num[x][y] = cnt;
							count++;
							if (x + 1 < n)
								if (str[x + 1][y] - '0') {
									lan[right][0] = x + 1;
									lan[right++][1] = y;
								}
							if (x - 1 >= 0)
								if (str[x - 1][y] - '0') {
									lan[right][0] = x - 1;
									lan[right++][1] = y;
								}
							if (y + 1 < n)
								if (str[x][y + 1] - '0') {
									lan[right][0] = x;
									lan[right++][1] = y + 1;
								}
							if (y - 1 >= 0)
								if (str[x][y - 1] - '0') {
									lan[right][0] = x;
									lan[right++][1] = y - 1;
								}
						}
				}
				sum[cnt] = count;
				std::cout << count << std::endl;
			}
		}
	}
	return 0;
}

/*void bfs(int x, int y) {
	if (!num[x][y])
		if (str[x][y]-'0') {
			num[x][y] = cnt;
			count++;
			if (x + 1 < n)
				if ((!str[x + 1][y]-'0'))
					bfs(x + 1, y);
			if (x - 1 >= 0)
				if (!(str[x - 1][y]-'0'))
					bfs(x - 1, y);
			if (y + 1 < n)
				if (!(str[x][y + 1]-'0'))
					bfs(x, y + 1);
			if (y - 1 >= 0)
				if (!(str[x][y - 1]-'0'))
					bfs(x, y - 1);
		}
		else {
			num[x][y] = cnt;
			count++;
			if (x + 1 < n)
				if (str[x + 1][y]-'0')
					bfs(x + 1, y);
			if (x - 1 >= 0)
				if (str[x - 1][y]-'0')
					bfs(x - 1, y);
			if (y + 1 < n)
				if (str[x][y + 1]-'0')
					bfs(x, y + 1);
			if (y - 1 >= 0)
				if (str[x][y - 1]-'0')
					bfs(x, y - 1);
		}
}*/