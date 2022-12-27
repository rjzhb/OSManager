#include<iostream>
#include<string.h>
#include<iomanip>
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<cstdlib>
#include<Windows.h>
using namespace std;
#define  _WINSOCK_DEPRECATED_NO_WARNINGS 1
#define _CRT_SECURE_NO_WARNINGS 1

typedef struct node
{
	char name[50];
	int type;
	struct tm t;
	struct node* next;
	struct node* sub;
	struct node* father;
	int size;
	char* str;
	int addr;
	WCHAR PCName[255];//ֱ��ʹ��wchar���Ͷ���
	WCHAR UserName[255];
}dirNode;
dirNode* workDir;
dirNode root;
char path[100];
bool IsInMaster(dirNode* p)
{
	return false;
}
void Write_File(dirNode* p);
void Read_File(dirNode* p);
void Transfer_In_File(dirNode* p);
void Transfer_Out_File(dirNode* p);
void Create_File(dirNode* p);
void Delete_File(dirNode* p);

void initial()
{
	strcpy_s(root.name, "root");
	root.type = 0;
	root.next = NULL;
	root.sub = NULL;
	root.father = NULL;
	root.size = 0;
	root.str = NULL;
	workDir = &root;
	strcpy_s(path, "root");
}

dirNode* init()
{
	dirNode* p;
	p = new dirNode;
	strcpy_s(root.name, "");
	root.type = 0;
	root.next = NULL;
	root.sub = NULL;
	root.father = NULL;
	root.size = 0;
	root.str = NULL;
	return p;
}

void CD(char dirName[])
{
	dirNode* p;
	int flag = 0;
	p = workDir->sub;
	if (p == NULL)
		cout << "����\"" << dirName << "\"��Ŀ¼������" << endl;
	else
	{
		while (p)
		{
			if (p->type == 0)
			{
				if (!strcmp(p->name, dirName))
				{
					flag = 1;
					break;
				}
			}
			p = p->next;
		}
		if (flag == 1)
		{
			workDir = p;
			strcat_s(path, "\\");
			strcat_s(path, p->name);
			cout << "����Ŀ¼�ѽ���\"" << dirName << "\"" << endl;
		}
		else
		{
			cout << "����\"" << dirName << "\"��Ŀ¼������" << endl;
		}
	}
}

void CREATE(char fileName[])
{
	int flag;
	dirNode* p, * q;
	q = new dirNode;
	strcpy_s(q->name, fileName);
	time_t now;  //����time_t���ͱ���
	time(&now);      //��ȡϵͳ���ں�ʱ��
	localtime_s(&q->t, &now);  //��ȡ�������ں�ʱ��
	unsigned long size = 255;
	GetComputerName(q->PCName, &size);//GetComputerName()�����ĵ�һ��������������LPWSTR������ֱ��ʹ��wchar����ǰ�������
	GetUserName(q->UserName, &size);//GetUserName()����ͬ��
	//printf("The computer's name is :%S\n", PCName);//��ӡҪ��%S����Ӧwchar		
	//printf("The computer's user name is %S\n", UserName);
	//system("pause");
	q->sub = NULL;
	q->type = 1;
	q->next = NULL;
	q->father = workDir;
	q->str = (char*)malloc(50 * sizeof(char));
	q->size = 0;
	p = workDir->sub;
	if (p == NULL)
	{
		workDir->sub = q;
		cout << "\"" << fileName << "�ļ������ɹ�" << endl;
		Create_File(p);
	}
	else
	{
		flag = 0;
		while (p)
		{
			if (p->type == 1)
			{
				if (!strcmp(p->name, fileName))
				{
					flag = 1;
					break;
					cout << "����\"" << fileName << "\"�ļ��Ѵ���" << endl;
				}
			}
			p = p->next;
		}
		if (flag == 0)
		{
			p = workDir->sub;
			while (p->next)
			{
				p = p->next;
			}
			p->next = q;
			cout << "\"" << fileName << "�ļ������ɹ�" << endl;
			Create_File(p);
		}
	}
}

void DEL(char fileName[])
{
	dirNode* p, * q;
	int flag = 0;
	p = workDir->sub;
	if (p == NULL)
		cout << "����\"" << fileName << "\"�ļ�������" << endl;
	else
	{
		while (p)
		{
			if (p->type == 1)
			{
				if (!strcmp(p->name, fileName))
				{
					flag = 1;
					break;
				}
			}
			p = p->next;
		}
		if (flag == 1)
		{
			if (IsInMaster(p))
				cout << "����\"" << fileName << "\"��װ���ڴ�" << endl;
			else
			{
				if (p == workDir->sub)
					workDir->sub = p->next;
				else
				{
					q = workDir->sub;
					while (q->next != p)
						q = q->next;
					q->next = p->next;
					Delete_File(p);
					delete p;
				}
				cout << "\"" << fileName << "�ļ���ɾ��" << endl;
			}
		}
		else
			cout << "����\"" << fileName << "\"�ļ�������" << endl;

	}
}

void dir(dirNode *p)
{
	while (p)
	{
		if (p->type == 0)
		{
			cout << setw(14) << p->name << setw(12) << "<DIR>" << endl;
		}
		else
		{
			cout << setw(14) << p->name << setw(12) << "<FILE>" << setw(10) << p->size << endl;
		}
		p = p->next;
	}
}

void dirs(dirNode* p, char str[])
{
	char newstr[100];
	dirNode* q;
	cout << str << "����Ŀ¼���ļ���" << endl;
	dir(p);
	q = p;
	if (q->sub)
	{
		strcpy_s(newstr, "");
		strcat_s(newstr, str);
		strcat_s(newstr, "\\");
		strcat_s(newstr, q->name);
		dirs(q->sub, newstr);
	}
	q = p;
	while (q->next)
	{
		if (q->next->sub)
		{
			strcpy_s(newstr, "");
			strcat_s(newstr, str);
			strcat_s(newstr, "\\");
			strcat_s(newstr, q->next->name);
			dirs(q->next->sub, newstr);
		}
		q = q->next;
	}
}

void LSALL()
{
	dirNode* p;
	cout << "��ʾ����Ŀ¼�ṹ" << endl << "---------------------------------------------------------------------" << endl;
	p = root.sub;
	char C[5] = "root";
	dirs(p,C);
}

void MD(char dirName[])
{
	int flag;
	dirNode* p, * q;
	q = new dirNode;
	strcpy_s(q->name, dirName);
	q->sub = NULL;
	q->type = 0;
	q->next = NULL;
	q->father = workDir;
	q->size = 0;
	q->str = NULL;
	p = workDir->sub;
	if (p == NULL)
	{
		workDir->sub = q;
		cout << "\"" << dirName << "��Ŀ¼�����ɹ�" << endl;
	}
	else
	{
		flag = 0;
		while (p)
		{
			if (p->type == 0)
			{
				if (!strcmp(p->name, dirName))
				{
					flag = 1;
					break;
					cout << "����\"" << dirName << "\"��Ŀ¼�Ѵ���" << endl;
				}
			}
			p = p->next;
		}
		if (flag == 0)
		{
			p = workDir->sub;
			while (p->next)
			{
				p = p->next;
			}
			p->next = q;
			cout << "\"" << dirName << "��Ŀ¼�����ɹ�" << endl;
		}
	}
}

void RD(char dirName[])
{
	dirNode* p, * q;
	int flag = 0;
	p = workDir->sub;
	if (p == NULL)
	{
		cout << "����\"" << dirName << "\"��Ŀ¼�Ѵ���" << endl;
	}
	else
	{
		while (p)
		{
			if (p->type == 0)
			{
				if (!strcmp(p->name, dirName))
				{
					flag = 1;
					break;
				}
			}
			p = p->next;
		}
		if (flag == 1)
		{
			if(p->sub)
				cout << "����\"" << dirName << "\"��Ŀ¼�´�����Ŀ¼���ļ�" << endl;
			else
			{
				if (p == workDir->sub)
					workDir->sub = p->next;
				else
				{
					q = workDir->sub;
					while (q->next != p)
						q = q->next;
					q->next = p->next;
					delete p;
				}
				cout << "\"" << dirName << "��Ŀ¼��ɾ��" << endl;
			}
		}
		else
			cout << "����\"" << dirName << "\"��Ŀ¼������" << endl;
	}
}

void BACK()
{
	if (workDir->father)
	{
		int len = strlen(path), Len = strlen(workDir->name);
		path[len - Len - 1] = '\0';
		workDir = workDir->father;
		cout << "�ѷ���" << workDir->name << "Ŀ¼" << endl;
	}
	else
	{
		cout << "������һ��Ŀ¼������" << endl;
	}
}

void version()
{
	cout << endl << endl;
	cout << "---------------------------------------------------------" << endl;
	cout << "|                  ģ���ļ�ģ�����ϵͳ                 |" << endl;
	cout << "|-------------------------------------------------------|" << endl;
	cout << "|                (c)All Right Reserved Neo              |" << endl;
	cout << "---------------------------------------------------------" << endl;
	cout << endl << endl;
}

void OPEN(char fileName[])
{
	dirNode* p, * q;
	int flag = 0;
	p = workDir->sub;
	if (p == NULL)
		cout << "����\"" << fileName << "\"�ļ�������" << endl;
	else
	{
		while (p)
		{
			if (p->type == 1)
			{
				if (!strcmp(p->name, fileName))
				{
					flag = 1;
					break;
				}
			}
			p = p->next;
		}
		if (flag == 1)
		{
			if (IsInMaster(p))
				cout << "����\"" << fileName << "\"��װ���ڴ�" << endl;
			else
			{
				Read_File(p);
				Transfer_In_File(p);
			}
		}
		else
			cout << "����\"" << fileName << "\"�ļ�������" << endl;
	}
}

void CLOSE(char fileName[])
{
	dirNode* p, * q;
	int flag = 0;
	p = workDir->sub;
	if (p == NULL)
		cout << "����\"" << fileName << "\"�ļ�������" << endl;
	else
	{
		while (p)
		{
			if (p->type == 1)
			{
				if (!strcmp(p->name, fileName))
				{
					flag = 1;
					break;
				}
			}
			p = p->next;
		}
		if (flag == 1)
		{
			if (!IsInMaster(p))
				cout << "����\"" << fileName << "\"���Ƴ��ڴ�" << endl;
			else
			{
				Transfer_Out_File(p);
				Write_File(p);
			}
		}
		else
			cout << "����\"" << fileName << "\"�ļ�������" << endl;
	}
}

int main()
{
	int len, fileSize, flag, comm;
	char String[50];
	char command[10];
	char name[10];
	char* s, * s1;
	version();
	initial();
	dir(workDir->sub);
	flag = 1;
	while (flag)
	{
		cout << endl << "ģ���ļ�����ģ��ϵͳ" << endl;
		cout << endl << "CD �ı�Ŀ¼      CREATE �����ļ�   DEL ɾ���ļ�   OPEN ���ļ�   CLOSE �ر��ļ�" << endl;
		cout << endl << "LSALL ��ʾĿ¼   MD ����Ŀ¼       RD ɾ��Ŀ¼    BACK ������һ��Ŀ¼" << endl;
		cout << endl << "------------------------------------------------------------" << endl;
		printf("%s:>#", path);
		int i = 0;
		for (; (String[i] = getchar()) != '\n'; i++);
		String[i] = '\0';
		len = strlen(String);
		if (len == 0)
		{
			strcpy_s(command, "error");
		}
		else
		{
			s = NULL;
			s = strchr(String, ' ');
			if (s != NULL)
				*s = '\0';
			strcpy_s(command, String);
			if ((!strcmp(command, "CD")) || !strcmp(command, "cd"))
				comm = 1;
			else if ((!strcmp(command, "CREATE")) || !strcmp(command, "create"))
				comm = 2;
			else if ((!strcmp(command, "DEL")) || !strcmp(command, "del"))
				comm = 3;
			else if ((!strcmp(command, "LSALL")) || !strcmp(command, "lsall"))
				comm = 4;
			else if ((!strcmp(command, "MD")) || !strcmp(command, "md"))
				comm = 5;
			else if ((!strcmp(command, "RD")) || !strcmp(command, "rd"))
				comm = 6;
			else if ((!strcmp(command, "BACK")) || !strcmp(command, "back"))
				comm = 7;
			else if ((!strcmp(command, "OPEN")) || !strcmp(command, "open"))
				comm = 8;
			else if ((!strcmp(command, "CLOSE")) || !strcmp(command, "close"))
				comm = 9;
			else if ((!strcmp(command, "EXIT")) || !strcmp(command, "exit"))
				comm = 0;
			else comm = 100;
			switch (comm)
			{
			case 1:
				strcpy_s(name, s + 1);
				CD(name);
				break;
			case 2:
				strcpy_s(name, s + 1);
				CREATE(name);
				break;
			case 3:
				strcpy_s(name, s + 1);
				DEL(name);
				break;
			case 4:
				LSALL();
				break;
			case 5:
				strcpy_s(name, s + 1);
				MD(name);
				break;
			case 6:
				strcpy_s(name, s + 1);
				RD(name);
				break;
			case 7:
				BACK();
				break;
			case 8:
				strcpy_s(name, s + 1);
				OPEN(name);
				break;
			case 9:
				strcpy_s(name, s + 1);
				CLOSE(name);
				break;
			case 0:
				flag = 0;
				break;
			default:
				cout << "�������" << endl;
				break;
			}
		}
		dir(workDir->sub);
	}
	return 0;
}