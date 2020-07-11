#include<bits/stdc++.h>
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
const int logn=13;
int a,b,n;
int in[maxn][maxn];
int max[maxn][maxn][logn],min[maxn][maxn][logn];

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    scanf("%d%d%d",&a,&b,&n);
    FOR(i,0,a) FOR(j,0,b){
        scanf("%d",in[i]+j);
        max[i][j][0]=min[i][j][0]=in[i][j];
    }

    for(int k=1;(1<<k)<=n;++k) {
        for(int i=0;i+(1<<k)-1<a;++i) for(int j=0;j+(1<<k)-1<b;++j){
            max[i][j][k]=std::max({max[i][j][k-1],max[i][j+(1<<(k-1))][k-1],max[i+(1<<(k-1))][j][k-1],max[i+(1<<(k-1))][j+(1<<(k-1))][k-1]});//C++11的新特性，函数参数可以传个initializer_list过去，说白了就是传个特定类型数组过去
            min[i][j][k]=std::min({min[i][j][k-1],min[i][j+(1<<(k-1))][k-1],min[i+(1<<(k-1))][j][k-1],min[i+(1<<(k-1))][j+(1<<(k-1))][k-1]});
			//printf("max[%d][%d][%d]=%d min[%d][%d][%d]=%d\n",i,j,k,max[i][j][k],i,j,k,min[i][j][k]);
        }
    }
    
	//枚举左上角i，j，求区间[i,i+n][j,j+n]的最大最小值作差更新ans
    int k=0,ans=2e9;
    while((1<<(k+1))<=n) ++k;
    for(int i=0;i+n-1<a;++i) for(int j=0;j+n-1<b;++j){
        int Max=std::max({max[i][j][k],max[i][j+n-(1<<k)][k],max[i+n-(1<<k)][j][k],max[i+n-(1<<k)][j+n-(1<<k)][k]});
        int Min=std::min({min[i][j][k],min[i][j+n-(1<<k)][k],min[i+n-(1<<k)][j][k],min[i+n-(1<<k)][j+n-(1<<k)][k]});
        ans=std::min(ans,Max-Min);
    }
    printf("%d\n",ans);

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
