#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<cstring>
const int max = 10000;
const int max1 = 100;
struct Lan {
	char name[max1],sid[max1];
	int cid, chinese, math, english, program, sum;
	double average;
}lan[max];
double eps = 1e-5;
int cnt = 0;
void print_menu() {
	printf("Welcome to Student Performance Management System (SPMS).\n\n1 - Add\n2 - Remove\n3 - Query\n4 - Show ranking\n5 - Show Statistics\n0 - Exit\n\n");
}
int rank(int n) {
	int num = 1;
	for (int i = 0; i < cnt; i++)
		if (lan[i].sum>lan[n].sum)
			num++;
	return num;
}
void add() {
	char s[max1];
	for (;;) {
		printf("Please enter the SID, CID, name and four scores. Enter 0 to finish.\n");
		scanf("%s",s);
		if (strcmp(s,"0")==0)
			break;
		else {
			int off = 0;
			for (int i = 0; i < cnt&&i < max; i++) {
				if (strcmp(s, lan[i].sid) == 0) {
					printf("Duplicated SID.\n");
					off = 1;
					break;
				}
			}
			strcpy(lan[cnt].sid, s);
			scanf("%d%s%d%d%d%d", &lan[cnt].cid, lan[cnt].name, &lan[cnt].chinese, &lan[cnt].math, &lan[cnt].english, &lan[cnt].program);
			lan[cnt].sum = lan[cnt].chinese + lan[cnt].math + lan[cnt].english + lan[cnt].program;
			lan[cnt].average = lan[cnt].sum / 4.0 + eps;
			if(!off)
				cnt++;
		}
	}
}
void del(Lan &temp) {
	temp.average = temp.chinese = temp.cid = temp.english = temp.math = temp.program = temp.sum = -1;
	strcpy(temp.sid, "-1");
	strcpy(temp.name, "*");
}
void dq(int isq) {
	char s[max1];
	for (;;) {
		printf("Please enter SID or name. Enter 0 to finish.\n");
		scanf("%s", s);
		if (strcmp(s, "0") == 0)
			break;
		int r = 0;
		for (int i = 0; i < cnt; i++)
			if (lan[i].cid != -1) {
				if (strcmp(lan[i].sid, s) == 0 || strcmp(lan[i].name, s) == 0) {
					if (isq)
						printf("%d %s %d %s %d %d %d %d %d %.2f\n", rank(i), lan[i].sid, lan[i].cid, lan[i].name, lan[i].chinese, lan[i].math, lan[i].english, lan[i].program, lan[i].sum, lan[i].average);
					else {
						del(lan[i]);
						r++;
					}
				}
			}
		if (!isq)
			printf("%d student(s) removed.\n", r);
	}
}
void QAQ(int cid, int *n, double *num) {
	for (int i = 0; i < cnt; i++)
		if ((lan[i].cid == cid||cid==0)&&lan[i].cid!=-1) {
			int temp = 0;
			if (lan[i].chinese >= 60) {
				temp++;
				n[1]++;
			}
			else
				n[2]++;
			num[0] += lan[i].chinese;
			if (lan[i].math >= 60) {
				temp++;
				n[3]++;
			}
			else
				n[4]++;
			num[1] += lan[i].math;
			if (lan[i].english >= 60) {
				temp++;
				n[5]++;
			}
			else
				n[6]++;
			num[2] += lan[i].english;
			if (lan[i].program >= 60) {
				temp++;
				n[7]++;
			}
			else
				n[8]++;
			num[3] += lan[i].program;
			n[13-temp]++;
			n[0]++;
		}
}
void stat() {
	int cid;
	printf("Please enter class ID, 0 for the whole statistics.\n");
	scanf("%d", &cid);
	int n[14] = { 0 };
	double num[4] = { 0 };
	QAQ(cid,n, num);
	printf("Chinese\nAverage Score: %.2f\nNumber of passed students: %d\nNumber of failed students: %d\n\n", num[0]/n[0], n[1], n[2]);
	printf("Mathematics\nAverage Score: %.2f\nNumber of passed students: %d\nNumber of failed students: %d\n\n", num[1]/n[0], n[3], n[4]);
	printf("English\nAverage Score: %.2f\nNumber of passed students: %d\nNumber of failed students: %d\n\n", num[2]/n[0], n[5], n[6]);
	printf("Programming\nAverage Score: %.2f\nNumber of passed students: %d\nNumber of failed students: %d\n\n", num[3]/n[0], n[7], n[8]);
	printf("Overall:\nNumber of students who passed all subjects: %d\nNumber of students who passed 3 or more subjects: %d\nNumber of students who passed 2 or more subjects: %d\nNumber of students who passed 1 or more subjects: %d\nNumber of students who failed all subjects: %d\n\n",n[9],n[9]+n[10],n[9]+n[10]+n[11], n[9] + n[10] + n[11]+n[12],n[13]);
}
int main() {
	for (;;) {
		int choice;
		print_menu();
		/*for (int i = 0; i < cnt;i++)
			printf("%d %s %d %s %d %d %d %d %d %.2f\n", i, lan[i].sid, lan[i].cid, lan[i].name, lan[i].chinese, lan[i].math, lan[i].english, lan[i].program, lan[i].sum, lan[i].average);*/
		scanf("%d", &choice);
		if (choice == 0)
			break;
		if (choice == 1)
			add();
		if (choice == 2)
			dq(0);
		if (choice == 3)
			dq(1);
		if (choice == 4)
			printf("Showing the ranklist hurts students' self-esteem. Don't do that.\n");
		if (choice == 5)
			stat();
	}
	return 0;
}