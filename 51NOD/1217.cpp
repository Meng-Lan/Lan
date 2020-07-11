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

const int maxn=5e3+10;
const int maxm=1e6+10;
int in[maxn];
int d[maxm];
int vis[maxn],cnt;
int n,k;

bool check(int m){
    ++cnt;
    int ret=0;
    FOR(i,0,n){
        if(vis[in[i]%m]==cnt){
            ++ret;
            if(ret>k) return false;
        }
        vis[in[i]%m]=cnt;
    }
    return true;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    scanf("%d%d",&n,&k);
    int max=0;
    FOR(i,0,n) scanf("%d",in+i),max=std::max(max,in[i]);
    FOR(i,0,n) FOR(j,i+1,n) ++d[std::abs(in[i]-in[j])];
    int tmp=k*(k+1)/2;
    For(i,n-k,max+1){
        int m=(max+1)/i;
        int t=0;
        For(j,1,m) t+=d[i*j];
        if(t<=k){printf("%d\n",i);break;}
        if(t>tmp) continue;
        if(check(i)){printf("%d\n",i);break;}
    }

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
