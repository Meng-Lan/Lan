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
namespace IO {
	inline char getchar() {
		static const int BUFSIZE=1314520;
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
inline void read(char *s) {
	int c,idx=0;
	while(isspace(c=IO::getchar()));
	s[idx++]=c;//printf("c:%c\n",c);
	while(isupper(c=IO::getchar())) { s[idx++]=c; }
	s[idx]='\0';
};
inline int read() { static int x;read(x);return x; }
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

const int maxn=5e4+10;
const int maxm=1e4+10;
int n,m,in[maxn];
std::vector<int> v;
struct Que { int type,i,j,k; }q[maxm];
struct Node { int l,r,v; }t[maxn*50];
int root[maxn<<1],sz,cnt;

inline int ID(int x) { return std::lower_bound(v.begin(),v.end(),x)-v.begin()+1; }
inline int lowbit(int x) { return x&(-x); }

void getTLE() {
	unsigned int x=1e9;for(;;) { x*=(x*x); }
}

void update(int &rt,int l,int r,int pos,int x) {
	if(!rt) rt=++sz;
	t[rt].v+=x;
	if(sz>2500000) getTLE();
	if(l==r) return;
	int m=l+(r-l)/2;
	if(pos<=m) update(t[rt].l,l,m,pos,x);
	else update(t[rt].r,m+1,r,pos,x);
}

void build(int &x,int y,int l,int r,int pos) {
	t[++sz]=t[y];t[sz].v++;x=sz;
	if(l==r) return;
	int m=l+(r-l)/2;
	if(pos<=m) build(t[x].l,t[y].l,l,m,pos);
	else build(t[x].r,t[y].r,m+1,r,pos);
}

void add(int pos,int val,int x) {
	//printf("pos:%d val:%d x:%d\n",pos,val,x);
	while(pos<=n) { update(root[pos],1,cnt,val,x);pos+=lowbit(pos); }
}

int query(int l,int r,int k) {
	static int A[30],B[30];
	A[0]=B[0]=0;--l;
	A[++A[0]]=l?root[l+n]:0;
	B[++B[0]]=root[r+n];
	for(int x=l;x>0;x-=lowbit(x)) A[++A[0]]=root[x];
	for(int x=r;x>0;x-=lowbit(x)) B[++B[0]]=root[x];
	//printf("l:%d r:%d k:%d\n",l,r,k);
	//For(i,0,A[0]) printf("%d%c",A[i]," \n"[i==A[0]]);
	//For(i,0,B[0]) printf("%d%c",B[i]," \n"[i==B[0]]);
	int L=1,R=cnt,sumr,suml;
	while(L<R) {
		suml=sumr=0;
		For(i,1,A[0]) suml+=t[t[A[i]].l].v;
		For(i,1,B[0]) sumr+=t[t[B[i]].l].v;
		int m=L+(R-L)/2;
		//printf("L:%d R:%d m:%d suml:%d sumr:%d\n",L,R,m,suml,sumr);
		if(sumr-suml>=k) {
			For(i,1,A[0]) A[i]=t[A[i]].l;
			For(i,1,B[0]) B[i]=t[B[i]].l;
			R=m;
		}
		else {
			For(i,1,A[0]) A[i]=t[A[i]].r;
			For(i,1,B[0]) B[i]=t[B[i]].r;
			k-=sumr-suml;
			L=m+1;
		}
	}
	//printf("L:%d R:%d\n",L,R);
	return L;
}

void print(int rt,int l,int r) {
	printf("rt:%d l:%d r:%d v:%d\n",rt,l,r,t[rt].v);
	int m=l+(r-l)/2;
	if(t[rt].l) print(t[rt].l,1,m);
	if(t[rt].r) print(t[rt].r,m+1,r);
}

void printall() {
	For(i,1,n<<1) {
		printf("print tree:%d root:%d\n",i,root[i]);
		print(root[i],1,cnt);
	}
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	int T=read();//scanf("%d",&T);
	v.reserve(maxn+maxm);
	while(T--) {
		v.clear();memset(t,0,sizeof(t));memset(root,0,sizeof(root));sz=0;
		read(n);read(m);
		//printf("n:%d m:%d\n",n,m);
		//scanf("%d%d",&n,&m);
		For(i,1,n) {
			read(in[i]);
			//printf("in[%d]=%d\n",i,in[i]);
			//scanf("%d",in+i);
			v.push_back(in[i]);
		}
		For(i,1,m) {
			char cmd[10];read(cmd);//scanf(" %s",cmd);
			//printf("cmd:%s\n",cmd);
			//printf("%s\n",cmd);
			if(cmd[0]=='Q') {
				read(q[i].i);read(q[i].j);read(q[i].k);
				//scanf("%d%d%d",&q[i].i,&q[i].j,&q[i].k);
				q[i].type=0;
			}
			else {
				read(q[i].i);read(q[i].j);
				//scanf("%d%d",&q[i].i,&q[i].j);
				q[i].type=1;v.push_back(q[i].j);
			}
		}
		//puts("input over");
		std::sort(v.begin(),v.end());
		v.erase(std::unique(v.begin(),v.end()),v.end());
		cnt=v.size();
		For(i,1,n) build(root[n+i],root[n+i-1],1,cnt,ID(in[i]));
		For(i,1,m) {
			//printall();
			if(q[i].type) {
				add(q[i].i,ID(in[q[i].i]),-1);
				add(q[i].i,ID(q[i].j),1);
				in[q[i].i]=q[i].j;
			}
			else {
				printf("%d\n",v[query(q[i].i,q[i].j,q[i].k)-1]);
			}
		}
		//puts("next case:");
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}