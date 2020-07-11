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

const int maxn=2e5+10;
const int logn=22;
ll d[maxn][logn];
int M,D;

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    scanf("%d%d",&M,&D);
    ll t=0;
    int size=0;
    while(M--){
        char cmd[10];
        ll in;
        scanf("%s%lld",cmd,&in);
        if(cmd[0]=='A'){
            in=(in+t)%D;
            d[size][0]=in;
            //直接更新到最高层去，省得以后多加一层，我还需要跑去处理最上层的东西，更好写，常数会高一点，毕竟nlogn跑满了
            FOR(k,1,logn){
                int len=(1<<k);
                int L=size-len+1;//区间[L,size],长度为2^k
                if(L<0) d[0][k]=std::max(d[0][k],in);//2^k>size，d[0][k]表示的区间大于当前我值的个数，那么全部更新到以0开始长度为2^k的区间里面去
                else d[L][k]=std::max(d[L][k-1],d[L+(1<<(k-1))][k-1]);
            }
            ++size;
        }
        else{
            if(in==0) puts("0");
            else{
                int k=0;
                while((1<<(k+1))<=in) ++k;
                int L=size-in;
                t=std::max(d[L][k],d[size-(1<<k)][k]);
                printf("%lld\n",t);
            }
        }
    }

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
