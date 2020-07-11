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
#define fi first
#define se second
#define pb push_back
#define is insert
namespace IO {
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
inline int read() { static int x;read(x);return x; }
ll gcd(ll a,ll b) { return b?gcd(b,a%b):a; }
ll lcm(ll a,ll b) { return a/gcd(a,b)*b; }
#define PA(name,init,len) cout<<#name"["<<(len-init)<<"]=";FOR(_,init,len) cout<<name[_]<<" \n"[_==(len-1)];
#define Pa(name,init,len) cout<<#name"["<<(len-init+1)<<"]=";For(_,init,len) cout<<name[_]<<" \n"[_==(len)];
#define PV(name) cout<<#name"="<<name<<'\n';

const int INF=1e9;
const int maxn=1e6+10;
struct Node {
	int l,r,d[2],min[2],max[2];
	//const int& operator[](int x) const{ return d[x]; }
	int& operator[](int x) { return d[x]; }
	Node(int x=0,int y=0) :l(0),r(0) { d[0]=x;d[1]=y; }
}p[maxn>>1];
int n,m,root,D;
bool operator<(Node a,Node b) { return a[D]<b[D]; }
inline int dis(Node a,Node b) { return std::abs(a[0]-b[0])+std::abs(a[1]-b[1]); }

struct KDTree {
	int ans;
	Node t[maxn],T;
	void up(int k) {
		Node &l=t[t[k].l],&r=t[t[k].r];
		for(int i=0;i<2;++i) {
			if(t[k].l) t[k].min[i]=std::min(t[k].min[i],l.min[i]),t[k].max[i]=std::max(t[k].max[i],l.max[i]);
			if(t[k].r) t[k].min[i]=std::min(t[k].min[i],r.min[i]),t[k].max[i]=std::max(t[k].max[i],r.max[i]);
		}
	}
	int build(int l,int r,int d) {
		D=d;
		int mid=(l+r)>>1;
		std::nth_element(p+l,p+mid,p+r+1);
		t[mid]=p[mid];
		for(int i=0;i<2;++i) t[mid].min[i]=t[mid].max[i]=t[mid][i];
		if(l<mid) t[mid].l=build(l,mid-1,d^1);
		if(r>mid) t[mid].r=build(mid+1,r,d^1);
		up(mid);
		return mid;
	}
	int get(int k,Node p) {
		int tmp=0;
		for(int i=0;i<2;++i) tmp+=std::max(0,t[k].min[i]-p[i]);
		for(int i=0;i<2;++i) tmp+=std::max(0,p[i]-t[k].max[i]);
		return tmp;
	}
	void insert(int k,int now) {
		if(T[now]>=t[k][now]) {
			if(t[k].r) insert(t[k].r,now^1);
			else {
				t[k].r=++n;t[n]=T;
				for(int i=0;i<2;++i) t[n].min[i]=t[n].max[i]=t[n][i];
			}
		}
		else {
			if(t[k].l) insert(t[k].l,now^1);
			else {
				t[k].l=++n;t[n]=T;
				for(int i=0;i<2;++i) t[n].min[i]=t[n].max[i]=t[n][i];
			}
		}
		up(k);
	}
	void query(int k,int now) {
		int d,dl=INF,dr=INF;
		d=dis(t[k],T);
		ans=std::min(ans,d);
		if(t[k].l) dl=get(t[k].l,T);
		if(t[k].r) dr=get(t[k].r,T);
		if(dl<dr) {
			if(dl<ans) query(t[k].l,now^1);
			if(dr<ans) query(t[k].r,now^1);
		}
		else {
			if(dr<ans) query(t[k].r,now^1);
			if(dl<ans) query(t[k].l,now^1);
		}
	}
	int query(Node p) {
		ans=INF;T=p;query(root,0);
		return ans;
	}
	void insert(Node p) {
		T=p;insert(root,0);
	}
}kd;

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i) scanf("%d%d",&p[i].d[0],&p[i].d[1]);
	root=kd.build(1,n,0);
	while(m--) {
		int op,x,y;scanf("%d%d%d",&op,&x,&y);
		if(op==1) kd.insert(Node(x,y));
		else printf("%d\n",kd.query(Node(x,y)));
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}
