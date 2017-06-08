#include<iostream>
double min(double a, double b) {
	return a > b ? b : a;
}
int main() {
	double a, b, c;
	int n;
	using std::cin;
	using std::cout;
	using std::endl;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a >> b >> c;
		if (a > 0) {
			int t = b*b - 4 * a*c;
			int minn = (4 * a*c - b*b) / (4 * a);
			double mid = -(b / 2 * a);
			//printf("min=%lf\n", mid);
			if ((mid >= 0 && mid <= 100) && minn <= 0)
				printf("0\n");
			else if (mid >= 0 && mid <= 100)
				printf("%d\n", minn);
			else {
				int x1 = c;
				int x2 = a * 10000 + b * 100 + c;
				printf("%.0lf\n", min(x1, x2));
			}
		}
		else if(a<0) {
			int x1 = c;
			int x2 = a * 10000 + b * 100 + c;
			if (min(x1, x2) <= 0)
				printf("0\n");
			else
				printf("%.0lf\n", min(x1, x2));
		}
		else {
			int x1 = c;
			int x2 = b * 100 + c;
			if (min(x1, x2) <= 0)
				printf("0\n");
			else
				printf("%.0lf\n", min(x1, x2));
		}
	}
	return 0;
}