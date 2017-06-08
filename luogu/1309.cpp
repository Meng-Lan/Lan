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
typedef pair<int, P> ppp;
#define mp make_pair
vector<ppp> vi;

bool cmp(const ppp &a, const ppp &b) {
	return a.second.first > b.second.first || a.second.first == b.second.first&&a.first < b.first;
}

int main() {
	int n, r, q;
	scanf("%d%d%d", &n, &r, &q);
	int len = 2 * n;
	vi.resize(len);
	for (int i = 0; i < len; i++)
		vi[i].first = i + 1;
	for (int i = 0; i < len; i++)
		scanf("%d", &vi[i].second.first);
	for (int i = 0; i < len; i++)
		scanf("%d", &vi[i].second.second);
	sort(vi.begin(), vi.end(), cmp);
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < n; j++) {
			if (vi[j << 1].second.second>vi[j << 1 | 1].second.second)
				++vi[j << 1].second.first;
			else
				++vi[j << 1 | 1].second.first;
			/*if (vi[j << 1].second.first < vi[j << 1 | 1].second.first || vi[j << 1].second.first == vi[j << 1 | 1].second.first
				&&vi[j << 1].first>vi[j << 1 | 1].first)
				swap(vi[j << 1], vi[j << 1 | 1]);*/
		}
		/*int change = 0;
		for (;;) {
			change = 0;
			for (int i = 0; i < len - 1; i++)
				if (vi[i].second.first < vi[i + 1].second.first || vi[i].second.first == vi[i + 1].second.first
					&&vi[i].first>vi[i + 1].first) {
					swap(vi[i], vi[i + 1]);
					++change;
				}
			if (!change)
				break;
		}*/
		sort(vi.begin(), vi.end(), cmp);
	}
	cout << vi[q - 1].first << endl;
	return 0;
}