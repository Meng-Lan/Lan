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
const int mod=1e9;
struct Lan{
    std::vector<int> em;
    Lan(){em.pb(0);}
    Lan& operator+(const Lan &rhs){
        std::vector<int> t(std::max(em.size(),rhs.em.size())+1,0);
        FOR(i,0,em.size()) t[i]+=em[i];
        FOR(i,0,rhs.em.size()) t[i]+=rhs.em[i];
        FOR(i,0,t.size()) if(t[i]>=mod){t[i+1]++;t[i]-=mod;}
        if(t.back()==0) t.pop_back();
        em=t;
        return *this;
    }
    Lan& operator+=(const Lan &rhs){
        return *this=*this+rhs;
    }
}d[maxn];
std::ostream& operator<<(std::ostream &os,Lan &rhs){
    for(int i=rhs.em.size()-1;i>=0;--i) os<<rhs.em[i];os<<'\n';
    return os;
}
int n,k;

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    scanf("%d%d",&n,&k);
    d[0].em[0]=1;
    For(i,1,k) For(j,i,n) d[j]+=d[j-i];
    cout<<d[n];

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
