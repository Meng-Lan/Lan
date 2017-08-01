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
	if (n-r < r) r=n-r;
	ll ansn=1,ansr=1;
	for (ll i=n-r+1; i<=n; ++i) ansn*=i;
	for (ll j=1; j<=r; ++j) ansr*=j;
	return ansn/ansr;
}
ll gcd(ll a,ll b) { return b?gcd(b,a%b):a; }
ll lcm(ll a,ll b) { return a/gcd(a,b)*b; }
std::vector<int> Eratosthenes(const int len,int *vis) {
	memset(vis,0,sizeof(int)*len);
	std::vector<int> prime;
	int m=(int)sqrt(len+0.5);
	For(i,2,m) if (!vis[i]) for (int j=i*i; j < len; j+=i) vis[j]=1;
	FOR(i,2,len) if (!vis[i]) prime.push_back(i);
	return prime;
}
void phi_table(int n,int *phi) {
	For(i,2,n) phi[i]=0;
	phi[1]=1;
	For(i,2,n) if (!phi[i])
		for (int j=i; j<=n; j+=i) {
			if (!phi[j]) phi[j]=j;
			phi[j]=phi[j]/i*(i-1);
		}
}

struct Node {
	int v,s,flip;
	Node *ch[2];
	int cmp(int k) {
		int d=k-ch[0]->s;
		if (d==1) return -1;
		return d<=0?0:1;
	}
	void maintain() { s=ch[0]->s+ch[1]->s+1; }
	void pushdown() {
		if (flip) {
			flip=0;
			std::swap(ch[0],ch[1]);
			ch[0]->flip^=1;
			ch[1]->flip^=1;
		}
	}
};

Node *null=new Node();

void rotate(Node *&o,int d) {
	Node *k=o->ch[d^1];o->ch[d^1]=k->ch[d];k->ch[d]=o;o->maintain();k->maintain();o=k;
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

Node* merge(Node *left,Node *right) {
	//printf("s:%d\n",left->s);
	splay(left,left->s);
	left->ch[1]=right;
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

const int maxn=1e5+10;
struct SplaySequence {
	int n;
	Node seq[maxn],*root;

	Node* build(int sz) {
		if(!sz) return null;
		Node *L=build(sz/2);
		Node *o=&seq[++n];
		o->v=n;
		o->ch[0]=L;
		o->ch[1]=build(sz-sz/2-1);
		o->s=o->flip=0;
		o->maintain();
		return o;
	}

	void init(int sz) {
		n=0;
		null->s=0;
		root=build(sz);
	}
};

std::vector<int> ans;
void print(Node *o) {
	if(o!=null) {
		o->pushdown();
		print(o->ch[0]);
		ans.push_back(o->v);
		print(o->ch[1]);
	}
}

void debug(Node* o) {
	if(o!=null) {
		o->pushdown();
		debug(o->ch[0]);
		printf("%d ",o->v-1);
		debug(o->ch[1]);
	}
}

SplaySequence ss;
int n,m;

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	scanf("%d%d",&n,&m);
	ss.init(n+1);
	while(m--) {
		int a,b;scanf("%d%d",&a,&b);
		Node *left,*right,*mid,*o;
		split(ss.root,a,left,o);
		split(o,b-a+1,mid,right);
		mid->flip^=1;
		ss.root=merge(merge(left,right),mid);
		//debug(ss.root);puts("");
	}

	print(ss.root);
	FOR(i,1,ans.size()) printf("%d\n",ans[i]-1);

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}