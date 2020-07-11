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
char s[maxn];
int n;
struct Lan{
    char T,c;
    int x;
    int q;
    std::vector<int> to;
}in[maxn];
std::vector<char> q;
int h[maxn];

void dfs(int u,int len){
    if(u==n+1) return;
    if(in[u].T=='U') return;
    if(in[u].T=='Q') q[in[u].q]=s[in[u].x-1];
    if(in[u].T=='T') s[len++]=in[u].c;
    //printf("u:%d len:%d\n",u,len);
    for(auto v:in[u].to) dfs(v,len);
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    scanf("%d",&n);
    int len=0;
    int tlen=0;
    For(i,1,n){
        scanf(" %c",&in[i].T);
        if(in[i].T=='T') scanf(" %c",&in[i].c);
        else scanf("%d",&in[i].x);
        if(in[i].T=='U') {
            int to=h[tlen-in[i].x-1];
            if(in[to].T=='U') to=in[to].q;
            in[to].to.pb(i+1);
            in[i].q=to;
            //printf("to:%d\n",to);
        }
        else in[i].to.pb(i+1);
        if(in[i].T=='T'||in[i].T=='U') h[tlen++]=i;
        if(in[i].T=='Q') in[i].q=len++;
    }
    in[0].T='#';
    in[0].to.pb(1);
    q.resize(len);
    dfs(0,0);
    FOR(i,0,len) printf("%c\n",q[i]);

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
