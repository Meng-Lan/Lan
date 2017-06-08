#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
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
#define mp make_pair

struct BigInteger {
	static const int BASE = 100000000;
	static const int WIDTH = 8;
	vector<int> s;

	BigInteger(long long num = 0) {
		*this = num;
	}
	BigInteger operator =(long long num) {
		s.clear();
		do {
			s.push_back(num%BASE);
			num /= BASE;
		} while (num > 0);
		return *this;
	}
	BigInteger operator =(const string &str) {
		s.clear();
		int x, len = (str.length() - 1) / WIDTH + 1;
		for (int i = 0; i < len; i++) {
			int end = str.length() - i*WIDTH;
			int start = max(0, end - WIDTH);
			sscanf(str.substr(start, end - start).c_str(), "%d", &x);
			s.push_back(x);
		}
		return *this;
	}
	BigInteger operator + (const BigInteger &b) const {
		BigInteger c;
		c.s.clear();
		for (int i = 0, g = 0;; i++) {
			if (g == 0 && i >= s.size() && i >= b.s.size()) break;
			int x = g;
			if (i < s.size()) x += s[i];
			if (i < b.s.size()) x += b.s[i];
			c.s.push_back(x%BASE);
			g = x / BASE;
		}
		return c;
	}
	BigInteger operator +=(const BigInteger &b) {
		*this = *this + b;
		return *this;
	}

	BigInteger operator *(const BigInteger &b) const {
		BigInteger c;
		ll x = 0;
		for (int i = 0; i < s.size(); i++) {
			for (int j = 0; j < b.s.size(); j++) {
				x += (ll)s[i] * b.s[j];
				if (c.s.size() <= i + j)
					c.s.push_back(x%BASE);
				else
					c.s[i + j] += x%BASE;
				x /= BASE;
				x += c.s[i + j] / BASE;
				c.s[i + j] %= BASE;
			}
			int len = i + b.s.size();
			while (x) {
				if (c.s.size() <= len)
					c.s.push_back(x%BASE);
				else
					c.s[len] += x%BASE;
				x /= BASE;
				x += c.s[len] / BASE;
				c.s[len] %= BASE;
				++len;
			}
		}
		return c;
	}
	BigInteger operator *=(const BigInteger &b) {
		*this = *this*b;
		return *this;
	}

	BigInteger operator - (const BigInteger &b) const {
		if (*this == b)
			return BigInteger(0);
		bool sign = *this > b ? 0 : 1;
		const BigInteger &s = sign ? b : *this;
		const BigInteger &t = sign ? *this : b;
		BigInteger c;
		c.s.resize(s.s.size());
		for (int i = 0; i < s.s.size(); i++) {
			if (i >= t.s.size())
				c.s[i] = s.s[i];
			else
				c.s[i] = s.s[i] - t.s[i];
		}
		for (int i = 0; i < c.s.size(); i++)
			if (c.s[i] < 0) {
				c.s[i + 1] -= 1;
				c.s[i] += BASE;
			}
		for (int i = c.s.size() - 1; i >= 0; i--)
			if (c.s[i] == 0)
				c.s.erase(c.s.begin() + i);
			else
				break;
		if (sign)
			c.s[c.s.size() - 1] = 0 - c.s[c.s.size() - 1];
		return c;
	}
	BigInteger operator -=(const BigInteger &b) {
		*this = *this - b;
		return *this;
	}

	bool operator < (const BigInteger &b) const {
		if (s.size() != b.s.size()) return s.size() < b.s.size();
		for (int i = s.size() - 1; i >= 0; i--)
			if (s[i] != b.s[i]) return s[i] < b.s[i];
		return false;
	}
	bool operator > (const BigInteger &b) const {
		return b < *this;
	}
	bool operator <=(const BigInteger &b) const {
		return !(b < *this);
	}
	bool operator >=(const BigInteger &b) const {
		return !(*this < b);
	}
	bool operator !=(const BigInteger &b) const {
		return !(*this == b);
	}
	bool operator ==(const BigInteger &b) const {
		return s == b.s;
	}

};

ostream& operator <<(ostream &out, const BigInteger &x) {
	out << x.s.back();
	for (int i = x.s.size() - 2; i >= 0; i--) {
		char buf[20];
		sprintf(buf, "%08d", x.s[i]);
		for (int j = 0; j < strlen(buf); j++)
			out << buf[j];
	}
	return out;
}

istream& operator >>(istream &in, BigInteger &x) {
	string s;
	if (!(in >> s)) return in;
	x = s;
	return in;
}

const int maxn = 5005;
BigInteger num[maxn];
int main() {
	int n;
	cin >> n;
	num[1] = 1;
	num[2] = 2;
	for (int i = 3; i <= n; i++)
		num[i] = num[i - 1] + num[i - 2];
	cout << num[n] << endl;
	return 0;
}