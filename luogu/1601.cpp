#include<iostream>
#include<cstdio>
#include<cstring>
char str1[1005], str[1005],str2[1005];
int main(){
	using std::cin;
	using std::cout;
	using std::endl;
	cin >> str1 >> str2;
	int len1 = strlen(str1);
	int len2 = strlen(str2);
	int max = len1 > len2 ? len1 : len2;
	int min = len1 < len2 ? len1 : len2;
	for (int i = 0; i < min;i++){
		for(int 