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

int n;
std::string a,b,c;
std::vector<int> ta,tb,tc;

int cal(std::string &s,std::vector<int> &v){
    v.resize(255);
    for(auto it:s) v[it]++;
    int idx=0,max=0;
    FOR(i,0,v.size()) if(v[i]>max){idx=i;max=v[i];}
    int diff=s.size()-max;
    if(!diff){
        if(n==1) return max-1;
        return max;
    }
    if(diff<=n) return s.size();
    return max+n;
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    //std::ios::sync_with_stdio(false);
    cin>>n;
    cin>>a>>b>>c;
    int aa=cal(a,ta),ab=cal(b,tb),ac=cal(c,tc);
    if(aa>ab&&aa>ac) cout<<"Kuro\n";
    else if(ab>aa&&ab>ac) cout<<"Shiro\n";
    else if(ac>aa&&ac>ab) cout<<"Katie\n";
    else cout<<"Draw\n";

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
