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

const ll mod =1e9+7;
struct Matrix{
    ll d[3][3];
    Matrix(){memset(d,0,sizeof(d));}
    Matrix operator*(const Matrix &rhs)const{
        Matrix ret;
        for(int i=0;i<3;++i) for(int j=0;j<3;++j) {for(int k=0;k<3;++k) ret.d[i][j]+=d[i][k]*rhs.d[k][j]%mod;ret.d[i][j]%=mod;}
        return ret;
    }
    Matrix operator+(const Matrix &rhs)const{
        Matrix ret;
        FOR(i,0,3) FOR(j,0,3){
            ret.d[i][j]=d[i][j]+rhs.d[i][j];
            if(ret.d[i][j]>mod) ret.d[i][j]-=mod;
        }
        return ret;
    }
    void print(){
        FOR(i,0,3) FOR(j,0,3) printf("%lld%c",d[i][j],j==2?'\n':' ');
    }
};

Matrix qpow(int n){
    Matrix a,ret;
    a.d[0][0]=a.d[0][2]=a.d[1][0]=a.d[2][1]=1;
    ret.d[0][0]=ret.d[1][0]=ret.d[2][0]=1;
    while(n){
        if(n&1) ret=a*ret;
        n>>=1;
        a=a*a;
    }
    return ret;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    int T;scanf("%d",&T);
    while(T--){
        int n;scanf("%d",&n);
        if(n<=3) puts("1");
        else{
            auto ans=qpow(n-3);
            printf("%lld\n",(ans.d[0][0]%mod+mod)%mod);
        }
    }

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
