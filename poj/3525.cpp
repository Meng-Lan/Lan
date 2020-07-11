#include<iostream>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
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

const int INF=1e6;
const double eps = 1e-6;
int dcmp(double x) {
  if(fabs(x) < eps) return 0; else return x < 0 ? -1 : 1;
}

const double PI = acos(-1);

struct Point {
  double x, y;
  Point(double x=0, double y=0):x(x),y(y) { }
};

typedef Point Vector;

Vector operator + (Vector A, Vector B) { return Vector(A.x+B.x, A.y+B.y); }
Vector operator - (Point A, Point B) { return Vector(A.x-B.x, A.y-B.y); }
Vector operator * (Vector A, double p) { return Vector(A.x*p, A.y*p); }
Vector operator / (Vector A, double p) { return Vector(A.x/p, A.y/p); }

bool operator < (const Point& a, const Point& b) {
  return a.x < b.x || (a.x == b.x && a.y < b.y);
}

bool operator == (const Point& a, const Point &b) {
  return dcmp(a.x-b.x) == 0 && dcmp(a.y-b.y) == 0;
}

double Dot(Vector A, Vector B) { return A.x*B.x + A.y*B.y; }
double Length(Vector A) { return sqrt(Dot(A, A)); }
double Angle(Vector A, Vector B) { return acos(Dot(A, B) / Length(A) / Length(B)); }
double Cross(Vector A, Vector B) { return A.x*B.y - A.y*B.x; }

Vector Rotate(Vector A, double rad) {
  return Vector(A.x*cos(rad)-A.y*sin(rad), A.x*sin(rad)+A.y*cos(rad));
}

Vector Normal(Vector A) {
  double L = Length(A);
  return Vector(-A.y/L, A.x/L);
}

Point GetLineIntersection(Point P, Point v, Point Q, Point w) {
  Vector u = P-Q;
  double t = Cross(w, u) / Cross(v, w);
  return P+v*t;
}

Point GetLineProjection(Point P, Point A, Point B) {
  Vector v = B-A;
  return A+v*(Dot(v, P-A) / Dot(v, v));
}

double DistanceToLine(Point P, Point A, Point B) {
  Vector v1 = B - A, v2 = P - A;
  return fabs(Cross(v1, v2)) / Length(v1); // 如果不取绝对值，得到的是有向距离
}

struct Line {
  Point p;
  Vector v;
  Line(Point p, Vector v):p(p),v(v) { }
  Point point(double t) {
    return p + v*t;
  }
  Line move(double d) {
    return Line(p + Normal(v)*d, v);
  }
};

Point GetLineIntersection(Line a, Line b) {
  return GetLineIntersection(a.p, a.v, b.p, b.v);
}

double angle(Vector v) {
  return atan2(v.y, v.x);
}

int n;
std::vector<Point> in;

void cut(std::vector<Point> &p,Line l){
  std::vector<Point> t;
  FOR(i,0,p.size()){
    if(Cross(l.v,p[i]-l.p)>=0) t.pb(p[i]);
    else{
      int j=i-1;
      if(j<0) j+=p.size();
      if(Cross(l.v,p[j]-l.p)>=0) t.pb(GetLineIntersection(Line(p[j],p[i]-p[j]),l));
      j=i+1;
      if(j>=p.size()) j-=p.size();
      if(Cross(l.v,p[j]-l.p)>=0) t.pb(GetLineIntersection(Line(p[i],p[j]-p[i]),l));
    }
  }
  // printf("line p x:%f y:%f v x:%f y:%f\n",l.p.x,l.p.y,l.v.x,l.v.y);
  // PV(t.size());
  // for(auto v:t) printf("x:%f y:%f\n",v.x,v.y);
  p=t;
}

bool check(double m){
  std::vector<Point> p;
  p.pb(Point(-INF,-INF));
  p.pb(Point(INF,-INF));
  p.pb(Point(INF,INF));
  p.pb(Point(-INF,INF));
  std::vector<Line> lines;
  FOR(i,0,n) lines.pb(Line(in[i],in[i+1]-in[i]).move(m));
  FOR(i,0,n) cut(p,lines[i]);
  // PV(p.size());
  // for(auto &v:p) printf("x:%f y:%f\n",v.x,v.y);
  return !p.empty();
}

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

  while(scanf("%d",&n)==1&&n){
    in.clear();
    FOR(i,0,n){int x,y;scanf("%d%d",&x,&y);in.pb(Point(x,y));}
    in.pb(in[0]);
    double l=0,r=1e9;
    // check(494);
    FOR(i,0,100){
      double m=(l+r)*0.5;
      if(check(m)) l=m;
      else r=m;
    }
    printf("%.6f\n",l);
  }

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
