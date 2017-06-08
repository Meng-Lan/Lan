#include<iostream>
int n, ans, r[15], tot;
void search(int);
int main() {
	std::cin >> n;
	search(0);
	std::cout << ans << std::endl;
	return 0;
}
void search(int cur) {
	if (cur == n) {
		if (tot < 3) {
			for (int i = 0; i < n; i++)
				printf("%d ", r[i]+1);
			printf("\n");
			tot++;
		}
		ans++;
	}
	else
		for (int i = 0; i < n; i++) {
			int ok = 1;
			r[cur] = i;
			for (int j = 0; j < cur; j++)
				if (r[cur] == r[j] || cur + r[cur] == r[j] + j || cur - r[cur] == j - r[j]) {
					ok = 0;
					break;
				}
			if (ok)
				search(cur + 1);
		}

}