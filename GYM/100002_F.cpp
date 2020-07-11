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

const int maxn=105;
std::string s,d[maxn][maxn];

int cal(int l,int r) {
	int len=r-l+1;
	for(int i=1;i<=len/2;++i) if(len%i==0) {
		bool ok=true;
		for(int j=l;j<=r-i;++j) if(s[j]!=s[j+i]) { ok=false;break; }
		if(ok) return i;
	}
	return 0;
}
/*
AAAAAAAAAABABABCCD
*/
std::string& dp(int l,int r) {
	if(d[l][r].size()) return d[l][r];
	d[l][r]=s.substr(l,r-l+1);
	if(l==r) return d[l][r];
	std::string &ans=d[l][r];
	FOR(k,l,r) {
		std::string tmp=dp(l,k)+dp(k+1,r);
		if(tmp.size()<ans.size()) ans=tmp;
	}
	int len=cal(l,r);
	if(len) {
		char s[5];
		sprintf(s,"%d",(r-l+1)/len);
		std::string tmp=std::string(s)+"("+d[l][l+len-1]+")";
		if(tmp.size()<ans.size()) ans=tmp;
	}
	//cout<<l<<' '<<r<<' '<<d[l][r]<<'\n';
	return ans;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
#else
	freopen("folding.in","r",stdin);
	freopen("folding.out","w",stdout);
#endif // MengLan

	cin>>s;
	cout<<dp(0,(int)s.size()-1)<<endl;

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}
