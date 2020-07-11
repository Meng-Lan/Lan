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
const int logn=18;
int n,m;
struct Lan{
    int y,r;
    bool operator<(const int &rhs)const{return y<rhs;}
}in[maxn];
int d[maxn][logn],Log[maxn];

int find(int x){return std::lower_bound(in,in+n,x)-in;}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    scanf("%d",&n);
    FOR(i,0,n) scanf("%d%d",&in[i].y,&in[i].r),d[i][0]=in[i].r;
    scanf("%d",&m);

    Log[1]=0;
    For(i,2,n) Log[i]=Log[i/2]+1;
    for(int j=1;(1<<j)<=n;++j)
        for(int i=0;i+(1<<j)-1<n;++i) d[i][j]=std::max(d[i][j-1],d[i+(1<<(j-1))][j-1]);

    while(m--){
        int x,y;scanf("%d%d",&y,&x);
        //assert(y+1<x);
        int l=find(y),r=find(x);
        if(in[l].y==y&&in[r].y==x){
            if(in[l].r<in[r].r) puts("false");//x年的降雨量比y年大，不符合“X年的降雨量不超过Y年”
            else if(y+1==x) puts("true");//空集，区间(y,x)直接不存在其他年份，由上一个条件知道y年降雨量比x年多，那么显然是对的
            else if(l+1==r) puts("maybe");//由两个条件可知，区间(y,x)直接存在其他年份，但是却没有这一年或多年的记录，那么显然maybe
            else{//上面的特殊情况终于完了，下面是正常情况
                int L=l+1,R=r-1;
                int k=Log[R-L+1];
                int max=std::max(d[L][k],d[R-(1<<k)+1][k]);//区间(y,x)的最大值
                if(max>=in[r].r) puts("false");
                else if(x-y+1==r-l+1) puts("true");//区间(y,x)内每年都有记录，那么可以准确回答
                else puts("maybe");
            }
        }
        else if(in[l].y==y){
            if(l+1==r) puts("maybe");//区间(y,x)没有记录，而我也不知道x年的值，那么只能maybe
            else{//区间(y,x)有记录，那么我假设x年降雨量和y年一样，也符合“X年的降雨量不超过Y年”，那么就看(y,x)是否比y要小了
                int L=l+1,R=r-1;
                int k=Log[R-L+1];
                int max=std::max(d[L][k],d[R-(1<<k)+1][k]);
                if(max>=in[l].r) puts("false");
                else puts("maybe");
            }
        }
        else if(in[r].y==x){
            if(l==r) puts("maybe");//y年没记录，我还找不到(y,x)的记录，那么maybe
            else{//区间(y,x)有记录，假设y年比我x年大，那么我判断(y,x)是不是比x年小就好了
                int L=l,R=r-1;
                int k=Log[R-L+1];
                int max=std::max(d[L][k],d[R-(1<<k)+1][k]);
                if(max>=in[r].r) puts("false");
                else puts("maybe");
            }
        }
        else puts("maybe");
    }

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
