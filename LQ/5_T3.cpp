#include <cstdio> 
using namespace std; int sum = 0; char str[100];  int Fun(int now, int i, int a, int b) {
	if (now < 0 || i > 16 || (now == 0 && i < 16))    return 0;   if (now == 0) {
		if (i == 16 && a == 5 && b == 10) {
			sum++;
			for (int j = 0; j < 15; j++)      putchar(str[j]);     putchar(10);
		}
	}   str[i - 1] = 'a';   Fun(now * 2, i + 1, a + 1, b);  str[i - 1] = 'b';   Fun(now - 1, i + 1, a, b + 1);
}
int main() { str[15] = '\0';  Fun(2, 1, 0, 0);   printf("sum = %d\n", sum);  return 0; }