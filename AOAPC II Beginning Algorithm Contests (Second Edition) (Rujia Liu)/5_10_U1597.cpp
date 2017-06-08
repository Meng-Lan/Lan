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
#define pb push_back

const int maxn = 1505;
const int maxlen = 85;
char s[maxn][maxlen], t[maxn][maxlen];
int cnt = 0;
P doc[100];
vector<P> line[maxn];

bool find_str(int idx,const char *str,set<int> &ans) {
	int start = doc[idx].first, over = doc[idx].second,len=strlen(str);
	//cout << len << endl;
	bool off = false;
	for (int i = start; i < over;++i)
		for (int j = 0; j < line[i].size(); ++j) {
			if (line[i][j].second != len) continue;
			if (strcmp(t[i] + line[i][j].first, str) == 0) {
				ans.insert(i);
				//puts(s[i]);
				off = true;
				break;
			}
		}
	return off;
}

void print(set<int> &ans) {
	for (auto &i : ans)
		printf("%s", s[i]);
}

int main() {
	char c;
	int n;
	scanf("%d%c", &n, &c);
	for (int i = 0; i < n; ++i) {
		doc[i].first = cnt;
		while (fgets(s[cnt], maxlen, stdin)) {
			if (strcmp(s[cnt], "**********\n") == 0) {
				doc[i].second = cnt;
				break;
			}
			int len = strlen(s[cnt]);
			int temp = 0;
			for (int j = 0; j < len; ++j) {
				if (isalpha(s[cnt][j])) {
					t[cnt][j] = tolower(s[cnt][j]);
					++temp;
				}
				else {
					if (temp) line[cnt].pb(mp(j - temp, temp));
					temp = 0;
					t[cnt][j] = '\0';
				}
			}
			++cnt;
		}
	}
	int m;
	scanf("%d%c", &m, &c);
	for (int i = 0; i < m; ++i) {
		string str[3];
		getline(cin, str[0]);
		stringstream ss(str[0]);
		for (int j = 0; ss >> str[j]; ++j);
		int temp = 0;
		for (int j = 0; j < n; ++j) {
			set<int> ans;
			if (str[0].compare("NOT") == 0) {
				if (!find_str(j, str[1].c_str(), ans)) {
					if (temp) puts("----------");
					for (int k = doc[j].first; k < doc[j].second; ++k)
						printf("%s", s[k]);
					++temp;
				}
			}
			else if (str[1].compare("AND") == 0) {
				if (find_str(j, str[0].c_str(), ans) && find_str(j, str[2].c_str(), ans)) {
					if (temp) puts("----------");
					print(ans);
					++temp;
				}
			}
			else if (str[1].compare("OR") == 0) {
				bool t1 = find_str(j, str[0].c_str(), ans), t2 = find_str(j, str[2].c_str(), ans);
				if (t1 || t2) {
					if (temp) puts("----------");
					print(ans);
					++temp;
				}
			}
			else {
				if (find_str(j, str[0].c_str(), ans)) {
					if (temp) puts("----------");
					print(ans);
					++temp;
				}
			}
		}
		if (!temp) puts("Sorry, I found nothing.");
		puts("==========");
	}
	return 0;
}