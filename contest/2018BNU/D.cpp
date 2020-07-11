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
 
ll a[1000005],b[1000005][2],c[1000005][2];
int main() {
#ifdef MengLan
    int Beginning=clock();
    //freopen("in","r",stdin);
    //freopen("out","w",stdout);
#endif // MengLan
    int T,n,m,k;
    cin>>T;
    while(T--){
        cin>>n>>m>>k;
        for(int i=0;i<n;i++)
            cin>>a[i];
        for(int i=0;i<m;i++)
            cin>>b[i][0];
        for(int i=0;i<k;i++)
            cin>>c[i][0];
        int j=0;
        for(int i=0;i<m;i++){
            while(j+1<n&&a[j+1]<b[i][0])
                j++;
            if(j+1>n-1)
                b[i][1]=std::abs(b[i][0]-a[j]);
            else
                b[i][1]=std::min(std::abs(b[i][0]-a[j]),std::abs(b[i][0]-a[j+1]));
            //cout<<"b:"<<b[i][1]<<endl;
        }
        j=0;
        for(int i=0;i<k;i++){
            while(b[j+1][0]<c[i][0]&&j+1<m)
                j++;
            if(j+1>m-1)
                c[i][1]=std::abs(c[i][0]-b[j][0])+b[j][1];
            else
                c[i][1]=std::min(std::abs(c[i][0]-b[j][0])+b[j][1],std::abs(c[i][0]-b[j+1][0])+b[j+1][1]);
            //cout<<"c:"<<c[i][1]<<endl;
        }
        ll ans=c[0][1];
        for(int i=1;i<k;i++)
            ans=ans<c[i][1]?ans:c[i][1];
        cout<<ans+3<<endl;
    }
 
 
 
 
 
#ifdef MengLan
    printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
    return 0;
}