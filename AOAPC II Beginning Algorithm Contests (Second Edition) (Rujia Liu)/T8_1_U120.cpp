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
#define FOR(i,len) for(int i=0;i<(len);++i)
#define For(i,len) for(int i=0;i<=(len);++i)
#define rep(i,init,len) for(int i=(init);i<(len);++i)
#define mp make_pair
ll Factorial(ll i) { return i > 1 ? i*Factorial(i - 1) : 1; }

ll Combination(ll n, ll r) {
	if (n - r < r) r = n - r;
	ll ansn = 1, ansr = 1;
	for (int i = n - r + 1; i <= n; ++i) ansn *= i;
	for (int j = 1; j <= r; ++j) ansr *= j;
	return ansn / ansr;
}

vector<int> vi,now;

void rever(vector<int> &t, int k) {
	queue<int> q;
	for (int i = 0; i <= vi.size() - k; ++i)
		q.push(vi[i]);
	for (int i = vi.size() - k; i >= 0; --i) {
		vi[i] = q.front(); q.pop();
	}
}

int main() {
	string s;
	while (getline(cin, s)) {
		cout << s << endl;
		stringstream ss(s); vi.clear();
		int tmp;
		while (ss >> tmp)
			vi.push_back(tmp);
		now = vi;
		sort(now.begin(), now.end());
		/*for (auto &t : now)
			cout << t << ' ';
		cout << endl;*/
		for (int i = vi.size() - 1; i >= 0;--i)
			if (now[i] != vi[i]) {
				int find = 0;
				for (; vi[find] != now[i]; ++find);
				if (find != 0) {
					rever(vi, vi.size() - find);
					printf("%d ", vi.size() - find);
				}
				rever(vi, vi.size() - i);
				printf("%d ", vi.size() - i);
			}
		printf("0\n");
	}
	return 0;
}