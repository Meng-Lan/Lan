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
	int v,r,s;
	Node *ch[2];
	Node(int v=0) :v(v) { ch[0]=ch[1]=NULL;s=1;r=rand(); }
	bool operator<(const Node &rhs)const { return r<rhs.r; }
	int cmp(int x) { if (x==v) return -1;return x<v?0:1; }
	void maintain() {
		s=1;
		if (ch[0]!=NULL) s+=ch[0]->s;
		if (ch[1]!=NULL) s+=ch[1]->s;
	}
};

void rotate(Node *&o,int d) {
	Node *k=o->ch[d^1];o->ch[d^1]=k->ch[d];k->ch[d]=o;o->maintain();k->maintain();o=k;
}

void insert(Node *&o,int x) {
	//printf("1# o:%d\n",o);
	if (o==NULL) o=new Node(x);
	else {
		int d=o->v>x?0:1;
		//printf("2# o:%d d:%d\n",o,d);
		insert(o->ch[d],x);
		if (o->ch[d]->r>o->r) rotate(o,d^1);
	}
	//printf("3# o:%d\n",o);
	o->maintain();
}

void remove(Node *&o,int x) {
	int d=o->cmp(x);
	//printf("#o:%d lo:%d ro:%d\n",o,o->ch[0],o->ch[1]);
	//printf("o:%d o->v:%d x:%d d:%d o->ch[d]:%d \n",o,o->v,x,d,o->ch[d]);
	if (d==-1) {
		if (o->ch[0]!=NULL&&o->ch[1]!=NULL) {
			int d2=o->ch[0]->r>o->ch[1]->r?1:0;
			rotate(o,d2);remove(o->ch[d2],x);
		}
		else {
			Node *u=o;
			if (o->ch[0]==NULL) o=o->ch[1];else o=o->ch[0];
			delete u;
		}
	}
	else remove(o->ch[d],x);
	if (o!=NULL) o->maintain();
}

const int maxc=5e5+10;
struct Command {
	char type;
	int x,p;
	Command(char type,int x,int p) :type(type),x(x),p(p) {}
	Command() :Command(0,0,0) {}
}cmd[maxc];

const int maxn=2e5+10;
const int maxm=6e5+10;
int n,m,weight[maxn],from[maxm],to[maxm],removed[maxm];

int fa[maxn];
int find(int x) { return fa[x]!=x?fa[x]=find(fa[x]):x; }

Node *root[maxn];

int kth(Node *&o,int k) {
	if (o==NULL||k<=0||k>o->s) return 0;
	int s=o->ch[1]==NULL?0:o->ch[1]->s;
	if (k==s+1) return o->v;
	else if (k<=s) return kth(o->ch[1],k);
	else return kth(o->ch[0],k-s-1);
}

void mergeto(Node *&src,Node *&dest) {
	//printf("o:%d lo:%d ro:%d\n",dest,dest->ch[0],dest->ch[1]);
	if (src->ch[0]!=NULL) mergeto(src->ch[0],dest);
	if (src->ch[1]!=NULL) mergeto(src->ch[1],dest);
	insert(dest,src->v);
	//printf("o:%d lo:%d ro:%d\n",dest,dest->ch[0],dest->ch[1]);
	delete src;src=NULL;
}

void removetree(Node *&x) {
	if (x->ch[0]!=NULL) removetree(x->ch[0]);
	if (x->ch[1]!=NULL) removetree(x->ch[1]);
	delete x;x=NULL;
}

void add_edge(int x) {
	int u=find(from[x]),v=find(to[x]);
	if (u!=v) {
		if (root[u]->s>root[v]->s) { fa[v]=u;mergeto(root[v],root[u]); }
		else { fa[u]=v;mergeto(root[u],root[v]); }
	}
}

int query_cnt;
ll query_tot;
void query(int x,int k) {
	query_cnt++;
	query_tot+=kth(root[find(x)],k);
}

void change_weight(int x,int v) {
	int u=find(x);
	remove(root[u],weight[x]);
	insert(root[u],v);
	weight[x]=v;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	int kase=0;
	while (scanf("%d%d",&n,&m)==2&&n&&m) {
		For(i,1,n) scanf("%d",weight+i);
		For(i,1,m) scanf("%d%d",from+i,to+i);
		memset(removed,0,sizeof(removed));

		int c=0;
		for (;;) {
			char type;
			int x,p=0,v=0;
			scanf(" %c",&type);
			if (type=='E') break;
			if (type=='D') { scanf("%d",&x);removed[x]=1; }
			if (type=='Q') scanf("%d%d",&x,&p);
			if (type=='C') { scanf("%d%d",&x,&v);p=weight[x];weight[x]=v; }
			cmd[c++]=Command(type,x,p);
		}

		For(i,1,n) {
			fa[i]=i;if (root[i]!=NULL) removetree(root[i]);
			root[i]=new Node(weight[i]);
			//printf("#%d v:%d weight:%d \n",i,root[i]->v,weight[i]);
		}

		For(i,1,m) if (!removed[i]) add_edge(i);

		query_tot=query_cnt=0;
		for (int i=c-1;i>=0;--i) {
			//printf("cmd[%d]={type:%c x:%d p:%d}\n",i,cmd[i].type,cmd[i].x,cmd[i].p);
			if (cmd[i].type=='D') add_edge(cmd[i].x);
			if (cmd[i].type=='Q') query(cmd[i].x,cmd[i].p);
			if (cmd[i].type=='C') change_weight(cmd[i].x,cmd[i].p);
		}
		printf("Case %d: %.6f\n",++kase,query_tot/(double)query_cnt);
	}


#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}