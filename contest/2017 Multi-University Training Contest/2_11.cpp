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
#define mp std::make_pair
ll Factorial(ll i) { return i > 1?i*Factorial(i-1):1; }
ll Combination(ll n,ll r) {
	if(n-r < r) r=n-r;
	ll ansn=1,ansr=1;
	for(ll i=n-r+1; i<=n; ++i) ansn*=i;
	for(ll j=1; j<=r; ++j) ansr*=j;
	return ansn/ansr;
}
ll gcd(ll a,ll b) { return b?gcd(b,a%b):a; }
ll lcm(ll a,ll b) { return a/gcd(a,b)*b; }
std::vector<int> Eratosthenes(const int len,int *vis) {
	memset(vis,0,sizeof(int)*len);
	std::vector<int> prime;
	int m=(int)sqrt(len+0.5);
	For(i,2,m) if(!vis[i]) for(int j=i*i; j < len; j+=i) vis[j]=1;
	FOR(i,2,len) if(!vis[i]) prime.push_back(i);
	return prime;
}
void phi_table(int n,int *phi) {
	For(i,2,n) phi[i]=0;
	phi[1]=1;
	For(i,2,n) if(!phi[i])
		for(int j=i; j<=n; j+=i) {
			if(!phi[j]) phi[j]=j;
			phi[j]=phi[j]/i*(i-1);
		}
}

struct Point {
	double x,y;
	Point(double x=0,double y=0) :x(x),y(y) {}
};

typedef Point Vector;

Vector operator + (const Vector& A,const Vector& B) { return Vector(A.x+B.x,A.y+B.y); }
Vector operator - (const Point& A,const Point& B) { return Vector(A.x-B.x,A.y-B.y); }
Vector operator * (const Vector& A,double p) { return Vector(A.x*p,A.y*p); }
const double eps=1e-10;
int dcmp(double x) {
	if(fabs(x)<eps) return 0;else return x<0?-1:1;
}
bool operator < (const Point& a,const Point& b) {
	return dcmp(a.x-b.x)==-1||dcmp(a.x-b.x)==0&&dcmp(a.y-b.y)==-1;
}
double Dot(const Vector& A,const Vector& B) { return A.x*B.x+A.y*B.y; }
double Length(const Vector& A) { return sqrt(Dot(A,A)); }
double Angle(const Vector& A,const Vector& B) { return acos(Dot(A,B)/Length(A)/Length(B)); }
double Cross(const Vector& A,const Vector& B) { return A.x*B.y-A.y*B.x; }

Point GetLineIntersection(const Point& P,const Point& v,const Point& Q,const Point& w) {
	Vector u=P-Q;
	double t=Cross(w,u)/Cross(v,w);
	return P+v*t;
}

Vector Rotate(const Vector& A,double rad) {
	return Vector(A.x*cos(rad)-A.y*sin(rad),A.x*sin(rad)+A.y*cos(rad));
}

Point read_point() {
	double x,y;
	scanf("%lf%lf",&x,&y);
	return Point(x,y);
}

const double PI=acos(-1);
const int maxn=500+10;
Point in[maxn];
int n;

void print(Point p) {
	printf("(%.3f,%.3f) ",p.x,p.y);
}

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	//cout<<PI<<endl;
	while(scanf("%d",&n)==1&&n) {
		std::set<Point> s;
		FOR(i,0,n) { in[i]=read_point();s.insert(in[i]); }
		int ans=0;
		FOR(i,0,n) FOR(j,0,n) if(i!=j){
			Point edge=Rotate(in[j]-in[i],PI/2);
			Point a=in[i]+edge;
			Point b=in[j]+edge;
			//print(in[i]);print(in[j]);print(a);print(b);puts("");
			if(s.find(a)!=s.end()&&s.find(b)!=s.end()) ++ans;
		}
		cout<<ans/4<<endl;
	}


#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}