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

int A[10], cnt = 0;
vector<vector<int>> permu[7];
bool pic[5][9];
map<ll, bool> ans;

ll f(ll i) {
	return i > 1 ? i*f(i - 1) : 1;
}

ll c(ll n,ll r) {
	if (n - r < r) r = n - r;
	ll ansn = 1, ansr = 1;
	for (int i = n - r + 1; i <= n; ++i)
		ansn*=i;
	for (int j = 1; j <= r; ++j)
		ansr*=j;
	return ansn / ansr;
}

void permutation(vector<vector<int>> &t,int cur) {
	if (cur == cnt) {
		t.push_back(vector<int>(A, A + cnt));
	}
	else for (int i = 0; i < cnt; ++i) {
		int ok = 1;
		for (int j = 0; j < cur; ++j)
			if (A[j] == i) {
				ok = 0; break;
			}
		if (ok) {
			A[cur] = i;
			permutation(t,cur + 1);
		}
	}
}

ll draw(vector<int> &bit, vector<int> &p) {
	memset(pic, 0, sizeof(pic));
	for (auto &t : p) {
		int x = (bit[t] / 3 + 1), y = (bit[t] % 3) * 2;
		pic[x][y + 1] = pic[x][y + 2] = pic[x][y + 3] = pic[x + 1][y + 2] = false;
			pic[x - 1][y + 1] = pic[x][y] = true;
			pic[x - 1][y + 3] = pic[x][y + 4] = true;
			pic[x + 1][y] = pic[x + 1][y + 1] = true;
			pic[x + 1][y + 3] = pic[x + 1][y + 4] = true;
	}
	ll to_bit = 0;
	FOR(i, 5) FOR(j, 9) {
		to_bit <<= 1;
		if (pic[i][j])
			to_bit |= 1;
	}
	return to_bit;
}

int main() {
	for (int i = 1; i <= 6; ++i) {
		cnt = i;
		permutation(permu[i], 0);
	}
	int len = 1 << 9;
	for (int i = 1; i < len; ++i) {
		vector<int> bit; int temp = i; cnt = 0;
		for (int j = 0; temp; ++j) {
			if (temp & 1) {
				bit.push_back(j); ++cnt;
			}
			temp >>= 1;
		}
		if (cnt > 6) continue;
		for (auto &t : permu[cnt])
			ans[draw(bit, t)] = true;
	}
	string s[5];
	int kase = 0;
	while (getline(cin, s[0])) {
		if (s[0][0] == '0') break;
		for (int i = 1; i < 5; ++i) getline(cin, s[i]);
		printf("Case %d: ", ++kase);
		ll que = 0;
		FOR(i, 5) FOR(j, 9) {
			que <<= 1;
			if (s[i][j] != ' ')
				que |= 1;
		}
		if (ans.find(que) != ans.end())
			printf("Yes\n");
		else
			printf("No\n");
	}
	return 0;
}
/*
         #
 _ _ _   #
| |_ _|  #
|_|   |  #
  |_ _|  #
         #
   _ _   #
  |   |  #
  |_ _|  #
         #
 _ _ _ _ #
|_|_|_|_|#
|_|_|_|_|#
|_|_|_|_|#
|_|_|_|_|#
   _ _   #
 _|   |_ #
| |_ _| |#
|_|   |_|#
  |_ _|_|#
0
*/