#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
char str[2][3] = { "H","He" };
char str2[8][3] = { "Li","Be","B","C","N","O","F" };
char str3[8][3] = { "Na","Mg","Al","Si","P","S","Cl" };
char str4[17][3] = { "K","Ca","Sc","T","V","Cr","Mn","Fe","Co","Ni","Cu","Zn","Ga","Ge","As","Se","Br" };
char str5[17][3] = { "Rb","Sr","Y","Zr","Nb","Mo","Tc","Ru","Rh","Pd","Ag","Cd","In","Sn","Sb","Te","I"};
char str6[17][3] = { "Cs","Ba","La","Hf","Ta","W","Re","Os","Ir","Pt","Au","Hg","Tl","Pb","Bi","Po","At"};
char str7[17][4] = { "Fr","Ra","Ac","Rf","Db","Sg","Bh","Hs","Mt","Ds","Rg","Cn","Uut","Fl","Uup","Lv","Uus"};
int main() {
	int x, y;
	while (scanf("%d%d", &x, &y) != EOF) {
		if (x == 1)
			printf("%s\n", str[y - 1]);
		if (x == 2)
			printf("%s\n", str2[y - 1]);
		if (x == 3)
			printf("%s\n", str3[y - 1]);
		if (x == 4)
			printf("%s\n", str4[y - 1]);
		if (x == 5)
			printf("%s\n", str5[y - 1]);
		if (x == 6)
			printf("%s\n", str6[y - 1]);
		if (x == 7)
			printf("%s\n", str7[y - 1]);
	}
	return 0;
}