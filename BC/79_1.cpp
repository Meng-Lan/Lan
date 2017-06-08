#include <stdio.h>

char*s = "#include <stdio.h>%cchar*s=%c%s%c;%cintmain(){printf(s,10,34,s,34,10,10);return0;}%c";

int main() {
	printf(s, 10, 34, s, 34, 10, 10);
	return 0;

}