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

struct Lan {
	int chinese, math, english,id,sum;
};
vector<Lan> stu;

bool cmp(const Lan &a, const Lan &b) {
	return a.sum > b.sum || a.sum == b.sum&&a.chinese > b.chinese ||
		a.sum == b.sum&&a.chinese == b.chinese&&a.id < b.id;
}

int main() {
	int n;
	scanf("%d", &n);
	Lan t;
	for (int i = 0; i < n; i++) {
		scanf("%d%d%d", &t.chinese, &t.math, &t.english);
		t.id = i + 1;
		t.sum = t.chinese + t.math + t.english;
		stu.push_back(t);
	}
	sort(stu.begin(), stu.end(), cmp);
	for (int i = 0; i < 5; i++)
		printf("%d %d\n", stu[i].id, stu[i].sum);
	return 0;
}