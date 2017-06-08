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
const int maxn = 1e6 + 10;
int num[maxn];
struct Node {
	int val;
	Node *left, *right;
	Node(int val = 0) :val(val), left(NULL), right(NULL) {}
};
void build(int val, Node *v) {
	while (v) {
		if (val > v->val) {
			if (v->right == NULL) {
				printf("%d", v->val);
				v->right = new Node;
				v->right->val = val;
				return;
			}
			else
				v = v->right;
		}
		else {
			if (v->left == NULL) {
				printf("%d", v->val);
				v->left = new Node;
				v->left->val = val;
				return;
			}
			else
				v = v->left;
		}
	}
}
int main() {
	int n;
	scanf("%d%d", &n, num + 0);
	Node *root = new Node;
	root->val = num[0];
	for (int i = 1; i < n; i++) {
		scanf("%d", num + i);
		build(num[i], root);
		if (i != n - 1)
			putchar(' ');
	}
	putchar('\n');
	return 0;
}