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

const ll mod=1e9+7;

struct Matrix{
    ll m[3][3];
    Matrix(){memset(m,0,sizeof(m));}

    Matrix operator*(const Matrix &rhs){
        Matrix c;
        FOR(i,0,3) FOR(j,0,3) {
            FOR(k,0,3) c.m[i][j]+=m[i][k]*rhs.m[k][j]%mod;
            c.m[i][j]%=mod;
        }
        return c;
    }

    void print(){
        FOR(i,0,3){FOR(j,0,3) printf("%d%c",m[i][j]," \n"[j==2]);}
    }
};

ll p,q,r,n;

ll qpow(ll a,ll b){
    ll ret=1;
    while(b){
        if(b&1){ret=ret*a%mod;}
        b>>=1;
        a=a*a%mod;
    }
    return ret;
}

Matrix qpow(ll b){
    Matrix ret;
    FOR(i,0,3) ret.m[i][i]=1;
    ll inv=qpow(q,mod-2);
    Matrix a;
    a.m[0][0]=a.m[2][0]=p*inv%mod;
    a.m[0][1]=a.m[1][1]=a.m[2][1]=inv;
    a.m[2][2]=1;
    while(b){
        if(b&1) ret=ret*a;
        b>>=1;
        a=a*a;
    }
    return ret;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    cin>>p>>q>>r>>n;
    Matrix ans;
    ans.m[0][0]=ans.m[1][0]=ans.m[2][0]=3*r%mod*qpow(q,n-1)%mod;
    Matrix t=qpow(n-1); 
    // t.print();
    ans=t*ans;
    // PV(ans.m[0][0]);
    // PV(ans.m[1][0]);
    // PV(ans.m[2][0]);
    printf("%lld\n",ans.m[2][0]%mod);

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
