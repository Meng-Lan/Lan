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

ll n;
ll ans;
int n5[]={4,9,49};
int n10[]={9,49,5,45};
int n50[]={49,45,40};

int sign(int i){
    int cnt=0;
    while(i){cnt+=i&1;i>>=1;}
    if(cnt&1) return 1;
    return -1;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    // PV(lcm(1,5));
    cin>>n;
    ans=n;
    ll l=n,r=5*n;
    FOR(i,1,(1<<3)){
        ll lc=1;
        FOR(j,0,4) if(i&(1<<j)) lc=lcm(lc,n5[j]);
        ans+=sign(i)*(r/lc-l/lc);
    }
    l=5*n,r=10*n;
    FOR(i,1,(1<<4)){
        ll lc=1;
        FOR(j,0,3) if(i&(1<<j)) lc=lcm(lc,n10[j]);
        ans+=sign(i)*(r/lc-l/lc);
    }
    l=10*n,r=50*n;
    FOR(i,1,(1<<3)){
        ll lc=1;
        FOR(j,0,3) if(i&(1<<j)) lc=lcm(lc,n50[j]);
        ans+=sign(i)*(r/lc-l/lc);
    }
    PV(ans);


#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
