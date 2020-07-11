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

const P cost[5][5]={{{0,0},{0,1},{1,0},{1,0},{0,1}},
{{0,0},{0,0},{0,1},{1,0},{0,1}},
{{0,0},{0,0},{0,0},{0,1},{1,0}},
{{0,0},{0,0},{0,0},{0,0},{1,0}},
{{0,0},{0,0},{0,0},{0,0},{0,0}}};
const int maxn=205;
int a[maxn],b[maxn],na,nb,n;

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    scanf("%d%d%d",&n,&na,&nb);
    FOR(i,0,na) scanf("%d",a+i);
    FOR(i,0,nb) scanf("%d",b+i);
    int aa=0,ab=0;
    FOR(i,0,n){
        int ta=a[i%na],tb=b[i%nb];
        int rev=0;
        //printf("%d %d ",ta,tb);
        if(ta>tb){std::swap(ta,tb);rev=1;}
        P ans=cost[ta][tb];
        //printf("%d %d\n",ans.fi,ans.se);
        if(rev){aa+=ans.se;ab+=ans.fi;}
        else {aa+=ans.fi;ab+=ans.se;}
    }
    printf("%d %d\n",aa,ab);


#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
