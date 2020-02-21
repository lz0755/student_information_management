#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <conio.h>

#define USR_NAME_LEN 30
#define USR_PWD_LEN 30

typedef struct usr_account_tag
{
	char usr_name[USR_NAME_LEN];
	char usr_pwd[USR_PWD_LEN];
	int usr_role;
	struct usr_account_tag* pNext_Usr_Account;
}USR_ACCOUNT, * pUSR_ACCOUNT;
typedef struct usr_infor_tag
{
	int usr_id;
	char usr_name[USR_NAME_LEN];
	int usr_course_id;
	int usr_course_score;
	struct usr_infor_tag* pNext_Usr_Infor;
}USR_INFOR, * pUSR_INFOR;

int system_init();
void account_tail_insert(pUSR_ACCOUNT* phead, pUSR_ACCOUNT* ptail, char* name, char* passwd, int role);
void stu_tail_insert(pUSR_INFOR* phead, pUSR_INFOR* ptail, int id, char* name, int course, int score);
void modify_stu(pUSR_INFOR phead, int id, int course, int score);
void modify_usr(pUSR_ACCOUNT phead, char* name, char* passwd);
void delete_stu(pUSR_INFOR* phead, pUSR_INFOR* ptail, int i);
void delete_usr(pUSR_ACCOUNT* phead, pUSR_ACCOUNT* ptail, char* name);
void search_usr(pUSR_ACCOUNT phead, char* name);
void search_stu_byid(pUSR_INFOR phead, int id);
void search_stu_byname(pUSR_INFOR phead, char* name);
void print_stu(pUSR_INFOR phead);

int main()
{
	int is_root = system_init();
	system("cls");
	FILE* stu_file = fopen("usr_infor.txt", "r+");
	FILE* usr_file = fopen("usr_account.txt", "r+");
	pUSR_ACCOUNT usr_head = NULL, usr_tail = NULL;
	pUSR_INFOR stu_head = NULL, stu_tail = NULL;
	char buf[2048];

	while (fgets(buf, sizeof(buf), usr_file) != NULL)
	{
		char name[30];
		char passwd[30];
		memset(name, '\0', sizeof(name));
		memset(passwd, '\0', sizeof(passwd));
		int role;
		int i = 0, index;
		for (; i < strlen(buf) && !isspace(buf[i]); i++)
		{
			name[i] = buf[i];
		}
		i++;
		index = i;
		for (; i < strlen(buf) && !isspace(buf[i]); i++)
		{
			passwd[i - index] = buf[i];
		}
		role = buf[i + 1] - 48;

		account_tail_insert(&usr_head, &usr_tail, name, passwd, role);
	}

	while (fgets(buf, sizeof(buf), stu_file) != NULL)
	{
		int id, course, score;
		char name[30];
		char sid[8];
		char scourse[8];
		char sscore[8];
		memset(name, '\0', sizeof(name));
		int i = 0, index;
		for (; !isspace(buf[i]); i++)
			sid[i] = buf[i];
		i++;
		index = i;

		for (; !isspace(buf[i]); i++)
			name[i - index] = buf[i];
		i++;
		index = i;
		id = atoi(sid);
		for (; !isspace(buf[i]); i++)
			scourse[i - index] = buf[i];
		i++;
		index = i;
		course = atoi(scourse);
		for (; i < strlen(buf); i++)
			sscore[i - index] = buf[i];
		score = atoi(sscore);
		stu_tail_insert(&stu_head, &stu_tail, id, name, course, score);
	}

	fclose(usr_file);
	fclose(stu_file);

	if (is_root == 0)
	{
		while (1)
		{
			system("cls");
			printf("*************************************************\n");
			printf("******Student Information Management System******\n");
			printf("*************************************************\n");
			printf("1.search	student inforamtion\n");
			printf("2.add	student information\n");
			printf("3.update	student information\n");
			printf("4.delete	student information\n");
			printf("5.add	user account\n");
			printf("6.update	user account\n");
			printf("7.delete	user account\n");
			printf("8.search	user account\n");
			printf("9.exit");
			printf("\n");

			int choice;
			printf("select a number:");
			scanf("%d", &choice);
			int id, course, score;
			char name[30];
			char passwd[30];
			switch (choice)
			{
			default:
				printf("Sorry,wrong input\n");
				break;
			case 1:
				system("cls");
				printf("0.search	student all\n");
				printf("1.search	student by id\n");
				printf("2.search	student by name\n");
				int choice_n;
				printf("select a number:");
				scanf("%d", &choice_n);
				switch (choice_n)
				{
				default:
					printf("Sorry,wrong input\n");
					break;
				case 0:
					printf("\n");
					print_stu(stu_head);
					Sleep(1000);
					break;
				case 1:
					printf("enter student's id:");
					scanf("%d", &id);
					search_stu_byid(stu_head, id);
					Sleep(1000);
					break;
				case 2:
					printf("enter students' name:");
					memset(name, '\0', sizeof(name));
					search_stu_byname(stu_head, name);
					Sleep(1000);
					break;
				}
				break;
			case 2:
				system("cls");
				memset(name, '\0', sizeof(name));
				printf("enter student id:");
				scanf("%d", &id);
				printf("\n");
				printf("enter student name:");
				scanf("%s", name);
				printf("\n");
				printf("enter student course:");
				scanf("%d", &course);
				printf("\n");
				printf("enter student score:");
				scanf("%d", &score);
				stu_tail_insert(&stu_head, &stu_tail, id, name, course, score);
				break;
			case 3:
				system("cls");
				printf("enter student id:");
				scanf("%d", &id);
				printf("\n");
				printf("enter student course:");
				scanf("%d", &course);
				printf("\n");
				printf("enter student score:");
				scanf("%d", &score);
				modify_stu(stu_head,id, course,score);
				break;
			case 4:
				system("cls");
				printf("enter student id:");
				scanf("%d", &id);
				delete_stu(&stu_head, &stu_tail, id);
				break;
			case 5:
				system("cls");
				memset(name, '\0', sizeof(name));
				memset(passwd, '\0', sizeof(passwd));
				printf("enter usr name:");
				scanf("%s", name);
				printf("\n");
				printf("enter usr passwd:");
				scanf("%s", passwd);
				printf("\n");
				account_tail_insert(&usr_head, &usr_tail, name, passwd, 1);
				break;
			case 6:
				system("cls");
				memset(name, '\0', sizeof(name));
				memset(passwd, '\0', sizeof(passwd));
				printf("enter usr name:");
				scanf("%s", name);
				printf("\n");
				printf("enter usr passwd:");
				scanf("%s", passwd);
				printf("\n");
				modify_usr(usr_head,name,  passwd);
				break;
			case 7:
				system("cls");
				memset(name, '\0', sizeof(name));
				printf("enter user name:");
				scanf("%s", name);
				delete_usr(&usr_head, &usr_tail, name);
				break;
			case 8:
				system("cls");
				memset(name, '\0', sizeof(name));
				printf("enter user name:");
				scanf("%s", name);
				search_usr(usr_head, name);
				Sleep(1000);
				break;
			case 9:
				system("cls");
				FILE* stu_file = fopen("usr_infor.txt", "w");
				FILE* usr_file = fopen("usr_account.txt", "w");
				while (stu_head != NULL)
				{
					fprintf(stu_file, "%d %s %d %d\n", stu_head->usr_course_id, stu_head->usr_name, stu_head->usr_course_id, stu_head->usr_course_score);
					stu_head = stu_head->pNext_Usr_Infor;
				}

				while (usr_head != NULL)
				{
					fprintf(usr_file, "%s %s %d\n", usr_head->usr_name, usr_head->usr_pwd, usr_head->usr_role);
					usr_head = usr_head->pNext_Usr_Account;
				}
				fclose(usr_file);
				fclose(stu_file);
				printf("exiting...\n");
				Sleep(1000);
				goto ending;
				break;
			}
		}
	}
	if (is_root == 1)
	{
		while (1)
		{
			system("cls");
			printf("*************************************************\n");
			printf("******Student Information Management System******\n");
			printf("*************************************************\n");
			printf("1.search	student inforamtion\n");
			printf("9.exit");
			printf("\n");

			int choice;
			printf("select a number:");
			scanf("%d", &choice);
			int id, course, score;
			char name[30];
			char passwd[30];
			switch (choice)
			{
			default:
				printf("Sorry,wrong input\n");
				break;
			case 1:
				system("cls");
				printf("1.search	student by id\n");
				printf("2.search	student by name\n");
				int choice_n;
				printf("select a number:");
				scanf("%d", &choice_n);
				switch (choice_n)
				{
				default:
					printf("Sorry,wrong input\n");
					Sleep(1000);
					break;
				case 1:
					printf("enter student's id:");
					scanf("%d", &id);
					search_stu_byid(stu_head, id);
					Sleep(1000);
					break;
				case 2:
					printf("enter students' name:");
					memset(name, '\0', sizeof(name));
					search_stu_byname(stu_head, name);
					Sleep(1000);
					break;
				}
				break;
			case 9:
				system("cls");
				printf("exiting...\n");
				Sleep(1000);
				goto ending;
				break;
			}
		}
	}


ending:
	
	return 0;
}

void account_tail_insert(pUSR_ACCOUNT* phead, pUSR_ACCOUNT* ptail, char* name,char* passwd,int role)
{
	pUSR_ACCOUNT pnew;
	pnew = (pUSR_ACCOUNT)malloc(sizeof(USR_ACCOUNT)); 
	memset(pnew, '\0', sizeof(USR_ACCOUNT));
	strcpy(pnew->usr_name, name);
	strcpy(pnew->usr_pwd, passwd);
	pnew->usr_role = role;
	if (*phead == NULL)
	{
		*phead = pnew;
		*ptail = pnew;
	}
	else
	{
		(*ptail)->pNext_Usr_Account = pnew;
		*ptail = pnew;
	}
}

void stu_tail_insert(pUSR_INFOR* phead, pUSR_INFOR* ptail, int id ,char* name, int course, int score)
{
	pUSR_INFOR pnew;
	pnew = (pUSR_INFOR)malloc(sizeof(USR_INFOR));
	memset(pnew, '\0', sizeof(USR_INFOR));
	strcpy(pnew->usr_name, name);
	pnew->usr_id = id;
	pnew->usr_course_id = course;
	pnew->usr_course_score = score;
	if (*phead == NULL)
	{
		*phead = pnew;
		*ptail = pnew;
	}
	else
	{
		(*ptail)->pNext_Usr_Infor = pnew;
		*ptail = pnew;
	}
}

void modify_stu(pUSR_INFOR phead, int id, int course, int score)
{
	while (phead!=NULL)
	{
		if (phead->usr_id == id)
		{
			phead->usr_course_id = course;
			phead->usr_course_score = score;
			break;
		}
		phead = phead->pNext_Usr_Infor;
	}
	if (phead == NULL)
		printf("No this student\n");
}

void modify_usr(pUSR_ACCOUNT phead, char* name,char* passwd)
{
	while (phead != NULL)
	{
		if (strcmp(phead->usr_name,name)==0)
		{
			strcpy(phead->usr_pwd, passwd);
			break;
		}
		phead = phead->pNext_Usr_Account;
	}
	if (phead == NULL)
		printf("No this student\n");
}

void delete_stu(pUSR_INFOR* phead, pUSR_INFOR* ptail, int i)
{
	pUSR_INFOR pcur, ppre;
	pcur = *phead;
	ppre = pcur;
	if (pcur != NULL)
	{
		if (pcur->usr_id == i)
		{
			*phead = pcur->pNext_Usr_Infor;
			if (*phead == NULL)
				*ptail = NULL;
			free(pcur);
		}
		else
		{
			while (pcur != NULL)
			{
				if (pcur->usr_id == i)
				{
					ppre->pNext_Usr_Infor = pcur->pNext_Usr_Infor;
					free(pcur);
					break;
				}
				ppre = pcur;
				pcur = pcur->pNext_Usr_Infor;
			}
			if (ppre->pNext_Usr_Infor == NULL)
				*ptail = ppre;
			if (pcur == NULL)
				printf("no this node\n");
		}
	}
	else
		printf("list is null\n");
}

void delete_usr(pUSR_ACCOUNT* phead, pUSR_ACCOUNT* ptail, char* name)
{
	pUSR_ACCOUNT pcur, ppre;
	pcur = *phead;
	ppre = pcur;
	if (pcur != NULL)
	{
		if (strcmp(pcur->usr_name,name)==0)
		{
			*phead = pcur->pNext_Usr_Account;
			if (*phead == NULL)
				*ptail = NULL;
			free(pcur);
		}
		else
		{
			while (pcur != NULL)
			{
				if (strcmp(pcur->usr_name,name)==0)
				{
					ppre->pNext_Usr_Account = pcur->pNext_Usr_Account;
					free(pcur);
					break;
				}
				ppre = pcur;
				pcur = pcur->pNext_Usr_Account;
			}
			if (ppre->pNext_Usr_Account == NULL)
				*ptail = ppre;
			if (pcur == NULL)
				printf("no this node\n");
		}
	}
	else
		printf("list is null\n");
}

void search_usr(pUSR_ACCOUNT phead,char* name)
{
	while (phead != NULL)
	{
		if (strcmp(phead->usr_name, name) == 0)
		{
			printf("user_name: %s user_passwd:%s %s\n", phead->usr_name, phead->usr_pwd, (phead->usr_role) ? "common" : "root");
			break;
		}
		else
		{
			phead = phead->pNext_Usr_Account;
		}
		
	}
	if (phead == NULL)
		printf("No this user\n");
}

void search_stu_byid(pUSR_INFOR phead, int id)
{
	while (phead != NULL)
	{
		if (phead->usr_id=id)
		{
			printf("ID:%d Name:%s Course:%d Score:%d\n", phead->usr_id, phead->usr_name, phead->usr_course_id, phead->usr_course_score);
			break;
		}
		else
		{
			phead = phead->pNext_Usr_Infor;
		}

	}
	if (phead == NULL)
		printf("No this user\n");
}

void search_stu_byname(pUSR_INFOR phead, char* name)
{
	while (phead != NULL)
	{
		if (strcmp(phead->usr_name,name)==0)
		{
			printf("ID:%d Name:%s Course:%d Score:%d\n", phead->usr_id, phead->usr_name, phead->usr_course_id, phead->usr_course_score);
			break;
		}
		else
		{
			phead = phead->pNext_Usr_Infor;
		}

	}
	if (phead == NULL)
		printf("No this user\n");
}

void print_stu(pUSR_INFOR phead)
{
	while (phead!=NULL)
	{
		printf("ID:%d Name:%s Course:%d Score:%d\n", phead->usr_id, phead->usr_name, phead->usr_course_id, phead->usr_course_score);
		phead = phead->pNext_Usr_Infor;
	}
}

int system_init()
{
	char usr_name[USR_NAME_LEN];
	char usr_passwd[USR_PWD_LEN];
	memset(usr_name, '\0', sizeof(usr_name));
	memset(usr_passwd, '\0', sizeof(usr_passwd));
	FILE* acc_file = fopen("usr_account.txt", "r+");
	pUSR_ACCOUNT usr_head = NULL, usr_tail = NULL;
	char buf[2048];
	while (fgets(buf, sizeof(buf), acc_file) != NULL)
	{
		char name[30];
		char passwd[30];
		memset(name, '\0', sizeof(name));
		memset(passwd, '\0', sizeof(passwd));
		int role;
		int i = 0,index;
		for (; i < strlen(buf) && !isspace(buf[i]); i++)
		{
			name[i] = buf[i];
		}
		i++;
		index = i;
		for (; i < strlen(buf) && !isspace(buf[i]); i++)
		{
			passwd[i - index] = buf[i];
		}
		role = buf[i+1]-48;

		account_tail_insert(&usr_head, &usr_tail, name, passwd, role);
	}
	fclose(acc_file);
	int role;
	goto login;
	return role;
login:
	system("cls");
	printf("enter user name:");
	gets(usr_name);
	system("cls");
	printf("enter password:");
	char c;
	int i = 0;
	while ((c = getch()) != EOF)
	{
		if (c == '\b')
		{
			i--;
			printf("\b \b");
		}
		else if(c==13)
		{
			break;
		}
		else
		{
			usr_passwd[i++] = c;
			putchar('*');
		}
	}
	printf("\n");
	int is_exit = 0;
	int is_right = 0;
	
	while (usr_head!=NULL)
	{
		if (strcmp(usr_head->usr_name,usr_name)==0)
		{
			is_exit = 1;
			if (strcmp(usr_head->usr_pwd,usr_passwd)==0)
			{
				is_right = 1;
				if (usr_head->usr_role == 0)
				{
					printf("login in...\n");
					Sleep(1500);
					return 0;
				}
				else
				{
					printf("login in...\n");
					Sleep(1500);
					return 1;
				}
			}
			else
			{
				break;
			}
		}
		usr_head = usr_head->pNext_Usr_Account;
	}
	if (is_exit == 0)
	{
		printf("No this user\n");
		Sleep(1500);
		goto login;
	}
	else if(is_right==0)
	{
		printf("Wrong passwd\n");
		Sleep(1500);
		goto login;
	}
}
