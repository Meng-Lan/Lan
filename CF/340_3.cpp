#include<iostream>
#include<cstdio>
long long num[2005][5];
int main() {
	long long n, x1, x2, y1, y2;
	std::cin >> n >> x1 >> y1 >> x2 >> y2;
	long long temp = 0;
	for (int i = 0; i < n; i++) {
		std::cin >> num[i][0] >> num[i][1];
		num[i][2] = (num[i][0] - x1)*(num[i][0] - x1) + (num[i][1] - y1)*(num[i][1] - y1);
		//std::cout << num[i][2] << "    ";
		num[i][3] = (num[i][0] - x2)*(num[i][0] - x2) + (num[i][1] - y2)*(num[i][1] - y2);
		if (num[i][2] <= num[i][3])
			num[i][4] = 1;
		else
			num[i][4] = 2;
		//std::cout << num[i][3] << std::endl;
	}
	long long r1, r2, tr1, tr2;
	r1 = r2 = tr1 = tr2 = 0;
	for (int i = 0; i < n; i++) {
		if (num[i][4] == 1) {
			if (num[i][2]>r1)
				r1 = num[i][2];
		}
		else if (num[i][4] == 2)
			if (num[i][3]>tr2)
				tr2 = num[i][3];
	}
	for (int i = 0; i < n; i++) {
		if (num[i][4] == 2) {
			if (num[i][2]>r1)
				if (num[i][3] > r2)
					r2 = num[i][3];
		}
		else if (num[i][4] == 1)
			if (num[i][3] > tr2)
				tr1 = num[i][2];
	}
	if ((r1 + r2) >= (tr1 + tr2))
		temp = tr1 + tr2;
	else
		temp = r1 + r2;
	std::cout << temp << std::endl;
	return 0;
}