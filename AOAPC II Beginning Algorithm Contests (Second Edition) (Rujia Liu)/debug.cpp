#include<set>
#include<map>
#include<list>
#include<queue>
#include<stack>
#include<string>
#include<math.h>
#include<time.h>
#include<vector>
#include<bitset>
#include<memory>
#include<utility>
#include<stdio.h>
#include<sstream>
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<algorithm>
using namespace std;
int a[10010] = { 0 }, b[10010] = { 0 }, c[20020] = { 0 };//c=a*b��abc���ǵ��Ŵ��
int la, lb, lc;//�ֱ��a��b��c
int i, j;//ѭ�����Ʊ���
string ch;//����ʱ���õ�
void chengfa(int x[10010], int y[10010], int z[20020], int lx, int ly)//�˷��Ĺ���
{
	for (i = 1; i <= lx; i++)//�˵Ĺ���
		for (j = 1; j <= ly; j++)
		{
			z[i + j - 1] += x[i] * y[j];//�˽�ȥ
			z[i + j] += z[i + j - 1] / 10;//��λ
			z[i + j - 1] %= 10;//��λ
		}
}
int main()
{
	/////////////////////���벿��///////////////////////////////////////////////////
	cin >> ch;//�����һ����
	int haha = ch.size() - 1;//�����һ�����ĳ���
	la = 0;
	for (i = haha; i >= 0; i--)//���Ŵ浽A������
	{
		la++;//���Ҳ�Ǵ�λ����
		a[la] = (int)(ch[i]) - 48; //���ȥ
	}
	cin >> ch;//����ڶ�����
	haha = ch.size() - 1;//����ڶ������ĳ���
	lb = 0;
	for (i = haha; i >= 0; i--)//���Ŵ浽B������
	{
		lb++;//���Ҳ�Ǵ�λ����
		b[lb] = (int)(ch[i]) - 48; //���ȥ
	}
	///////////////////////�˷�����/////////////////////////////////////////////////
	chengfa(a, b, c, la, lb);
	///////////////////////�������/////////////////////////////////////////////////
	if (a[1] == 0 && b[1] == 0) cout << 0;//�������
	lc = la + lb;//c�����ô��
	int hehe = 0;//�����
	for (i = lc; i >= 1; i--)//���ʱ���ǵ��Ŵ����ʱ��Ҫ�������
	{
		if (c[i] != 0) hehe = 1;//�ҵ���һ����Ϊ0����
		if (hehe == 1) printf("%d", c[i]); //���
	}
	return 0;
}