#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
/*ӛ����}�⣬���}��Ҳ���˰�С�r= =�I
/ݔ���x1 x2 x3����x3 x1 x2�� ��ʾȡx�����ᣬ��˼���Ƕ�����픵��׸�����֧��xn�����
/ݔ�����0100 (x1,x2--xn����ʾxn��ֵ��n��1�_ʼ
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