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

const int maxn=1e3+10;

int wa[maxn],wb[maxn],wv[maxn],ws[maxn];
inline int cmp(int *r,int a,int b,int l) { return r[a]==r[b]&&r[a+l]==r[b+l]; }
void da(int *r,int *sa,int n,int m) {
	int *x=wa,*y=wb,*t;
	for(int i=0;i<m;++i) ws[i]=0;
	for(int i=0;i<n;++i) ws[x[i]=r[i]]++;
	for(int i=1;i<m;++i) ws[i]+=ws[i-1];
	for(int i=n-1;i>=0;--i) sa[--ws[x[i]]]=i;
	for(int j=1,p=1,i;p<n;j*=2,m=p) {
		for(p=0,i=n-j;i<n;++i) y[p++]=i;
		for(i=0;i<n;++i) if(sa[i]>=j) y[p++]=sa[i]-j;
		for(i=0;i<n;++i) wv[i]=x[y[i]];
		for(i=0;i<m;++i) ws[i]=0;
		for(i=0;i<n;++i) ws[wv[i]]++;
		for(i=1;i<m;++i) ws[i]+=ws[i-1];
		for(i=n-1;i>=0;--i) sa[--ws[wv[i]]]=y[i];
		for(t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1;i<n;++i)
			x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
	}
	//PA(sa,0,n);
	//PA(x,0,n);
}
int rank[maxn],height[maxn];
void calheight(int *r,int *sa,int n) {
	for(int i=1;i<=n;++i) rank[sa[i]]=i;
	for(int i=0,k=0,j;i<n;height[rank[i++]]=k)
		for(k?k--:0,j=sa[rank[i]-1];r[i+k]==r[j+k];k++);
	//Pa(height,1,n);
}
int a[maxn],sa[maxn];
char s[maxn];

int main() {
#ifdef MengLan
	int Beginning=clock();
	freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	int T;scanf("%d",&T);
	while(T--) {
		scanf("%s",s);
		int n=strlen(s);
		For(i,0,n) a[i]=s[i];
		//PA(a,0,n);
		da(a,sa,n+1,255);
		calheight(a,sa,n);
		int ans=0;
		for(int i=1;i<=n;++i) {
			ans+=n-sa[i]-height[i];
		}
		printf("%d\n",ans);
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}
