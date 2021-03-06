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
int n,m;
int in[maxn];
int C[255];

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    C['C']=1;C['W']=0;C['B']=2;C['D']=3;
    int T;scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        FOR(i,0,n){
            char c;
            scanf(" %c",&c);
            if(c=='W') in[i]=0;
            else {int x;scanf("%d",&x);in[i]=(C[c]-1)*m+x;}
        }
        if(n==1) printf("%d\n",3*m);
        else{
            int idx=-1;
            FOR(i,0,n) if(!in[i]) idx=i;
            if(idx==-1){
                if(in[0]>in[1]) printf("1\n");
                else{
                    int ans=m*3-(n-1);
                    printf("%d\n",ans);
                }
            }
            else{
                int ans=0;
                if(idx==0) ans+=in[idx+1]-1;
                else{
                    if(in[0]>in[1]&&in[1]!=0) ans=1;
                    else{
                        if(idx==1) ++ans;
                        if(idx==n-1) ans+=3*m-in[idx-1];
                        else ans+=in[idx+1]-in[idx-1]-1;
                    }
                }
                printf("%d\n",ans);
            }
        }
    }


	return 0;
}
