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

string s;
vector<vector<int>> vi[9];
int cnt, A[10], over,num[10];
const char *sign="+-*/";

bool check(vector<int> &sign) {
	stack<int> si;

}

void dfs(int bgn,int cur) {
	if (cur == over+1) {
		A[cur] = cnt;
		for (int i = 0; i < over; ++i)
			if (s[A[i]] != '0')
				sscanf(s.substr(s[A[i]], A[i + 1] - A[i]).c_str(), "%d", num[i]);
			else
				return;
		for (auto &t : vi[over]) {
			
		}
	}
	else {
		for (int i = bgn; i < cnt; ++i) {
			A[cur] = i;
			dfs(i+1, cur + 1);
		}
	}
}

int main() {
	for (int i = 0; i < 9; ++i) {
		int len = 1 << (i * 2);
		cout << len << endl;
		for (int j = 0; j < len; ++j) {
			int temp = j;
			for (int k = 0; temp; ++k) {
				A[k] = temp & 3;
				temp >>= 2;
			}
			vi[i].push_back(vector<int>(A,A+i));
		}
	}
	while (getline(cin, s) && s[0] != '=') {
		cnt = s.size() - 1;
		int num=0;
		sscanf(s.substr(0, cnt).c_str(), "%d", &num);
		if (num == 2000) printf("2000\n");
		for (int i = 1; i < cnt; ++i) {
			over = i; A[0] = 0;
			dfs(1, 1);
		}
	}
	return 0;
}