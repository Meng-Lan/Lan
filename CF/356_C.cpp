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

const int pri[25] = { 2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97 };
const char *ans[2] = { "yes","no" };
const int composite[9] = { 25,35,49,55,65,77,85,91,95 };
bool two=false, three=false;
char in[5];

int main() {
	printf("2\n"); fflush(stdout);
	scanf("%s", in);
	if (strcmp(in, ans[0]) == 0) two = true;
	printf("3\n"); fflush(stdout);
	scanf("%s", in);
	if (strcmp(in, ans[0]) == 0) three = true;
	if (two&&three) {
		printf("composite\n"); fflush(stdout);
		return 0;
	}
	else if (two&&!three) {
		printf("4\n"); fflush(stdout);
		scanf("%s", in);
		if (strcmp(in, ans[0]) == 0) {
			printf("composite\n"); fflush(stdout);
			return 0;
		}
		else {
			for (int i = 2; i <= 14; ++i) {
				printf("%d\n", pri[i]); fflush(stdout);
				scanf("%s", in);
				if (strcmp(in, ans[0]) == 0) {
					printf("composite\n"); fflush(stdout);
					return 0;
				}
			}
			printf("prime\n"); fflush(stdout);
		}
	}
	else if (!two&&three) {
		printf("9\n"); fflush(stdout);
		scanf("%s", in);
		if (strcmp(in, ans[0]) == 0) {
			printf("composite\n"); fflush(stdout);
			return 0;
		}
		else {
			for (int i = 2; i <= 10; ++i) {
				printf("%d\n", pri[i]); fflush(stdout);
				scanf("%s", in);
				if (strcmp(in, ans[0]) == 0) {
					printf("composite\n"); fflush(stdout);
					return 0;
				}
			}
			printf("prime\n"); fflush(stdout);
		}
	}
	else {
		for (auto &t : composite) {
			printf("%d\n", t); fflush(stdout);
			scanf("%s", in);
			if (strcmp(in, ans[0]) == 0) {
				printf("composite\n"); fflush(stdout);
				return 0;
			}
		}
		printf("prime\n"); fflush(stdout);
	}
	return 0;
}