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
int d[2][maxn][maxn][4];
int n,m;
int a[maxn*10],b[maxn];

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    int T;scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        For(i,1,n) scanf("%d",a+i);
        For(i,1,m) scanf("%d",b+i);
        memset(d,0,sizeof(d));
        std::sort(b+1,b+m+1);
        int now=0,old=1;
        For(i,0,n) {
            For(j,1,m+1) for(int len=m-j+1;len>=0;--len){
                int k=j+len-1;
                if(i){
                    d[now][j][k][0]=std::max({d[old][j][k][0],d[old][j][k][1],d[old][j][k][2],d[old][j][k][3]});
                    d[now][j][k][1]=std::max(d[old][j][k][0],d[old][j][k][2])+a[i];
                }
                if(j>1) d[now][j][k][2]=std::max({d[now][j-1][k][0],d[now][j-1][k][1],d[now][j-1][k][2],d[now][j-1][k][3]});
                if(k<m) d[now][j][k][3]=std::max(d[now][j][k+1][0],d[now][j][k+1][2])+b[k+1];
            }
            std::swap(old,now);
        }
        int ans=0;
        For(i,1,m+1) ans=std::max({ans,d[old][i][i-1][0],d[old][i][i-1][1],d[old][i][i-1][2],d[old][i][i-1][3]});
        printf("%d\n",ans);
    }

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
