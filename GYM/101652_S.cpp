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

const int maxn=1e5+10;
char s[maxn];
int d[maxn];

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    scanf("%s",s+1);
    int len=strlen(s+1);
    For(i,1,len) if(s[i]=='B') d[i]=-1;else d[i]=1;
    int m1=0,l1=1,r1=0,t1=0;
    int tl=1;
    For(i,1,len){
        if(t1<0) {t1=0;tl=i;}
        t1+=d[i];
        if(t1>m1){m1=t1;l1=tl;r1=i;}
    }
    For(i,1,len) if(s[i]=='R') d[i]=-1;else d[i]=1;
    int m2=0,l2=1,r2=0,t2=0;
    tl=1;
    For(i,1,len){
        if(t2<0) {t2=0;tl=i;}
        t2+=d[i];
        if(t2>m2) {m2=t2;l2=tl;r2=i;}
    }
    if(m1==m2){
        if(l1==l2) printf("%d %d\n",l1,(r1<r2?r1:r2));
        else if(l1<l2) printf("%d %d\n",l1,r1);
        else printf("%d %d\n",l2,r2);
    }
    else if(m1>m2) printf("%d %d\n",l1,r1);
    else printf("%d %d\n",l2,r2);

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
