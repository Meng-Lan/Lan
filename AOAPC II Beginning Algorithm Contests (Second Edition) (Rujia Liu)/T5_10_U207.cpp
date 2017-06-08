#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<string>
#include<cstring>
#include<cctype>
using namespace std;
double money[100];
int n;
struct Lan {
	string name;
	int rd[4];
	int sum[2];
	bool star = 0;
	int isdq=0;
	int top=0;
	bool dt = 0;
	double money = 0.0;

	int findnum(string &s,int i) {
		for (; i < s.length(); i++)
			if (s[i] >= '0'&&s[i] <= '9')
				return i;
		return false;
	}
	bool findx(string &s) {
		for (int i = 0; i < s.length(); i++)
			if (s[i] == '*')
				return true;
		return false;
	}
	int getint(string &s, int &begin) {
		int i = s[begin++] - '0';
		for (; s[begin] >= '0'&&s[begin] <= '9';)
			i = i * 10 + s[begin++] - '0';
		return i;
	}
	void Lan_new(string &s) {
		if (findx(s))
			star = true;
		name.resize(21);
		for (int i = 0; i < 20; i++)
			name[i] = s[i];
		s[20] = '\0';
		for (int i = 0; i < 4; i++) {
			int temp = findnum(s, 20 + 3 * i);
			if (!temp) {
				isdq = i + 1;
				break;
			}
			rd[i] = getint(s,temp);
		}
		if (isdq)
			sum[0] = sum[1] = 0;
		else {
			sum[0] = rd[0] + rd[1];
			sum[1] = sum[0] + rd[2] + rd[3];
		}
	}
	Lan* operator =(string &s) {
		this->Lan_new(s);
		return this;
	}
	Lan() {
		name = "NULL";
		rd[0] = rd[1] = rd[2] = rd[3] = 0;
		sum[0] = sum[1] = 0;
		isdq = top = 0;
		star = false;
	}
}lan[150];
ostream& operator << (ostream &out,const Lan &temp) {
	out << temp.name;
	if (temp.isdq) {
		printf("          ");
		for (int i = 0; i < temp.isdq-1; i++)
			printf("%-5d", temp.rd[i]);
		for (int i = temp.isdq-1; i < 4; i++)
			printf("     ");
		printf("DQ\n");
	}
	else {
		char t[5] = { 0 };
		sprintf(t, "%d%c", temp.top, temp.dt ? 'T' : ' ');
		printf("%-10s", t);
		for (int i = 0; i < 4; i++)
			printf("%-5d", temp.rd[i]);
		if (!temp.star&&temp.money>0) {
			printf("%-10d", temp.sum[1]);
			printf("$%9.2lf\n", temp.money);
		}
		else
			printf("%d\n", temp.sum[1]);
	}
	return out;
}
void calplace(int s) {
	int left = 0, right = 0, len = 0, top = 0, rd = -1;
	for (int i = 0; i < n; i++)
		lan[i].dt = false;
	for (int i = 0; i < n; i++) {
		if (lan[i].isdq)
			return;
		if (lan[i].sum[s] != rd) {
			right = i;
			if (len > 1)
				for (int j = left; j < right; j++)
					if (!lan[j].star) 
						lan[j].dt = true;
			lan[i].top = top = i + 1;
			left = i;
			if (lan[i].star)
				len = 0;
			else
				len = 1;
			rd = lan[i].sum[s];
		}
		else {
			lan[i].top = top;
			if (!lan[i].star)
				len++;
		}
	}
	return;
}
int main() {
	int T;
	cin >> T;
	while (T--) {
		for (int i = 0; i < 71; i++) {
			scanf("%lf", money + i);
		}
		cin >> n;
		string s;
		getline(cin, s);
		for (int i = 0; i < n; i++) {
			getline(cin, s);
			lan[i].Lan_new(s);
		}
		//printf("Player Name          Place     RD1  RD2  RD3  RD4  TOTAL     Money Won\n-----------------------------------------------------------------------\n");
		sort(lan, lan + n, [](const Lan &t1, const Lan &t2) {
			if (t1.isdq && (!t2.isdq)) return false;
			if ((!t1.isdq) && t2.isdq) return true;
			if (t1.isdq&&t2.isdq) {
				if (t1.isdq != t2.isdq) return t1.isdq > t2.isdq;
				if (t1.isdq == 1) return t1.rd[0] < t2.rd[0];
				if (t1.isdq == 2) return (t1.rd[0]+t1.rd[1]) < (t2.rd[0]+t2.rd[1]);
				if (t1.isdq == 3) return (t1.rd[0] + t1.rd[1] + t1.rd[2]) < (t2.rd[0] + t2.rd[1] + t2.rd[2]);
				/*if (t1.rd[0] != t2.rd[0]) return t1.rd[0] < t2.rd[0];
				if (t1.rd[1] != t2.rd[1]) return t1.rd[1] < t2.rd[1];
				if (t1.rd[2] != t2.rd[2]) return t1.rd[2] < t2.rd[2];*/
			}
			return t1.sum[0] < t2.sum[0]; });
		calplace(0);
		/*for (int i = 0; i < n; i++)
			cout << lan[i];*/
		int find70 = 0;
		for (int i = 0; i < n; i++)
			if ((!lan[i].top) || lan[i].top == 71)
				break;
			else
				find70++;
		printf("Player Name          Place     RD1  RD2  RD3  RD4  TOTAL     Money Won\n-----------------------------------------------------------------------\n");
		sort(lan,lan+find70, [](const Lan &t1, const Lan &t2) {
			if (t1.isdq && (!t2.isdq)) return false;
			if ((!t1.isdq) && t2.isdq) return true;
			if (t1.isdq&&t2.isdq) {
				if (t1.isdq != t2.isdq) return t1.isdq > t2.isdq;
				if (t1.isdq == 1) return t1.rd[0] < t2.rd[0];
				if (t1.isdq == 2) return (t1.rd[0] + t1.rd[1]) < (t2.rd[0] + t2.rd[1]);
				if (t1.isdq == 3) return (t1.rd[0] + t1.rd[1] + t1.rd[2]) < (t2.rd[0] + t2.rd[1] + t2.rd[2]);
				/*if (t1.rd[0] != t2.rd[0]) return t1.rd[0] < t2.rd[0];
				if (t1.rd[1] != t2.rd[1]) return t1.rd[1] < t2.rd[1];
				if (t1.rd[2] != t2.rd[2]) return t1.rd[2] < t2.rd[2];*/
			}
			return t1.sum[1] < t2.sum[1]; });
		calplace(1);
		find70 = 0; 
		for (int i = 0; i < n; i++)
			if ((!lan[i].top) || lan[i].top == 71)
				break;
			else
				find70++;
		int left = 0, right = 0, rd = -1,ym=0,cnt=0;
		double m = 0.0;
		for (int i = 0; i < find70;i++)
			if (lan[i].sum[1] != rd) {
				right = i;
				if (right - left > 1) {
					for (int j = left; j < right; j++)
						if (!lan[j].star) {
							m += money[cnt++];
							ym++;
						}
					for (int j = left; j < right; j++)
						if (!lan[j].star)
							lan[j].money = (m*money[0] / 100) / ym;
					m = 0.0;
				}
				else if (!lan[left].star)
					lan[left].money = (money[0] * money[cnt++]) / 100;
				left = i;
				rd = lan[i].sum[1];
			}
		for (int i = 0; i < n; i++)
			if (lan[i].isdq>2||!lan[i].isdq)
				cout << lan[i];
			else
				break;
	}
	return 0;
}
/*
1
4
WALLY WEDGE 70 70 70 70
SANDY LIE 80 DQ
SID SHANKER* 90 99 62 61
JIMMY ABLE 69 73 80 DQ
*/
