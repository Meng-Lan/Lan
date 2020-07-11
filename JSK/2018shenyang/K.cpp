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

const int S=1<<5;
int digit[]={1,2,3,5,7};
std::set<int> si;

bool isprime(int x){
    int sq=sqrt(x+0.5);
    For(i,2,sq) if(x%i==0) return false;
    return true;
}

int ans[]={2,3,5,7,11,13,17,23,31,37,53,71,73,113,131,137,173,311,317};

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    // FOR(i,1,S){
    //     std::vector<int> v;
    //     FOR(j,0,5) if((i>>j)&1) v.pb(digit[j]);
    //     std::sort(v.begin(),v.end());
    //     int s=i;
    //     bool ok=true;
    //     for(int s0=s;s0;s0=(s0-1)&s){
    //         std::vector<int> tmp;
    //         for(int k=0;k<v.size();++k) if((s0>>k)&1) tmp.pb(v[k]);
    //         do{
    //             int x=0;
    //             FOR(j,0,tmp.size()) {x*=10;x+=tmp[j];}
    //             if(!isprime(x)) ok=false;
    //             break;
    //         }while(std::next_permutation(tmp.begin(),tmp.end()));
    //         if(!ok) break;
    //     }
    //     if(ok){
    //         do{
    //             int x=0;
    //             FOR(j,0,v.size()) {x*=10;x+=v[j];}
    //             si.insert(x);
    //         }while(std::next_permutation(v.begin(),v.end()));
    //     }
    // }
    // PV(si.size());
    // for(auto &v:si) PV(v);
    int T;cin>>T;
    For(kase,1,T){
        std::string in;
        cin>>in;
        if(in.size()>4) cout<<"Case #"<<kase<<": "<<ans[18]<<'\n';
        else{
            int x=0;
            for(auto &v:in){x*=10;x+=v-'0';}
            int ret=1;
            for(auto &v:ans) if(v<=x) ret=v;
            cout<<"Case #"<<kase<<": "<<ret<<'\n';
        }
    }

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
