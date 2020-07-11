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

const int maxc=105;
const int maxn=305;
int C[maxc][maxn][maxn];
int in[maxn][maxn];
int n,m;

int lowbit(int x){return x&-x;}
void add(int x,int y,int v,int c[][maxn]){
    int y2=y;
    while(x<=n) {
        y=y2;
        while(y<=m) {c[x][y]+=v;y+=lowbit(y);}
        x+=lowbit(x);
    }
}

int sum(int x,int y,int c[][maxn]){
    int ret=0,y2=y;
    while(x){
        y=y2;
        while(y){ret+=c[x][y];y-=lowbit(y);}
        x-=lowbit(x);
    }
    return ret;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    scanf("%d%d",&n,&m);
    For(i,1,n) For(j,1,m){
        scanf("%d",in[i]+j);
        add(i,j,1,C[in[i][j]]);
    }
    int q;scanf("%d",&q);
    while(q--){
        int t;scanf("%d",&t);
        if(t==1){
            int x,y,z;scanf("%d%d%d",&x,&y,&z);
            add(x,y,-1,C[in[x][y]]);
            add(x,y,1,C[z]);
            in[x][y]=z;
        }
        else{
            int x1,x2,y1,y2,z;scanf("%d%d%d%d%d",&x1,&x2,&y1,&y2,&z);
            int ans=sum(x2,y2,C[z])-sum(x1-1,y2,C[z])-sum(x2,y1-1,C[z])+sum(x1-1,y1-1,C[z]);
            printf("%d\n",ans);
        }
    }

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
