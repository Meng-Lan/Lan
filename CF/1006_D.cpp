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

const int maxn=1e5+10;
std::string a,b;
int n;

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    cin>>n;
    cin>>a>>b;
    int ans=0;
    for(int i=0;i<=n/2;++i){
        if(i==n/2) {if(a[i]!=b[i]) ++ans;}
        else{
            if(b[i]==b[n-i-1]){if(a[i]!=a[n-i-1]) ++ans;}
            else{
                if(a[i]>a[n-i-1]) std::swap(a[i],a[n-1-i]);
                if(b[i]>b[n-i-1]) std::swap(b[i],b[n-i-1]);
                if(a[i]==b[i]){
                    if(a[n-i-1]!=b[n-1-i]) ++ans;
                }
                else if(a[i]==b[n-1-i]||a[n-i-1]==b[i]||b[n-i-1]==a[n-i-1]) ++ans;
                else ans+=2;
            }
            // char c[5];
            // c[0]=a[i];c[1]=a[n-i-1];c[2]=b[i];c[3]=b[n-i-1];
            // std::sort(c,c+4);
            // if(c[0]==c[1]&&c[2]==c[3]);
            // else if(c[0]==c[1]||c[2]==c[3]) ++ans;
            // else if(c[1]==c[2]) ++ans;
            // else ans+=2;
        }
        // PV(ans)
    }
    cout<<ans<<endl;

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
