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
const char *s="RGB";
char c[255];
int d[maxn][3];
std::string in;
int n;

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    FOR(i,0,3) c[s[i]]=i;
    cin>>n>>in;
    memset(d,0x3f,sizeof(d));
    FOR(i,0,n){
        if(!i) FOR(j,0,3) d[i][j]=c[in[i]]!=j;
        else{
            FOR(j,0,3) FOR(k,0,3) if(j!=k) d[i][j]=std::min(d[i][j],d[i-1][k]+(c[in[i]]!=j));
        }
    }
    int ans=1e9;
    FOR(i,0,3) ans=std::min(d[n-1][i],ans);
    cout<<ans<<endl;
    std::string ret;
    int last=-1;
    for(int i=n-1;i>=0;--i){
        FOR(j,0,3) if(d[i][j]==ans&&j!=last){last=j;ret.push_back(s[j]);ans-=c[in[i]]!=j;break;}
    }
    std::reverse(ret.begin(),ret.end());
    cout<<ret<<endl;

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
