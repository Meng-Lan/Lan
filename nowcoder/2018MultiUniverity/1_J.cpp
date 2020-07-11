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

const int maxn=1e5+10;
int n,q,in[maxn];
struct Q{
    int l,r,i;
    bool operator<(const Q &rhs)const{return r<rhs.r;}
}qs[maxn];
int c[maxn];
int first[maxn],last[maxn];

inline int lowbit(int x){return x&-x;}
void add(int x,int v){while(x){c[x]+=v;x-=lowbit(x);}}
int sum(int x){
    int ret=0;
    while(x<maxn){ret+=c[x];x+=lowbit(x);}
    return ret;
}
int ans[maxn];

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    while(scanf("%d%d",&n,&q)==2){
        For(i,1,n) scanf("%d",in+i);
        FOR(i,0,q) scanf("%d%d",&qs[i].l,&qs[i].r),qs[i].i=i;
        std::sort(qs,qs+q);
        memset(first,-1,sizeof(first));
        memset(last,-1,sizeof(last));
        For(i,1,n){if(first[in[i]]==-1) first[in[i]]=i;last[in[i]]=i;}
        int sz=0;
        for(auto &v:first) if(v!=-1) ++sz;
        int j=0;
        memset(c,0,sizeof(c));
        For(i,1,n){
            while(j<q&&qs[j].r==i){
                ans[qs[j].i]=sz-sum(qs[j].l);
                ++j;
            }
            if(last[in[i]]==i) {add(first[in[i]]-1,1);}
        }
        FOR(i,0,q) printf("%d\n",ans[i]);
    }

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
