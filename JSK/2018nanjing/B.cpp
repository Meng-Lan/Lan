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

const int maxm=1e2+10;
int n,m,k;
struct Lan{
    int x,y;
    bool operator<(const Lan &rhs)const{return x<rhs.x||x==rhs.x&&y<rhs.y;}
};
std::vector<Lan> in;
int h[maxm];
int y[maxm];

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    int T;scanf("%d",&T);
    For(kase,1,T){
        scanf("%d%d%d",&n,&m,&k);
        in.clear();
        memset(h,0,sizeof(h));
        FOR(i,0,k){int x,y;scanf("%d%d",&x,&y);in.pb({x,y});}
        ll ans=0,tmp=0;
        int idx=0;
        std::sort(in.begin(),in.end());
        For(i,1,n){
            For(j,1,m) ++h[j];
            while(idx<k&&in[idx].x<=i){h[in[idx].y]=0;++idx;}
            std::vector<Lan> q;
            q.pb({0,0});
            tmp=0;
            For(j,1,m){
                while(h[j]<q.back().x){
                    int x=q.back().x,y1=q.back().y;
                    q.pop_back();
                    int y2=q.back().y;
                    tmp-=(y1-y2)*x;
                }
                int y1=j,y2=q.back().y;
                tmp+=h[j]*(y1-y2);
                ans+=tmp;
                q.pb({h[j],j});
            }
        }
        printf("Case #%d: ",kase);
        cout<<ans<<endl;
    }



#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
