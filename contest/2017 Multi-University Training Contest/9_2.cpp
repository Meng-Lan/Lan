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
/*namespace IO {
inline char getchar() {
static const int BUFSIZE=5201314;
static char buf[BUFSIZE],*begin,*end;
if(begin==end) {
begin=buf;
end=buf+fread(buf,1,BUFSIZE,stdin);
if(begin==end) return -1;
}
return *begin++;
}
}
inline void read(int &in) {
int c,symbol=1;
while(isspace(c=IO::getchar()));
if(c=='-') { in=0;symbol=-1; }
else in=c-'0';
while(isdigit(c=IO::getchar())) { in*=10;in+=c-'0'; }
in*=symbol;
}
inline int read() { static int x;read(x);return x; }*/
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

const int maxn=1e5+10;
const int INF=1e9;
std::vector<int> G[maxn];
int n,m,cost[maxn];
struct Query { int id,d,smb; };
std::vector<Query> q[maxn];

int anc[maxn][20],L[maxn];
void dfs(int u,int fa) {
	anc[u][0]=fa;
	for(auto &v:G[u]) if(v!=fa) { L[v]=L[u]+1;dfs(v,u); }
}
void preprocess() {
	memset(anc,0,sizeof(anc));
	L[1]=1;
	dfs(1,0);
	//For(i,1,n) printf("u:%d fa:%d\n",i,anc[i][0]);
	for(int j=1;(1<<j)<=n;++j) For(i,1,n)
		if(anc[i][j-1]!=0) {
			int a=anc[i][j-1];
			anc[i][j]=anc[a][j-1];
		}
}
int query(int p,int q) {
	int tmp,log,i;
	if(L[p]<L[q]) std::swap(p,q);
	for(log=1;(1<<log)<=L[p];++log);--log;
	for(int i=log;i>=0;--i)
		if(L[p]-(1<<i)>=L[q]) p=anc[p][i];
	if(p==q) return p;
	for(int i=log;i>=0;--i)
		if(anc[p][i]!=0&&anc[p][i]!=anc[q][i]) { p=anc[p][i];q=anc[q][i]; }
	return anc[p][0];
}

struct Node {
	Node *ch[2];
	int r,v,s;
	ll sum;
	Node(int v=0) :v(v),sum(v) { ch[0]=ch[1]=NULL;r=rand();s=1; }
	int cmp(int x)const { if(x==v) return -1;return x<v?0:1; }
	void maintain() {
		s=1,sum=v;
		if(ch[0]!=NULL) s+=ch[0]->s,sum+=ch[0]->sum;
		if(ch[1]!=NULL) s+=ch[1]->s,sum+=ch[1]->sum;
	}
}*root;

void rotate(Node *&o,int d) {
	Node *k=o->ch[d^1];o->ch[d^1]=k->ch[d];k->ch[d]=o;
	o->maintain();k->maintain();o=k;
}

void insert(Node *&o,int x) {
	if(o==NULL) o=new Node(x);
	else {
		int d=(x<o->v?0:1);
		insert(o->ch[d],x);
		if(o->ch[d]->r>o->r) rotate(o,d^1);
	}
	o->maintain();
}

Node* find(Node *o,int x) {
	if(o==NULL) return NULL;
	if(x==o->v) return o;
	return x<o->v?find(o->ch[0],x):find(o->ch[1],x);
}

void remove(Node *&o,int x) {
	int d=o->cmp(x);
	int ret=0;
	if(d==-1) {
		Node *u=o;
		if(o->ch[0]!=NULL&&o->ch[1]!=NULL) {
			int d2=(o->ch[0]->r>o->ch[1]->r?1:0);
			rotate(o,d2);remove(o->ch[d2],x);
		}
		else {
			if(o->ch[0]==NULL) o=o->ch[1];else o=o->ch[0];
			delete u;
		}
	}
	else remove(o->ch[d],x);
	if(o!=NULL) o->maintain();
}

ll getans(int x) {
	ll sum=0;
	Node *o=root;
	while(o!=NULL) {
		if(x>=o->v) {
			sum+=o->v;
			if(o->ch[0]!=NULL) sum+=o->ch[0]->sum;
			o=o->ch[1];
		}
		else o=o->ch[0];
	}
	return sum;
}

void print(Node *x) {
	if(x==NULL) return;
	print(x->ch[0]);
	printf("%d ",x->v);
	print(x->ch[1]);
}

ll ans[maxn];
void dfs2(int u,int fa) {
	//printf("in:%d\n",u);
	insert(root,cost[u]);
	//print(root);puts("");
	for(auto &it:q[u]) {
		ans[it.id]+=getans(it.d)*it.smb;
		//printf("id:%d d:%d sym:%d tans:%d\n",it.id,it.d,it.smb,tans);
	}
	for(auto &v:G[u]) if(v!=fa) dfs2(v,u);
	remove(root,cost[u]);
	//printf("leave:%d\n",u);
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	srand((unsigned int)time(0));
	while(scanf("%d%d",&n,&m)==2) {
		For(i,1,n) scanf("%d",cost+i);
		For(i,1,n) G[i].clear();
		FOR(i,1,n) {
			int u,v;scanf("%d%d",&u,&v);
			G[u].push_back(v);G[v].push_back(u);
		}
		preprocess();
		For(i,1,m) q[i].clear();
		For(i,1,m) {
			int s,t,a,b;scanf("%d%d%d%d",&s,&t,&a,&b);
			int lca=query(s,t);
			//printf("s:%d t:%d LCA:%d\n",s,t,lca);
			q[s].push_back({ i,a-1,-1 });
			q[t].push_back({ i,a-1,-1 });
			q[lca].push_back({ i,a-1,1 });
			q[anc[lca][0]].push_back({ i,a-1,1 });
			q[s].push_back({ i,b,1 });
			q[t].push_back({ i,b,1 });
			q[lca].push_back({ i,b,-1 });
			q[anc[lca][0]].push_back({ i,b,-1 });
		}
		root=NULL;
		memset(ans,0,sizeof(ans));
		dfs2(1,-1);
		For(i,1,m) printf("%lld%c",ans[i]," \n"[i==m]);
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}