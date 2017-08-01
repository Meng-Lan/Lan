#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<sstream>
#include<fstream>
#include<vector>
#include<list>
#include<deque>
#include<stack>
#include<queue>
#include<map>
#include<set>
#include<cmath>
#include<utility>
#include<numeric>
#include<iterator>
#include<algorithm>
#include<functional>
#include<ctime>
#include<cassert>
using std::cin;
using std::cout;
using std::endl;
typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<int,int> P;
#define FOR(i,init,len) for(int i=(init);i<(len);++i)
#define For(i,init,len) for(int i=(init);i<=(len);++i)
#define mp std::make_pair
ll Factorial(ll i) { return i > 1?i*Factorial(i-1):1; }
ll Combination(ll n,ll r) {
	if(n-r < r) r=n-r;
	ll ansn=1,ansr=1;
	for(ll i=n-r+1; i<=n; ++i) ansn*=i;
	for(ll j=1; j<=r; ++j) ansr*=j;
	return ansn/ansr;
}
ll gcd(ll a,ll b) { return b?gcd(b,a%b):a; }
ll lcm(ll a,ll b) { return a/gcd(a,b)*b; }
std::vector<int> Eratosthenes(const int len,int *vis) {
	memset(vis,0,sizeof(int)*len);
	std::vector<int> prime;
	int m=(int)sqrt(len+0.5);
	For(i,2,m) if(!vis[i]) for(int j=i*i; j < len; j+=i) vis[j]=1;
	FOR(i,2,len) if(!vis[i]) prime.push_back(i);
	return prime;
}
void phi_table(int n,int *phi) {
	For(i,2,n) phi[i]=0;
	phi[1]=1;
	For(i,2,n) if(!phi[i])
		for(int j=i; j<=n; j+=i) {
			if(!phi[j]) phi[j]=j;
			phi[j]=phi[j]/i*(i-1);
		}
}

struct Node {
	int s,flip;
	Node *ch[2],*fa;
	int cmp(int x) { x-=ch[0]->s;if(x==1) return -1;return x<=0?0:1; }
	int cmp(std::stack<Node*> &path) { if(path.empty()) return -1;Node *p=path.top();path.pop();return p==ch[0]?0:1; }
	void maintain() { s=ch[0]->s+ch[1]->s+1; }
	void pushdown() {
		if(flip) {
			flip=0;
			std::swap(ch[0],ch[1]);
			ch[0]->flip^=1;ch[1]->flip^=1;
		}
	}
};

Node *null=new Node();

void rotate(Node *&o,int d) {
	Node *k=o->ch[d^1];o->ch[d^1]=k->ch[d];o->ch[d^1]->fa=o;k->fa=o->fa;k->ch[d]=o;o->fa=k;o->maintain();k->maintain();o=k;
}

void splay(Node *&o,int k) {
	o->pushdown();
	int d=o->cmp(k);
	if(d==1) k-=o->ch[0]->s+1;
	if(d!=-1) {
		Node *p=o->ch[d];
		p->pushdown();
		int d2=p->cmp(k);
		int k2=(d2==0?k:k-p->ch[0]->s-1);
		if(d2!=-1) {
			splay(p->ch[d2],k2);
			if(d==d2) rotate(o,d^1);else rotate(o->ch[d],d);
		}
		rotate(o,d^1);
	}
}

void splay(Node *&o,std::stack<Node*> &path) {
	o->pushdown();
	int d=o->cmp(path);
	if(d!=-1) {
		Node *p=o->ch[d];
		p->pushdown();
		int d2=p->cmp(path);
		if(d2!=-1) {
			splay(p->ch[d2],path);
			if(d==d2) rotate(o,d^1);else rotate(o->ch[d],d);
		}
		rotate(o,d^1);
	}
}

Node* merge(Node *left,Node *right) {
	splay(left,left->s);
	left->ch[1]=right;
	right->fa=left;
	left->maintain();
	return left;
}

void split(Node *o,int k,Node *&left,Node *&right) {
	splay(o,k);
	left=o;
	right=o->ch[1];
	o->ch[1]=null;
	left->maintain();
}

void debug(Node* o) {
	if(o!=null) {
		o->pushdown();
		debug(o->ch[0]);
		printf("now:%d fa:%d left:%d right:%d\n",o,o->fa,o->ch[0],o->ch[1]);
		debug(o->ch[1]);
	}
}

const int maxn=1e5+10;
struct SplaySequence {
	struct Lan {
		int id,v;
		bool operator<(const Lan &rhs)const { return v<rhs.v||v==rhs.v&&id<rhs.id; }
	}in[maxn];
	int n;
	Node seq[maxn],*root;

	Node* build(int sz) {
		if(!sz) return null;
		Node *L=build(sz/2);
		Node *o=&seq[++n];
		o->ch[0]=L;
		o->ch[1]=build(sz-sz/2-1);
		o->ch[0]->fa=o->ch[1]->fa=o;
		o->s=o->flip=0;
		o->maintain();
		return o;
	}

	void init(int sz) {
		n=0;null->s=0;
		root=build(sz);root->fa=root;
		For(i,1,sz) { scanf("%d",&in[i].v);in[i].id=i; }
		std::sort(in+1,in+1+n);
	}

	void getpath(std::stack<Node*> &path,Node *u) {
		if(u!=root) { path.push(u);getpath(path,u->fa); }
	}

	void solve() {
		//printf("null addrsss:%d\n",null);
		//For(i,1,n) printf("v:%d id:%d address:%d\n",in[i].v,in[i].id,&seq[in[i].id]);
		For(i,1,n) {
			std::stack<Node*> s;
			getpath(s,&seq[in[i].id]);//puts("getpath");
			//printf("root:%d\n",root);
			//debug(root);
			//std::stack<Node*> t=s;
			//while(!t.empty()) { printf("address:%d\n",t.top());t.pop(); }
			splay(root,s);//puts("splay");
			printf("%d%c",(root->ch[0]==null?0:root->ch[0]->s)+i,i==n?'\n':' ');
			if(root->ch[0]==null) {
				root=root->ch[1];root->fa=root;
			}
			else {
				Node *left,*mid,*right,*o;
				split(root,root->ch[0]->s,left,o);//puts("#1");
				split(o,1,mid,right);//puts("#2");
				left->flip^=1;
				root=merge(left,right);//puts("#3");
				root->fa=root;
			}
		}
	}
}ss;
int n;

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	while(scanf("%d",&n)==1&&n) {
		ss.init(n);
		ss.solve();
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}