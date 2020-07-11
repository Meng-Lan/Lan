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

const int mod=1e9+7;
const int maxn=205;
int b[maxn][maxn],e[maxn][maxn];
int n;

int qpow(ll a,int b){
    ll ret=1;
    while(b){
        if(b&1) ret=ret*a%mod;
        b>>=1;
        a=a*a%mod;
    }
    return ret;
}

void print(){
    For(i,1,n){
        For(j,1,n) printf("%d ",b[i][j]);
        For(j,1,n) printf("%d ",e[i][j]);
        puts("");
    }
}

void gauss(){
    int det=1;
    //print();
    For(i,1,n){
        int t=i;
        For(j,i,n) if(b[j][i]) t=j;
        if(t!=i) det*=-1;
        For(j,1,n){
            std::swap(b[i][j],b[t][j]);
            std::swap(e[i][j],e[t][j]);
        }
        det=1LL*det*b[i][i]%mod;
        int inv=qpow(b[i][i],mod-2);
        For(j,1,n){
            b[i][j]=1LL*b[i][j]*inv%mod;
            e[i][j]=1LL*e[i][j]*inv%mod;
        }
        For(k,1,n) if(k!=i){
            int c=b[k][i];
            For(j,1,n){
                b[k][j]=(b[k][j]-1LL*c*b[i][j]%mod+mod)%mod;
                e[k][j]=(e[k][j]-1LL*c*e[i][j]%mod+mod)%mod;
            }
        }
        //PV(i)
        //print();
    }

    det=(det+mod)%mod;
    For(i,1,n) For(j,1,n) e[i][j]=(1LL*e[i][j]*det)%mod;
    //print();
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    while(scanf("%d",&n)==1){
        For(i,1,n) b[1][i]=1;
        For(i,2,n) For(j,1,n) scanf("%d",b[i]+j);
        For(i,1,n) For(j,1,n) e[i][j]=i==j;
        gauss();
        For(i,1,n){
            if(i&1) printf("%d",e[i][1]);
            else printf("%d",(mod-e[i][1])%mod);
            printf("%c"," \n"[i==n]);
        }
    }

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
