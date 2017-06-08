#include<cstdio>
#include<iostream>
#include<vector>
#include<string>
using namespace std;

const int maxn = 30;
int n;
vector<int> pile[maxn];

void find(int a, int& p, int& h) {
	for (p = 0; p < n; p++)
		for (h = 0; h < pile[p].size(); h++)
			if (pile[p][h] == a)
				return;
}

void clear(int p, int h) {
	for (size_t i = h + 1; i < pile[p].size(); i++)
		pile[pile[p][i]].push_back(pile[p][i]);
	pile[p].resize(h + 1);
}

void pile_onto(int p, int h, int p2) {
	for (size_t i = h; i < pile[p].size(); i++)
		pile[p2].push_back(pile[p][i]);
	pile[p].resize(h);
}

int main() {
	int a, b;
	cin >> n;
	string s1, s2;
	for (int i = 0; i < n; i++)
		pile[i].push_back(i);
	while (cin >> s1 >> a >> s2 >> b) {
		if (s1 == "quit") break;
		int pa, pb, ha, hb;
		find(a, pa, ha);
		find(b, pb, hb);
		if (pa == pb) continue;
		if (s2 == "onto") clear(pb, hb);
		if (s1 == "move") clear(pa, ha);
		pile_onto(pa, ha, pb);
	}
	for (int i = 0; i < n; i++) {
		printf("%d:", i);
		for (size_t j = 0; j < pile[i].size(); j++)
			printf(" %d", pile[i][j]);
		putchar('\n');
	}
	return 0;
}