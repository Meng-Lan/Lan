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

struct Point {
    double x,y;
    Point(double x=0,double y=0) :x(x):y(y) {}
};
typedef Point Vector;

Vector operator+(Vector A,Vector B) { return Vector(A.x+B.x,A.y+B.y); }
Vector operator-(Point A,Point B) { return Vector(A.x-B.x,A.y-B.y); }
Vector operator*(Vector A,double p) { return Vector(A.x*p,A.y*p); }
Vector operator/(Vector A,double p) { return Vector(A.x/p,A.y/p); }
bool operator<(const Point &a,const Point &b) { return a.x<b.x||(a.x==b.x&&a.y<b.y); }

const double eps=1e-10;
int dcmp(double x) {
    if(fabs(x)<eps) return 0;else return x<0?-1:1;
}
bool operator==(const Point &a,const Point &b) {
    return dcmp(a.x-b.x)==0&&dcmp(a.y-b.y)==0;
}

double Dot(Vector A,Vector B) { return A.x*B.x+A.y*B.y; }
double Length(Vector A) { return sqrt(Dot(A,A)); }
double Angle(Vector A,Vector B) { return acos(Dot(A,B)/Length(A)/Length(B)); }

double Cross(Vector A,Vector B) { return A.x*B.y-A.y*B.x; }


int main() {
#ifdef MengLan
    int Beginning=clock();
    //freopen("in","r",stdin);
    //freopen("out","w",stdout);
#endif // MengLan





#ifdef MengLan
    printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
    return 0;
}
