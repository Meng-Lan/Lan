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

std::string in,s;

void puttab(int n) {
	FOR(i,0,n) printf("    ");
}

int main() {
#ifdef MengLan
	int Beginning=clock();
#else
	freopen("code.in","r",stdin);
	freopen("code.out","w",stdout);
#endif // MengLan

	while(cin>>in) for(auto &c:in) if(!isspace(c)) s.pb(c);
	int tab=0;
	bool top=true,right=false;
	for(auto &c:s) {
		if(c=='{') {
			if(top) puttab(tab);
			else printf(" ");
			++tab;
			printf("{\n");
			top=true; right=false;
			continue;
		}
		if(c=='}') {
			if(!top) printf("\n");
			puttab(--tab);
			printf("}");
			top=false;right=false;
			continue;
		}
		if(c==';') {
			printf(";\n");top=true;
			continue;
		}
		if(top) {
			puttab(tab);top=false;
		}
		if(right) printf(" ");
		printf("%c",c);
		if(c==',') right=true;
		else right=false;
	}

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}
/*
{class(Point)
{
member ( int ( x ) ) ; member ( int ( y ) ) ;
member ( fun ( Length )
{
return ( sqrt ( sum ( sqr ( x ),sqr ( y ) ) ) );
} ) ;
};
Main
{
repeat
{
set ( n,input ( int ) ) ;
for ( int ( i,0 ) , lt ( i,n ) , inc ( i ) )
{
print ( mult ( n,n ) ) ;
};
};
}; }
*/