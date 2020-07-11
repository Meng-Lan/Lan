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

const int maxn=55;
char s[maxn][maxn];
int n,m;
bool vis[maxn][maxn][maxn<<1];
char in[maxn<<1];
int len;

const int dx[]={ 1,0,-1,0 };
const int dy[]={ 0,1,0,-1 };
int t[]={ 0,1,2,3 };

P b,e;

struct Node {
    P x;
    int y;
    Node(P x,int y) :x(x),y(y) {}
    Node() :Node(P(0,0),0) {}
};

bool check(P v) {
    return v.fi>=1&&v.fi<=n&&v.se>=1&&v.se<=m;
}

bool bfs() {
    std::queue<Node> q;q.push(Node(b,0));
    while(!q.empty()) {
        Node u=q.front();q.pop();
        if(u.x==e) return true;
        if(u.y>=len) return false;
        int nxt=in[u.y];
        int i=t[nxt];
        P v(u.x.fi+dx[i],u.x.se+dy[i]);
        if(!check(v)||s[v.fi][v.se]=='#') return false;
        q.push(Node(v,u.y+1));
    }
    return false;
}

int main() {
#ifdef MengLan
    int Beginning=clock();
    //freopen("in","r",stdin);
    //freopen("out","w",stdout);
#endif // MengLan

    scanf("%d%d",&n,&m);
    For(i,1,n) scanf(" %s",s[i]+1);
    For(i,1,n) For(j,1,m) {
        if(s[i][j]=='S') b=P(i,j);
        if(s[i][j]=='E') e=P(i,j);
    }
    scanf(" %s",in);
    len=strlen(in);
    //PV(len);
    FOR(i,0,len) in[i]-='0';
    int ans=0;
    do {
        if(bfs()) ++ans;
    } while(std::next_permutation(t,t+4));
    printf("%d\n",ans);


#ifdef MengLan
    printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
    return 0;
}