#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<sstream>
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
const int maxn = 20000 + 10;
int E[10];
vector<P> man;

bool cmp(const P &a, const P &b) {
	return a.first > b.first || a.first == b.first&&a.second <= b.second;
}

int main() {
	int n, k;
	scanf("%d%d", &n, &k);
	for (int i = 0; i < 10; i++)
		scanf("%d", E + i);
	int t;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &t);
		man.push_back(mp(t, i));
	}
	sort(man.begin(), man.end(),cmp);
	//for (auto &s : man)
	//	cout << s.first << "  " << s.second << endl;
	for (int i = 0; i < n; i++)
		man[i].first += E[i % 10];
	sort(man.begin(), man.end(),cmp);
	//for (auto &s : man)
	//	cout << s.first << "  " << s.second << endl;
	for (int i = 0; i < k; i++) {
		if (i) putchar(' ');
		printf("%d", man[i].second);
	}
	putchar('\n');
	return 0;
}