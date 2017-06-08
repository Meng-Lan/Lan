#include<iostream>
#include<cstdio>
#include<algorithm>
#include<stack>
#include<new>
using namespace std;

struct Node {
	int val;
	Node *next;
	Node() :val(0), next(NULL) {}
	Node(int val) :val(val), next(NULL) {}
};

Node* new_node() {
	return new Node();
}

Node* Del_Node(Node *u) {
	if (u == NULL) return NULL;
	Node *v = u->next;
	delete u;
	return v;
}

void Each_List(Node *root) {
	Node *u = root;
	while (u != NULL) {
		printf("%d ", u->val);
		u = u->next;
	}
	putchar('\n');
	return;
}

Node* Marge_List(Node *first, Node *second) {
	Node *u = first, *v = second;
	Node *root;
	stack<Node*> s;
	while (u != NULL||v != NULL) {
		if (u != NULL&&v != NULL) {
			if (u->val <= v->val) {
				s.push(u);
				u = u->next;
			}
			else {
				s.push(v);
				v = v->next;
			}
		}
		else if (u != NULL) {
			s.push(u);
			u = u->next;
		}
		else if (v != NULL) {
			s.push(v);
			v = v->next;
		}
	}
	if (!s.empty()) {
		root = s.top();
		s.pop();
	}
	Node *t = root;
	while (!s.empty()) {
		t->next = s.top();
		t = t->next;
		s.pop();
	}
	t->next = NULL;
	return root;
}
int main() {
	int n, m, val;
	cin >> n >> m;
	Node *first = new_node(), *u = first;
	for (int i = 0; i < n; i++) {
		cin >> val;
		u->val = val;
		if (i != n - 1) {
			u->next = new_node();
			u = u->next;
		}
	}
	Node *second = new_node();
	u = second;
	for (int i = 0; i < m; i++) {
		cin >> val;
		u->val = val;
		if (i != m - 1) {
			u->next = new_node();
			u = u->next;
		}
	}
	Node *root;
	root = Marge_List(first, second);
	Each_List(root);
	return 0;
}