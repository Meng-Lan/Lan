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
const int maxn=5e3+10;
int f[maxn],g[maxn],in[maxn];
int n;

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    while(scanf("%d",&n)==1){
        For(i,1,n) scanf("%d",in+i);
        For(i,1,n) g[i]=INF;
        For(i,1,n){
            int k=std::lower_bound(g+1,g+1+n,in[i])-g;
            f[i]=k;
            g[k]=in[i];
        }
        For(i,1,n){
            int t=0;
            For(j,1,n) g[j]=INF;//PV(i)
            For(j,1,n) if(i!=j){
                int k=f[j];
                //printf("K:%d g[k-1]:%d in[j]:%d\n",k,g[k-1],in[j]);
                if(g[k-1]<in[j]){
                    t^=k*k;
                    g[k]=std::min(g[k],in[j]);
                }
                else{
                    t^=(k-1)*(k-1);
                    g[k-1]=in[j];
                }
                //For(l,1,n) printf("g[%d]=%d\n",l,g[l]);
            }
            printf("%d%c",t,i!=n?' ':'\n');
        }
    }


#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
