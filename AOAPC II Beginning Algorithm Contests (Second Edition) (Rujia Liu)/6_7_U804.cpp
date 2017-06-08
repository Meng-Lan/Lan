#include<iostream>
#include<cstdio>
#include<queue>
#include<utility>
#include<map>
#include<cstring>
using namespace std;
typedef map<int, int> mii;
typedef pair<mii, mii> pmm;
const int maxn = 105;
pmm p[maxn];
int place[maxn];
bool vis[maxn];
void init() {
	for (auto &t : p) {
		t.first.clear();
		t.second.clear();
	}
}
int main() {
	int np, nt, nf, kase = 0;
	while (scanf("%d", &np) && np) {
		for (int i = 1; i <= np; i++)
			scanf("%d", place + i);
		init();
		scanf("%d", &nt);
		for (int i = 0; i < nt; i++) {
			int t;
			while (scanf("%d", &t) && t)
				if (t>0)
					p[i].second[t]++;
				else
					p[i].first[-t]++;
		}
		scanf("%d", &nf);
		int cnt = 0;
		bool off = true, sta = true;
		while (++cnt <= nf) {
			pmm temp;
			for (int i = 0; i < nt; i++) {
				off = true;
				temp = p[i];
				for (const auto &t : temp.first)
					if (place[t.first] < t.second) {
						off = false;
						break;
					}
				if (off)
					break;
			}
			if (off) {
				for (const auto &t : temp.first)
					place[t.first] -= t.second;
				for (const auto &t : temp.second)
					place[t.first] += t.second;
			}
			else {
				sta = false;
				break;
			}
		}
		if (sta)
			printf("Case %d: still live after %d transitions\n", ++kase, nf);
		else
			printf("Case %d: dead after %d transitions\n", ++kase, cnt-1);
		printf("Places with tokens:");
		for (int i = 1; i <= np; i++)
			if (place[i])
				printf(" %d (%d)", i, place[i]);
		putchar('\n');
		putchar('\n');
	}
	return 0;
}