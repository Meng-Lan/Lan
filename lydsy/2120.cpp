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

const int maxn=1e4+10;
const int maxm=1e6+10;
int n,m,c[maxn],pre[maxm],nxt[maxm];
int bl[maxn],sz,blo,L[maxn],R[maxn];

inline void resort(int i) { std::sort(pre+L[i],pre+R[i]+1); }

void build() {
	For(i,1,n) pre[c[i]]=0;
	For(i,1,n) { nxt[i]=pre[c[i]];pre[c[i]]=i; }
	For(i,1,n) pre[i]=nxt[i];
	For(i,1,sz) resort(i);
}

inline int cnt(int x,int v) { return std::lower_bound(pre+L[x],pre+R[x]+1,v)-(pre+L[x]); }

int query(int l,int r) {
	int ans=0;
	For(i,l,R[bl[l]]) if(nxt[i]<l) ++ans;
	if(bl[l]!=bl[r]) For(i,L[bl[r]],r) if(nxt[i]<l) ++ans;
	For(i,bl[l]+1,bl[r]-1) ans+=cnt(i,l);
	return ans;
}

void change(int x,int col) {
	c[x]=col;
	build();
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	scanf("%d%d",&n,&m);
	For(i,1,n) scanf("%d",c+i);
	blo=sqrt(n);sz=(n-1)/blo+1;
	For(i,1,n) bl[i]=(i-1)/blo+1;
	For(i,1,sz) L[i]=(i-1)*blo+1,R[i]=i*blo;
	R[sz]=n;
	//printf("blo:%d sz:%d\n",blo,sz);
	//For(i,1,sz) printf("i:%d L:%d R:%d\n",i,L[i],R[i]);
	//For(i,1,n) printf("bl[%d]=%d\n",i,bl[i]);
	build();
	For(i,1,m) {
		char op[5];int l,r;scanf(" %s%d%d",op,&l,&r);
		if(op[0]=='Q') printf("%d\n",query(l,r));
		else change(l,r);
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}
