#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<sstream>
#include<vector>
#include<map>
#include<set>
#include<utility>
#include<queue>
#include<stack>
#include<algorithm>
#include<cstdlib>
using namespace std;
typedef long long ll;
typedef pair<int, int> P;
#define FOR(i,len) for(int i=0;i<(len);++i)
#define For(i,len) for(int i=0;i<=(len);++i)
#define rep(i,init,len) for(int i=(init);i<(len);++i)
#define mp make_pair


struct person {
	string name, address;
	string get_name() const {
		return name;
	}
	string get_address()const {
		return address;
	}
};

istream &read(istream &in, person &t) {
	in >> t.name >> t.address;
	return in;
}

ostream &print(ostream &out, const person &t) {
	out << t.name << endl << t.address;
	return out;
}


