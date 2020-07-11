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

const int maxn=2e6+10;
char s[maxn];
int a[maxn],sa[maxn];
int wa[maxn],wb[maxn],ws[maxn],wv[maxn];
inline int cmp(int *r,int a,int b,int l) { return r[a]==r[b]&&r[a+l]==r[b+l]; }
void da(int *r,int *sa,int n,int m) {
	int *x=wa,*y=wb,*t;
	for(int i=0;i<m;++i) ws[i]=0;
	for(int i=0;i<n;++i) ws[x[i]=r[i]]++;
	for(int i=1;i<m;++i) ws[i]+=ws[i-1];
	for(int i=n-1;i>=0;--i) sa[--ws[x[i]]]=i;
	for(int p=1,j=1,i;p<n;j*=2,m=p) {
		for(p=0,i=n-j;i<n;++i) y[p++]=i;
		for(i=0;i<n;++i) if(sa[i]>=j) y[p++]=sa[i]-j;
		for(i=0;i<n;++i) wv[i]=x[y[i]];
		for(i=0;i<m;++i) ws[i]=0;
		for(i=0;i<n;++i) ws[wv[i]]++;
		for(i=1;i<m;++i) ws[i]+=ws[i-1];
		for(int i=n-1;i>=0;--i) sa[--ws[wv[i]]]=y[i];
		for(t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1;i<n;++i)
			x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
	}
	PA(sa,0,n);
	PA(x,0,n);
}
#define F(x) ((x)/3+((x)%3==1?0:tb))
#define G(x) ((x)<tb?(x)*3+1:((x)-tb)*3+2)
int c0(int *r,int a,int b) { return r[a]==r[b]&&r[a+1]==r[b+1]&&r[a+2]==r[b+2]; }
int c12(int k,int *r,int a,int b) {
	if(k==2) return r[a]<r[b]||r[a]==r[b]&&c12(1,r,a+1,b+1);
	else return r[a]<r[b]||r[a]==r[b]&&wv[a+1]<wv[b+1];
}
void sort(int *r,int *a,int *b,int n,int m) {
	int i;
	for(i=0;i<n;i++) wv[i]=r[a[i]];
	for(i=0;i<m;i++) ws[i]=0;
	for(i=0;i<n;i++) ws[wv[i]]++;
	for(i=1;i<m;i++) ws[i]+=ws[i-1];
	for(i=n-1;i>=0;i--) b[--ws[wv[i]]]=a[i];
	return;
}
void dc3(int *r,int *sa,int n,int m) {
	int i,j,*rn=r+n,*san=sa+n,ta=0,tb=(n+1)/3,tbc=0,p;
	r[n]=r[n+1]=0;
	for(i=0;i<n;i++) if(i%3!=0) wa[tbc++]=i;
	sort(r+2,wa,wb,tbc,m);
	sort(r+1,wb,wa,tbc,m);
	sort(r,wa,wb,tbc,m);
	for(p=1,rn[F(wb[0])]=0,i=1;i<tbc;i++)
		rn[F(wb[i])]=c0(r,wb[i-1],wb[i])?p-1:p++;
	if(p<tbc) dc3(rn,san,tbc,p);
	else for(i=0;i<tbc;i++) san[rn[i]]=i;
	for(i=0;i<tbc;i++) if(san[i]<tb) wb[ta++]=san[i]*3;
	if(n%3==1) wb[ta++]=n-1;
	sort(r,wb,wa,ta,m);
	for(i=0;i<tbc;i++) wv[wb[i]=G(san[i])]=i;
	for(i=0,j=0,p=0;i<ta && j<tbc;p++)
		sa[p]=c12(wb[j]%3,r,wa[i],wb[j])?wa[i++]:wb[j++];
	for(;i<ta;p++) sa[p]=wa[i++];
	for(;j<tbc;p++) sa[p]=wb[j++];
	//PA(sa,0,n);
	return;
}
int rank[maxn],height[maxn];
void calheight(int *r,int *sa,int n) {
	for(int i=1;i<=n;++i) rank[sa[i]]=i;
	for(int i=0,j,k=0;i<n;height[rank[i++]]=k)
		for(k?k--:0,j=sa[rank[i]-1];r[i+k]==r[j+k];++k);
	//Pa(height,1,n);
	//Pa(rank,0,n);
}
int f[maxn];

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	//da(a,sa,9,3);
	//dc3(a,sa,9,3);
	//calheight(a,sa,8);
	while(scanf("%s",s)==1) {
		if(strcmp(s,".")==0) break;
		int n=strlen(s);
		For(i,0,n) a[i]=s[i];
		dc3(a,sa,n+1,256);
		calheight(a,sa,n);
		memset(f,0,sizeof(f));
		f[rank[0]]=maxn;
		for(int i=rank[0]-1;i>=0;--i) f[i]=std::min(f[i+1],height[i+1]);
		for(int i=rank[0]+1;i<=n;++i) f[i]=std::min(f[i-1],height[i]);
		for(int k=1;k<=n;k++)
			if(n%k==0&&f[rank[k]]==n-k) {
				printf("%d\n",n/k);break;
			}
		//PA(f,0,n);
	}


#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}
