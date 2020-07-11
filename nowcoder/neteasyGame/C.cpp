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

std::vector<std::string> vs;
std::map<std::string,int> mp;

int getid(std::string s){
    if(mp.count(s)) return mp[s];
    vs.pb(s);
    return mp[s]=vs.size()-1;
}

typedef std::pair<int,std::bitset<100>> PIS;
std::vector<PIS> in;

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    int T;scanf("%d",&T);
    while(T--){
        int n,m,l,s;scanf("%d%d%d%d",&n,&m,&l,&s);
        in.clear();
        mp.clear();
        vs.clear();
        FOR(i,0,n){
            int x,p;scanf("%d%d",&x,&p);
            PIS tmp;
            tmp.fi=x;
            FOR(j,0,p){
                std::string s;cin>>s;
                int y=getid(s);
                tmp.se[y]=1;
            }
            in.pb(tmp);
        }
        int S=1<<n;
        int ans=0;
        FOR(i,1,S){
            int sz=0,t=i;
            while(t){sz+=(t&1);t>>=1;}
            if(sz!=m) continue;
            t=i;
            int max=0,min=6,sum=0;
            FOR(j,0,n) if((i>>j)&1){max=std::max(max,in[j].fi);min=std::min(min,in[j].fi);sum+=in[j].fi;}
            if(max-min<s||sum>l) continue;
            std::bitset<100> bs;
            bool ok=true;
            FOR(j,0,n) if((i>>j)&1){
                auto tmp=bs&in[j].se;
                if(tmp.count()) {ok=false;break;}
                bs|=in[j].se;
            }
            if(ok) ++ans;
        }
        printf("%d\n",ans);
    }

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
