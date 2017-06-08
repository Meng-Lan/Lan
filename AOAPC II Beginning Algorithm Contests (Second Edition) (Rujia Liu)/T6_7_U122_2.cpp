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
Node node[maxn];
queue<Node*> freenodes;
Node *root;
bool failed = false;
void init() {
	for (int i = 0; i < maxn; i++)
		freenodes.push(&node[i]);
}
Node* new_node() {
	Node *u = freenodes.front();
	u->left = u->right = NULL;
	u->have_val = false;
	freenodes.pop();
	return u;
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
	freenodes.push(u);
}
void del_alltree(Node *u) {
	if (u == NULL)
		return;
	del_alltree(u->left);
	del_alltree(u->right);
	del_node(u);
}
bool read_input() {
	failed = false;
	del_alltree(root);
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
	init();
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