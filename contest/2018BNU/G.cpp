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


int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan
    int T,k=0;
    cin>>T;
    std::string s;
    while(T--){
        cin>>s;
        if(s.length()<=4){
            cout<<s<<endl;
            continue;
        }
        std::string t;
        int p=0;
        k=0;
        for(int i=0;i<s.length();i++){
            if(s[i]>='A'&&s[i]<='Z'){
                if(!i){
                    t+=s[i]+32;
                    k++;
                    continue;
                }
                if(k==1||i==s.length()-1){
                    cout<<s<<endl;
                    break;
                }
                k=1;
                p++;
                t+='_';
                t+=s[i]+32;
                continue;
            }
            k++;
            t+=s[i];
            if(i==s.length()-1){
                if(k==1||k==s.length()||!p)
                    cout<<s<<endl;
                else
                    cout<<t<<endl;
            }
        }
    }



#ifdef MengLan
	//printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}