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
        static const int BUFSIZE=1314520;
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

typedef std::pair<int,P> IP;
typedef std::pair<P,P> PP;
const int maxn=1e6+10;
int n,m,t;
std::vector<std::vector<int>> in;
std::multiset<int> ci[maxn],cd[maxn];
std::vector<IP> ins[maxn],del[maxn];
int vis[maxn],cnt[maxn];

int diff=0;
inline void add(int idx,int now){
    if(vis[now]==idx) {++cnt[now];return;}
    vis[now]=idx;cnt[now]=1;++diff;
}

int main() {
#ifdef MengLan
    int Beginning=clock();
    //freopen("in","r",stdin);
    //freopen("out","w",stdout);
#endif // MengLan

    // scanf("%d%d%d",&n,&m,&t);
    read(n);read(m);read(t);
    FOR(i,0,n){
        in.pb(std::vector<int>());
        in[i].resize(m);
        FOR(j,0,m){
            int v;
            //scanf("%d",&v);
            read(v);
            in[i][j]=v;
        }
    }
    FOR(i,0,t){
        int x1,y1,x2,y2,k;
        // scanf("%d%d%d%d%d",&x1,&y1,&x2,&y2,&k);
        read(x1);read(y1);read(x2);read(y2);read(k);
        --x1;--x2;--y1;--y2;
        ins[x1].pb(IP(k,P(y1,y2)));
        del[x2].pb(IP(k,P(y1,y2)));
    }
    int ans=0;
    memset(vis,-1,sizeof(vis));
    FOR(i,0,n){
        for(auto &v:ins[i]){
            ci[v.se.fi].insert(v.fi);
            cd[v.se.se].insert(v.fi);
        }
        std::vector<IP> t;
        ins[i].swap(t);
        diff=0;
        FOR(j,0,m){
            for(auto &v:ci[j]){
                add(i,v);
                // PV(vis[v]);
            }
            if(diff>1) ++ans;
            else if(diff==1){
                auto &v=in[i][j];
                if(vis[v]!=i) ++ans;
                else if(cnt[v]==0) ++ans;
            }
            // PV(vis[in[i][j]]);
            // PV(ans)
            for(auto &v:cd[j]) --cnt[v];
        }
        for(auto &v:del[i]){
            ci[v.se.fi].erase(v.fi);
            cd[v.se.se].erase(v.fi);
        }
        std::vector<IP> tt;
        del[i].swap(tt);
    }
    printf("%d\n",ans);

#ifdef MengLan
    printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
    return 0;
}
