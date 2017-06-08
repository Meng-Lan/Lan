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
typedef unsigned int ui;
typedef pair<int, int> P;
typedef pair<P, int> pi;
#define FOR(i,len) for(int i=0;i<(len);++i)
#define For(i,len) for(int i=0;i<=(len);++i)
#define rep(i,init,len) for(int i=(init);i<(len);++i)
#define mp make_pair

char a[4], b[4], c[6], buf[14];
const int Min[] = { 0,1,10,100,1000 }, Max[] = { 0,9,99,999,9999 };
vector<string> vs;
int MIN;
map<ui,int> ms;
string ans,tmp;
ui ansh;

inline bool check(int val, int bit) {
	return val >= Min[bit] && val <= Max[bit];
}

inline ui h(const string &s) {
	ui h = 0;
	for (int i = 0; i < s.size(); ++i) {
		ui t = s[i] == '*' ? 0 : s[i] - '0'+1;
		h = h << 4 | t;
	}
	return h;
}

int main() {
	int kase = 0;
	while (scanf("%s %s %s", a, b, c) == 3) {
		vs.clear(); MIN = 10; ans.clear();
		sprintf(buf, "%s%s%s", a, b, c);
		string s(buf); ui sh = h(s);
		printf("Case %d: ", ++kase);
		int la = strlen(a), lb = strlen(b), lc = strlen(c);
		for (int i = Min[la]; i <= Max[la]; i++)
			for (int j = Min[lb]; j <= Max[lb]; ++j) {
				int k = i*j;
				if (check(k, lc)) {
					sprintf(buf, "%d%d%d", i, j, k);
					vs.push_back(buf);
				}
			}
		int llen = la + lb + lc;
		int len = 1 << llen;
		//cout << len << endl;
		for (int i = 0; i < len; ++i) {
			ms.clear();
			vector<int> bit;
			int temp = i;
			for (int j = 0; temp; j++) {
				if (temp & 1) bit.push_back(j);
				temp >>= 1;
			}
			for (auto &t : vs) {
				tmp.assign(t.size(), '*');
				for (const auto &tp : bit)
					tmp[tp] = t[tp];
				ui hh = h(tmp);
				++ms[hh];
			}
			for (auto &t : ms)
				if (t.second == 1) {
					int diff = 0;
					for (int j = 0; j < llen; ++j)
						if ((t.first >> (j * 4) & 15) != (sh >> (j * 4) & 15))
							++diff;
					if (diff < MIN) {
						ansh = t.first;
						MIN = diff;
					}
					else if (diff == MIN&&t.first < ansh)
						ansh = t.first;
				}
		}
		for (int i = llen - 1; i >= 0; --i)
			if (ansh >> (i * 4) & 15)
				ans.push_back('0' + (ansh >> (i * 4) & 15) - 1);
			else
				ans.push_back('*');
		for (int i = 0; i < la; ++i)
			putchar(ans[i]);
		putchar(' ');
		for (int i = la; i < la + lb; ++i)
			putchar(ans[i]);
		putchar(' ');
		for (int i = la + lb; i < llen; ++i)
			putchar(ans[i]);
		putchar('\n');
	}
	return 0;
}