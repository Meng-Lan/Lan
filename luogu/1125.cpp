#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
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
const int maxn = 105;
int ch[26];
int pri[maxn];
bool is_prime(int n) {
	if (n < 2) return false;
	for (int i = 2; i*i <= n; i++)
		if (n%i==0)
			return false;
	return true;
}

int main() {
	for (int i = 1; i < maxn; i++)
		if (is_prime(i))
			pri[i] = true;
	string s;
	cin >> s;
	for (int i = 0; i < s.size(); i++)
		ch[s[i] - 'a']++;
	int Min=maxn, Max=0;
	for (int i = 0; i < 26; i++)
		if (ch[i]) {
			Min = min(Min, ch[i]);
			Max = max(Max, ch[i]);
		}
	if (pri[Max - Min]) {
		printf("Lucky Word\n");
		printf("%d\n", Max - Min);
	}
	else
		printf("No Answer\n0\n");
	return 0;
}