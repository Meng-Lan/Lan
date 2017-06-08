#include<iostream>
int num[13];
int main() {
	for (int a = 1; a <= 12; a++)
		for (int b = 1; b <= 12; b++)
			for (int c = 1; c <= 12; c++)
				for (int d = 1; d <= 12; d++)
					for (int e = 1; e <= 12; e++)
						for (int f = 1; f <= 12; f++)
							for (int g = 1; g <= 12; g++)
								for (int h = 1; h <= 12; h++)
									for (int i = 1; i <= 12; i++) {
										memset(num, 0, sizeof(num));
										num[a]++;
										num[b]++;
										num[c]++;
										num[d]++;
										num[e]++;
										num[f]++;
										num[g]++;
										num[h]++;
										num[i]++;
										if (num[1] || num[3] || num[8])
											continue;
										int off = 0;
										for (int j = 2; j < 13; j++)
											if (num[j]>1)
												off = 1;
										if (off)
											continue;
										int temp = 8 + i + g + 3;
										if (8 + a + b + c != temp || c + d + f + 3 != temp ||
											h + i + a + 1 != temp || 1 + b + d + e != temp ||
											h + g + f + e != temp)
											continue;
										else
											printf("%d\n", i);
									}
	printf("break");
	return 0;
}