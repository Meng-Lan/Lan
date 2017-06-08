#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
/*記錄下題意，猜題意也用了半小時= =淚
/輸入的x1 x2 x3（或x3 x1 x2） 表示取x的先後，意思就是二叉樹從頂到底各個分支的xn的順序
/輸入的如0100 (x1,x2--xn）表示xn的值，n從1開始
*/
using namespace std;
const int maxn = 8;
#define lson (rt<<1)
#define rson (rt<<1|1)
int x[maxn];
string ans, s,temp;
int main() {
	int n, m, kase = 0;
	while (scanf("%d", &n) == 1&&n) {
		printf("S-Tree #%d:\n", ++kase);
		for (int i = 0; i < n; i++) {
			cin >> s;
			x[i] = s[1] - '1';
		}
		cin >> temp >> m;
		ans.clear();
		for (int i = 0; i < m; i++) {
			cin >> s;
			int rt = 0;
			for (int j = 0; j < s.size(); j++)
				if (s[x[j]]-'0')
					rt = rson;
				else
					rt = lson;
			ans.push_back(temp[rt]);
		}
		cout << ans << endl << endl;
	}
	return 0;
}