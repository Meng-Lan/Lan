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
typedef std::pair<int, int> P;
#define FOR(i,init,len) for(int i=(init);i<(len);++i)
#define For(i,init,len) for(int i=(init);i<=(len);++i)
#define mp std::make_pair
ll Factorial(ll i) { return i > 1 ? i*Factorial(i - 1) : 1; }
ll Combination(ll n, ll r) {
	if (n - r < r) r = n - r;
	ll ansn = 1, ansr = 1;
	for (ll i = n - r + 1; i <= n; ++i) ansn *= i;
	for (ll j = 1; j <= r; ++j) ansr *= j;
	return ansn / ansr;
}
ll gcd(ll a, ll b) { return b ? gcd(b, a%b) : a; }
ll lcm(ll a, ll b) { return a / gcd(a, b)*b; }
std::vector<int> Eratosthenes(const int len, int *vis) {
	memset(vis, 0, sizeof(int)*len);
	std::vector<int> prime;
	int m = (int)sqrt(len + 0.5);
	For(i, 2, m) if (!vis[i]) for (int j = i*i; j < len; j += i) vis[j] = 1;
	FOR(i, 2, len) if (!vis[i]) prime.push_back(i);
	return prime;
}
void phi_table(int n, int *phi) {
	For(i, 2, n) phi[i] = 0;
	phi[1] = 1;
	For(i, 2, n) if (!phi[i])
		for (int j = i; j <= n; j += i) {
			if (!phi[j]) phi[j] = j;
			phi[j] = phi[j] / i*(i - 1);
		}
}

const int maxn = 55;
const int maxks = maxn*(maxn + 1) / 2;
const double eps = 1e-8;

int n, nks;

struct Event {
	double t;
	int newks, oldks;
	Event(double t = 0, int newks = 0, int oldks = 0) :t(t), newks(newks), oldks(oldks) {}
	bool operator <(const Event &rhs) const {
		return t - rhs.t < 0;
	}
};
std::vector<Event> events;

struct KineticPoint {
	double x, y, z;
	double vx, vy, vz;
	void read() {
		scanf("%lf%lf%lf%lf%lf%lf", &x, &y, &z, &vx, &vy, &vz);
	}
}kp[maxn];

struct KineticSegment {
	double a, b, c;
	int u, v;
	bool operator<(const KineticSegment &rhs)const {
		return c - rhs.c < 0;
	}
}ks[maxks];

inline double sqr(double x) { return x*x; }

int pa[maxn];

void init_ufset() { FOR(i, 0, n) pa[i] = i; }
int findset(int x) { return pa[x] != x ? pa[x] = findset(pa[x]) : x; }

void make_segments() {
	nks = 0;
	FOR(i, 0, n) FOR(j, i + 1, n) {
		ks[nks].a = sqr(kp[i].vx - kp[j].vx) + sqr(kp[i].vy - kp[j].vy) + sqr(kp[i].vz - kp[j].vz);
		ks[nks].b = 2 * ((kp[i].x - kp[j].x)*(kp[i].vx - kp[j].vx) + (kp[i].y - kp[j].y)*(kp[i].vy - kp[j].vy) + (kp[i].z - kp[j].z)*(kp[i].vz - kp[j].vz));
		ks[nks].c = sqr(kp[i].x - kp[j].x) + sqr(kp[i].y - kp[j].y) + sqr(kp[i].z - kp[j].z);
		ks[nks].u = i;
		ks[nks].v = j;
		++nks;
	}
	std::sort(ks, ks + nks);
}

void make_events() {
	events.clear();
	FOR(i, 0, nks) FOR(j, i + 1, nks) {
		int s1 = i, s2 = j;
		if (ks[s1].a - ks[s2].a < 0) std::swap(s1, s2);

		double a = ks[s1].a - ks[s2].a;
		double b = ks[s1].b - ks[s2].b;
		double c = ks[s1].c - ks[s2].c;
		if (fabs(a) < eps) {
			if (fabs(b) < eps) continue;
			if (b > 0) { std::swap(s1, s2); b = -b; c = -c; }
			if (c > 0) events.push_back(Event(-c / b, s1, s2));
			continue;
		}
		double delta = b*b - 4 * a*c;
		if (delta < eps) continue;
		delta = sqrt(delta);
		double t1 = -(b + delta) / (2 * a);
		double t2 = (delta - b) / (2 * a);
		if (t1 > 0) events.push_back(Event(t1, s1, s2));
		if (t2 > 0) events.push_back(Event(t2, s2, s1));
	}
	std::sort(events.begin(), events.end());
}

int solve() {
	int pos[maxks], e[maxn];
	init_ufset();
	FOR(i, 0, nks) pos[i] = 0;
	int idx = 0;
	FOR(i, 0, nks) {
		int u = findset(ks[i].u), v = findset(ks[i].v);
		if (u != v) {
			e[pos[i] = ++idx] = i;
			pa[u] = v;
		}
		if (idx == n - 1) break;
	}

	int ans = 1;
	FOR(i, 0, events.size()) {
		if (pos[events[i].oldks] && !pos[events[i].newks]) {
			init_ufset();
			int oldpos = pos[events[i].oldks];
			FOR(j, 1, n) if (j != oldpos) {
				int u = findset(ks[e[j]].u), v = findset(ks[e[j]].v);
				if (u != v) pa[u] = v;
			}
			int u = findset(ks[events[i].newks].u), v = findset(ks[events[i].newks].v);
			if (u != v) {
				++ans;
				pos[events[i].newks] = oldpos;
				e[oldpos] = events[i].newks;
				pos[events[i].oldks] = 0;
			}
		}
	}
	return ans;
}

int main() {
#ifdef MengLan
	int Beginning = clock();
#endif // MengLan

	int kase = 0;
	while (scanf("%d", &n) == 1) {
		FOR(i, 0, n) kp[i].read();
		make_segments();
		make_events();
		int ans = solve();
		printf("Case %d: %d\n", ++kase, ans);
	}



#ifdef MengLan
	printf("Time: %d\n", clock() - Beginning);
#endif // MengLan
	return 0;
}