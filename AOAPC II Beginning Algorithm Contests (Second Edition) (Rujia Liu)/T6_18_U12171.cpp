#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
#include<queue>
using namespace std;
const int maxn = 100 + 5;
const int maxc = 1000 + 5;
int xyz[maxn][maxn][maxn], x[maxn], y[maxn], z[maxn];
int x2, y2, z2, n, nx, ny, nz, ansS, ansV;
struct Lan {
	int x1, y1, z1, x2, y2, z2;
	Lan() :x1(0), y1(0), z1(0), x2(0), y2(0), z2(0) {}
};
Lan cub[maxn];

const int dx[] = {1,-1,0,0,0,0};
const int dy[] = {0,0,1,-1,0,0};
const int dz[] = {0,0,0,0,1,-1};

bool inside(int X, int Y, int Z) {
	return X >= 0 && X < nx - 1 && Y >= 0 && Y < ny - 1 && Z >= 0 && Z < nz - 1;
}
int area(int dir,int X,int Y,int Z) {
	if (dx[dir] != 0) return (y[Y + 1] - y[Y])*(z[Z + 1] - z[Z]);
	else if (dy[dir] != 0) return (x[X + 1] - x[X])*(z[Z + 1] - z[Z]);
	return (x[X + 1] - x[X])*(y[Y + 1] - y[Y]);
}

int volu(int X, int Y, int Z) {
	return (x[X + 1] - x[X])*(y[Y + 1] - y[Y])*(z[Z + 1] - z[Z]);
}

struct Cub {
	int x, y, z;
	Cub() :x(0), y(0), z(0) {}
	Cub(int x, int y, int z) :x(x), y(y), z(z) {}
};
void dfs(int X,int  Y,int Z) {
	Cub t;
	queue<Cub> q;
	q.push(t);
	xyz[0][0][0] = -1;
	while (!q.empty()) {
		t = q.front();
		q.pop();
		ansV += volu(t.x, t.y, t.z);
		for (int i = 0; i < 6; i++) {
			int tx = t.x + dx[i];
			int ty = t.y + dy[i];
			int tz = t.z + dz[i];
			if (inside(tx, ty, tz))
				if (xyz[tx][ty][tz] == 0) {
					q.push(Cub(tx, ty, tz));
					xyz[tx][ty][tz] = -1;
				}
				else if (xyz[tx][ty][tz]>0)
					ansS += area(i, tx, ty, tz);
		}
	}
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		memset(xyz, 0, sizeof(xyz));
		memset(x, 0, sizeof(x));
		memset(y, 0, sizeof(y));
		memset(z, 0, sizeof(z));
		memset(cub, 0, sizeof(cub));
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%d%d%d%d%d%d", &cub[i].x1, &cub[i].y1, &cub[i].z1, &x2, &y2, &z2);
			cub[i].x2 = cub[i].x1 + x2;
			cub[i].y2 = cub[i].y1 + y2;
			cub[i].z2 = cub[i].z1 + z2;
			x[i << 1] = cub[i].x1;
			x[i << 1 | 1] = cub[i].x2;
			y[i << 1] = cub[i].y1;
			y[i << 1 | 1] = cub[i].y2;
			z[i << 1] = cub[i].z1;
			z[i << 1 | 1] = cub[i].z2;
		}
		x[2 * n] = y[2 * n] = z[2 * n] = maxc;
		sort(x, x + 2 * n + 2);
		nx = unique(x, x + 2 * n + 2) - x;
		sort(y, y + 2 * n + 2);
		ny = unique(y, y + 2 * n + 2) - y;
		sort(z, z + 2 * n + 2);
		nz = unique(z, z + 2 * n + 2) - z;
		map<int, int> mx, my, mz;
		for (int i = 0; i < nx; i++)
			mx[x[i]] = i;
		for (int i = 0; i < ny; i++)
			my[y[i]] = i;
		for (int i = 0; i < nz; i++)
			mz[z[i]] = i;
		for (int i = 0; i < n; i++) {
			for (int j = mx[cub[i].x1]; j < mx[cub[i].x2]; j++)
				for (int k = my[cub[i].y1]; k < my[cub[i].y2]; k++)
					for (int l = mz[cub[i].z1]; l < mz[cub[i].z2]; l++)
						xyz[j][k][l] = 1;
		}
		ansS = ansV = 0;
		dfs(0, 0, 0);
		printf("%d %d\n", ansS, maxc*maxc*maxc-ansV);
	}
	return 0;
}