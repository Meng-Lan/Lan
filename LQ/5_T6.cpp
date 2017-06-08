#include <cstdio> 
using namespace std; int sum = 0; int main() {  for(int a = 1; a <= 9; a++)   { 
for (int b = 1; b <= 9; b++) { for (int c = 1; c <= 9; c++) { for (int d = 1; d <= 9; d++) { if (a == b && c == d)        continue;       int na = a * 10 + c, nb = b * 10 + d;            if (a * 1.0 / b * c * 1.0 / d >= na * 1.0 / nb - 0.000001  &&         a * 1.0 / b * c * 1.0 / d <= na * 1.0 / nb + 0.000001) { printf("%d/%d * %d/%d = %d/%d\n", a, b, c, d, na, nb);       sum++; } } } }  }
printf("sum = %d", sum);  return 0;  }