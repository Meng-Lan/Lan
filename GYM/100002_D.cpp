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

const int maxn=2e4+10;
char s[maxn],t[maxn],ans[maxn];
int ns,nt,na;

int h2d(char c) { return isdigit(c)?c-'0':c-'A'+10; }
char d2h(int c) { return c<10?c+'0':c-10+'A'; }
int getbyte(char a,char b) { return ((h2d(a)<<4)|(h2d(b))); }
void toans(int key) { ans[na++]=d2h(key>>4);ans[na++]=d2h((key&15)); }

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

	freopen("decode.in","r",stdin);
	freopen("decode.out","w",stdout);
	while(scanf("%s %s",s,t)==2) {
		memset(ans,0,sizeof(ans));
		ns=strlen(s);nt=strlen(t);na=0;
		assert(ns==nt-2);
		int e=getbyte(t[0],t[1]);
		int c=32;
		int k=e^c;
		toans(k);
		for(int i=0;i<ns;i+=2) {
			e=getbyte(s[i],s[i+1]);
			c=e^k;
			e=getbyte(t[i+2],t[i+3]);
			k=e^c;
			toans(k);
		}
		printf("%s\n",ans);
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}
