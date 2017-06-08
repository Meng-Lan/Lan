#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<string>
#include<cstring>
#include<cctype>
#include<utility>
#include<cassert>
#include<cmath>
using namespace std;

#define FOR(i,n) for(int i=0;i<(n);i++)

const int maxn = 144;
const int n_cut = 70;
double eps = 1e-6;
double money[n_cut], totle;
int n;

struct Lan {
	char name[25];
	int rd[4], sc36, sc72, dq;
	int rnds;
	bool star;

	Lan operator =(string &s) {
		FOR(i, 20) name[i] = s[i];
		name[20] = 0;
		star = false;
		if (strchr(name,'*'))
			star = true;
		sc36 = sc72 = dq = rnds = 0;
		memset(rd, 0, sizeof(rd));
		FOR(i, 4) {
			char t[5];
			FOR(j, 3) t[j] = s[20 + i * 3 + j];
			t[3] = '\0';
			if (!(sscanf(t, "%d", &rd[i]))) {
				dq = -1;
				rnds = i;
				if (i < 2)
					sc36 = -1;
				break;
			}
			else {
				sc72 += rd[i];
				if (i < 2)
					sc36 += rd[i];
			}
		}
		return *this;
	}
	Lan() {
		memset(name, 0, sizeof(name));
		FOR(i, 4) rd[i] = 0;
		sc36 = sc72 = dq =rnds= 0;
		star = false;
	}
}lan[maxn];

void print_result() {
	printf("Player Name          Place     RD1  RD2  RD3  RD4  TOTAL     Money Won\n-----------------------------------------------------------------------\n");
	int i = 0, cnt = 0;
	while (i < n) {
		if (lan[i].dq) {
			printf("%s           ", lan[i].name);
			FOR(k, lan[i].rnds)
				printf("%-5d", lan[i].rd[k]);
			FOR(j, 4 - lan[i].rnds)
				printf("     ");
			printf("DQ\n");
			i++;
			continue;
		}
		int j = i, m = 0, top = i + 1;
		double tot = 0.0;
		bool have_money = false;
		while (j < n&&lan[i].sc72 == lan[j].sc72) {
			if (!lan[j].star) {
				m++;
				if (cnt < n_cut) {
					tot += money[cnt++];
					have_money = true;
				}
			}
			j++;
		}
		double totmoney = totle*tot / m;
		while (i < j) {
			printf("%s ", lan[i].name);
			char t[5];
			sprintf(t, "%d%c", top, (m>1 && have_money&& !lan[i].star) ? 'T' : ' ');
			printf("%-10s", t);
			FOR(k, 4)
				printf("%-5d", lan[i].rd[k]);
			if (!lan[i].star&&have_money) {
				printf("%-10d", lan[i].sc72);
				printf("$%9.2f\n", totmoney / 100.0);
			}
			else
				printf("%d\n", lan[i].sc72);
			i++;
		}
	}
}

int main() {
	int T;
	cin >> T;
	while (T--) {
		cin >> totle;
		FOR(i, 70) {
			cin >> money[i];
		}
		cin >> n;
		assert(n <= 144);
		string s;
		getline(cin, s);
		FOR(i, n) {
			getline(cin, s);
			lan[i] = s;
		}
		sort(lan, lan + n, [](const Lan& t1, const Lan& t2) {
			if (t1.sc36 < 0 && t2.sc36 < 0) return false;
			if (t1.sc36 < 0) return false;
			if (t2.sc36 < 0) return true;
			return t1.sc36 < t2.sc36; });
		//assert(lan[n_cut-1].sc36 >= 0);
		int len = 0;
		for (; len < n;len++)
			if (lan[len].sc36<0)
				break;
		if (len <= n_cut)
			n = len;
		else
			for (int i = n_cut-1; i < n; i++)
				if (i == n - 1 || lan[i].sc36 != lan[i + 1].sc36||lan[i].sc36<0) {
					n = i + 1;
					break;
				}
		sort(lan, lan + n, [](const Lan& t1, const Lan& t2) {
			if (t1.dq&&t2.dq) {
				if (t1.rnds != t2.rnds)return t1.rnds>t2.rnds;
				if(t1.sc72!=t2.sc72) return t1.sc72 < t2.sc72;
				return strcmp(t1.name,t2.name) < 0;
			}
			if (t1.dq) return false;
			if (t2.dq) return true;
			if (t1.sc72 != t2.sc72) return t1.sc72 < t2.sc72;
			return strcmp(t1.name,t2.name)< 0; });
		print_result();
		if(T) putchar('\n');
	}
	return 0;
}