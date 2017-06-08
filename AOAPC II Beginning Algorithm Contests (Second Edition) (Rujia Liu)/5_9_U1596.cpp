#include<iostream>
#include<cstdio>
#include<string>
#include<string.h>
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

const int maxc = 26*2;
const int maxn = 88;
int val[maxc],num;
map<int, int> m[maxc];
char line[maxn],ch;

int get_id(char c) {
	return (islower(c)) ? c - 'a' : c - 'A' + 26;
}

bool check(int id, int v) {
	//int id = get_id(ch);
	if (val[id]==-1||v >= val[id] || v < 0) return false;
	else if (m[id].find(v) == m[id].end()) return false;
	return true;
}

int get_num(char *s) {
	if (isalpha(*s)) {
		int id = get_id(*s);
		int num = get_num(s + 2);
		if (check(id, num)) return m[id][num];
		else return -1;
	}
	else {
		int num = 0;
		while (*s != '\0' && *s != '\n' && *s != ']') {
			num = num * 10 + (*s - '0');
			++s;
		}
		return num;
	}
}

int main() {
	while (fgets(line, maxn, stdin) && strcmp(line, ".\n") != 0) {
		memset(val, -1, sizeof(val));
		for (auto &t : m)
			t.clear();
		int off = true;
		int count = 0;
		do {
			if (strchr(line, '=') == NULL) {
				sscanf(line, "%c[%d]", &ch, &num);
				val[get_id(ch)] = num;
				++count;
			}
			else {
				char *eq = strchr(line, '=');
				int right = get_num(eq + 1);
				int left = get_num(line + 2);
				int id = get_id(*line);
				++count;
				if (val[id] == -1 || left >= val[id] || left < 0 || right == -1) {
					printf("%d\n", count);
					off = false;
					break;
				}
				else
					m[id][left] = right;
				//cout << left << "**" << right << endl;
			}
		} while (off&&fgets(line, maxn, stdin) && strcmp(line, ".\n") != 0);
		if (!off) while (fgets(line, maxn, stdin) && strcmp(line, ".\n") != 0);
		else puts("0");
		//for (auto &t : val)
		//	cout << t << endl;
	}
	return 0;
}