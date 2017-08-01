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
	if (n-r < r) r=n-r;
	ll ansn=1,ansr=1;
	for (ll i=n-r+1; i<=n; ++i) ansn*=i;
	for (ll j=1; j<=r; ++j) ansr*=j;
	return ansn/ansr;
}
ll gcd(ll a,ll b) { return b?gcd(b,a%b):a; }
ll lcm(ll a,ll b) { return a/gcd(a,b)*b; }
std::vector<int> Eratosthenes(const int len,int *vis) {
	memset(vis,0,sizeof(int)*len);
	std::vector<int> prime;
	int m=(int)sqrt(len+0.5);
	For(i,2,m) if (!vis[i]) for (int j=i*i; j < len; j+=i) vis[j]=1;
	FOR(i,2,len) if (!vis[i]) prime.push_back(i);
	return prime;
}
void phi_table(int n,int *phi) {
	For(i,2,n) phi[i]=0;
	phi[1]=1;
	For(i,2,n) if (!phi[i])
		for (int j=i; j<=n; j+=i) {
			if (!phi[j]) phi[j]=j;
			phi[j]=phi[j]/i*(i-1);
		}
}

const double PI=acos(-1);
struct Point {
	double x,y;
	Point(double x=0,double y=0) :x(x),y(y) {}
};
typedef Point Vector;
Vector operator+(Vector A,Vector B) { return Vector(A.x+B.x,A.y+B.y); }
Vector operator-(Vector A,Vector B) { return Vector(A.x-B.x,A.y-B.y); }
const double eps=1e-10;
int dcmp(double x) { if (fabs(x)<eps)return 0;else return x<0?-1:1; }
bool operator==(const Point &a,const Point &b) { return dcmp(a.x-b.x)==0&&dcmp(a.y-b.y)==0; }
const int maxn=1e5+10;
Point dot[maxn];
int n;
double a;
double Dot(Vector A,Vector B) { return A.x*B.x+A.y*B.y; }
double Length(Vector A) { return sqrt(Dot(A,A)); }
double Angle(Vector A,Vector B) { return acos(Dot(A,B)/Length(A)/Length(B)); }
Vector Rotate(Vector A,double rad) { return Vector(A.x*cos(rad)-A.y*sin(rad),A.x*sin(rad)+A.y*cos(rad)); }

int main() {
#ifdef MengLan
	int Beginning=clock();
#endif // MengLan

	scanf("%d%lf",&n,&a);
	double angle=0,add=360.0/n;
	//cout<<angle<<' '<<add<<endl;
	add=PI/180*add;angle+=add;
	dot[0]=Vector(0,0);dot[1]=Vector(1,0);
	FOR(i,2,n) { dot[i]=dot[i-1]+Rotate(dot[i-1]-dot[i-2],add);add; }
	//FOR(i,0,n) printf("#%d x:%f y:%f\n",i,dot[i].x,dot[i].y);
	double ans=acos(-1);
	a=PI/180*a;
	int ta=0,tb=1,tc=0;
	FOR(i,2,n) {
		double tmp=Angle(dot[0]-dot[1],dot[i]-dot[1]);
		//printf("#%d at:%d tmp:%f\n",i,1,tmp);
		if (fabs(tmp-a)<ans) { ta=0;tb=1;tc=i; ans=fabs(tmp-a); }
		tmp=Angle(dot[1]-dot[0],dot[i]-dot[0]);
		//printf("#%d at:%d tmp:%f\n",i,2,tmp);
		if (fabs(tmp-a)<ans) { ta=1;tb=0;tc=i;ans=fabs(tmp-a); }
	}
	printf("%d %d %d\n",ta+1,tb+1,tc+1);


#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
#endif // MengLan
	return 0;
}