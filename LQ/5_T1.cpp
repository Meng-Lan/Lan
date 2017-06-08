#include<iostream>
int main() {
	int p = 23, y = 19;
	for (int i = 0; i < 40; i++)
		for (int j = 0; j < 50; j++)
			if (i*p + j*y == 823)
				std::cout << i << "  " << j << "  ";
	return 0;
}