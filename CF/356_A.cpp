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

int in[5];
int num[200];
int sum = 0;

int main() {
	for (int i = 0; i < 5; ++i) {
		scanf("%d", in + i);
		sum += in[i];
	}
	for (int i = 0; i < 5; ++i)
		++num[in[i]];
	int Min = sum;
	for (int i = 1; i <= 100; ++i)
		if (num[i] >= 2) {
			int t = min(num[i], 3);
			Min = min(Min, sum - i*t);
		}
	printf("%d\n", Min);
	return 0;
}