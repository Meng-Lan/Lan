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

const int maxn=22;
int n,m;
ll in[maxn][maxn];
ll k;
std::map<ll,int> map[maxn][maxn];
struct Lan{
    int x,y,step;
    ll v;
    Lan(int x,int y,int step,ll v):x(x),y(y),step(step),v(v){}
    Lan():Lan(0,0,0,0){}
};

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    cin>>n>>m>>k;
    For(i,1,n) For(j,1,m) cin>>in[i][j];
    int step=std::max(n,m);
    std::queue<Lan> q;
    q.push(Lan(1,1,step-1,in[1][1]));
    ll ans=0;
    while(!q.empty()){
        Lan t=q.front();q.pop();
        if(!t.step){
            map[t.x][t.y][t.v]++;
            // printf("x:%d y:%d v:%lld\n",t.x,t.y,t.v);
            continue;
        }
        if(t.x<n){
            q.push(Lan(t.x+1,t.y,t.step-1,t.v^in[t.x+1][t.y]));
        }
        if(t.y<m){
            q.push(Lan(t.x,t.y+1,t.step-1,t.v^in[t.x][t.y+1]));
        }
    }
    step=std::min(n,m)-1;
    if(!step) ans=map[n][m][k];
    q.push(Lan(n,m,step-1,in[n][m]));
    // PV(step);
    while(!q.empty()){
        Lan t=q.front();q.pop();
        if(!t.step){
            // printf("x:%d y:%d v:%lld\n",t.x,t.y,t.v);
            if(t.x>1) ans+=map[t.x-1][t.y][t.v^k];
            if(t.y>1) ans+=map[t.x][t.y-1][t.v^k];
            continue;
        }
        if(t.x>1) q.push(Lan(t.x-1,t.y,t.step-1,t.v^in[t.x-1][t.y]));
        if(t.y>1) q.push(Lan(t.x,t.y-1,t.step-1,t.v^in[t.x][t.y-1]));
    }
    // PV(ans);
    cout<<ans<<endl;

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
