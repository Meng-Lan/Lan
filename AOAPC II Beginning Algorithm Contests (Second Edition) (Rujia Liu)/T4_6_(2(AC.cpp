#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<cstring>
const int max = 10000;
const int max1 = 100;
struct Lan {
	char name[max1], sid[max1];
	int cid, score[5];
}lan[max];
const double eps = 1e-5;
int cnt = 0;
bool rmv[max];
const char* course_name[] = { "Chinese", "Mathematics", "English", "Programming" };
void print_menu() {
	printf("Welcome to Student Performance Management System (SPMS).\n\n1 - Add\n2 - Remove\n3 - Query\n4 - Show ranking\n5 - Show Statistics\n0 - Exit\n\n");
}
bool find(char * str) {
	for (int i = 0; i < cnt; i++)
		if (!rmv[i] && strcmp(lan[i].sid, str) == 0)
			return true;
	return false;
}
void add() {
	for (;;) {
		printf("Please enter the SID, CID, name and four scores. Enter 0 to finish.\n");
		scanf("%s", lan[cnt].sid);
		if (strcmp(lan[cnt].sid, "0") == 0)
			break;
		scanf("%d%s%d%d%d%d", &lan[cnt].cid, lan[cnt].name, &lan[cnt].score[0], &lan[cnt].score[1], &lan[cnt].score[2], &lan[cnt].score[3]);
			if (!find(lan[cnt].sid)) {
				lan[cnt].score[4] = lan[cnt].score[0] + lan[cnt].score[1] + lan[cnt].score[2] + lan[cnt].score[3];
				cnt++;
			}
			else
				printf("Duplicated SID.\n");
	}
}
int rank(int n) {
	int tot = 0;
	for (int i = 0; i < cnt; i++)
		if (!rmv[i]&&(lan[i].score[4]>lan[n].score[4]))
			tot++;
	return tot+1;
}
void dq(int isq) {
	char s[max1];
	for (;;) {
		printf("Please enter SID or name. Enter 0 to finish.\n");
		scanf("%s", s);
		if (strcmp(s, "0") == 0)
			break;
		int tot = 0;
		for (int i = 0; i < cnt; i++) {
			if (rmv[i])
				continue;
			if (strcmp(lan[i].sid, s) == 0 || strcmp(lan[i].name, s) == 0)
				if (isq)
					printf("%d %s %d %s %d %d %d %d %d %.2f\n", rank(i), lan[i].sid, lan[i].cid, lan[i].name, lan[i].score[0], lan[i].score[1], lan[i].score[2], lan[i].score[3], lan[i].score[4], lan[i].score[4] / 4.0 + eps);
				else {
					rmv[i] = true;
					tot++;
				}
		}
		if (!isq)
			printf("%d student(s) removed.\n", tot);
	}
}
void stat() {
	int temp;
	printf("Please enter class ID, 0 for the whole statistics.\n");
	scanf("%d", &temp);
	for (int i = 0; i < 4; i++) {
		int pass = 0, fail = 0, sum = 0;
		for (int j = 0; j < cnt; j++)
			if (!rmv[j] && (lan[j].cid == temp || temp == 0)) {
				sum += lan[j].score[i];
				if (lan[j].score[i] >= 60)
					pass++;
				else
					fail++;
			}
		printf("%s\n", course_name[i]);
		printf("Average Score: %.2f\n", (double)sum / (double)(pass + fail) + eps);
		printf("Number of passed students: %d\n", pass);
		printf("Number of failed students: %d\n", fail);
		printf("\n");
	}
	int t[5];
	memset(t, 0, sizeof(t));
	for (int i = 0; i < cnt;i++)
		if (!rmv[i] && (lan[i].cid == temp || temp == 0)) {
			int k = 0;
			for (int j = 0; j < 4; j++)
				if (lan[i].score[j] >= 60)
					k++;
			t[k]++;
		}
	printf("Overall:\n");
	printf("Number of students who passed all subjects: %d\n", t[4]);
	printf("Number of students who passed 3 or more subjects: %d\n", t[4] + t[3]);
	printf("Number of students who passed 2 or more subjects: %d\n", t[4] + t[3] + t[2]);
	printf("Number of students who passed 1 or more subjects: %d\n", t[4] + t[3] + t[2] + t[1]);
	printf("Number of students who failed all subjects: %d\n", t[0]);
	printf("\n");
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