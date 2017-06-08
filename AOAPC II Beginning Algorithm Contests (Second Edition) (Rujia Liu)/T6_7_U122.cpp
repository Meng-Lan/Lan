#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<new>
#include<queue>
#include<vector>
using namespace std;
const int maxn = 1 << 16;
char s[maxn];
struct Node {
	bool have_val;
	int val;
	Node *left, *right;
	Node() :have_val(false), left(NULL), right(NULL) {}
};
Node *root;
bool failed = false;
Node* new_node() {
	return new Node();
}
void addnode(int val, char *str) {
	int len = strlen(str);
	Node *u = root;
	for (int i = 0; i < len; i++)
		if (str[i] == 'L') {
			if (u->left == NULL)
				u->left = new_node();
			u = u->left;
		}
		else if (str[i] == 'R') {
			if (u->right == NULL)
				u->right = new_node();
			u = u->right;
		}
		if (u->have_val) failed = true;
		u->have_val = true;
		u->val = val;
}
void del_node(Node *u) {
	if (u == NULL) return;
	del_node(u->left);
	del_node(u->right);
	delete u;
}
bool read_input() {
	failed = false;
	del_node(root);
	root = new_node();
	for (;;) {
		if (scanf("%s", s) != 1) return false;
		if (!strcmp(s, "()")) break;
		int v;
		sscanf(s + 1, "%d", &v);
		addnode(v, strchr(s, ','));
	}
	return true;
}
bool bfs(vector<int> &ans) {
	queue<Node*> q;
	q.push(root);
	while (!q.empty()) {
		Node *u = q.front();
		q.pop();
		if (!u->have_val) return false;
		ans.push_back(u->val);
		if (u->left != NULL) q.push(u->left);
		if (u->right != NULL) q.push(u->right);
	}
	return true;
}
int main() {
	while (read_input()) {
		vector<int> ans;
		if (failed || !bfs(ans))
			printf("not complete\n");
		else {
			for (int i = 0; i < ans.size(); i++) {
				printf("%d", ans[i]);
				if (i != ans.size() - 1)
					putchar(' ');
			}
			putchar('\n');
		}
	}
	return 0;
}