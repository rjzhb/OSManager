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
	WCHAR PCName[255];//直接使用wchar类型定义
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
		cout << "错误，\"" << dirName << "\"子目录不存在" << endl;
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
			cout << "工作目录已进入\"" << dirName << "\"" << endl;
		}
		else
		{
			cout << "错误，\"" << dirName << "\"子目录不存在" << endl;
		}
	}
}

void CREATE(char fileName[])
{
	int flag;
	dirNode* p, * q;
	q = new dirNode;
	strcpy_s(q->name, fileName);
	time_t now;  //声明time_t类型变量
	time(&now);      //获取系统日期和时间
	localtime_s(&q->t, &now);  //获取当地日期和时间
	unsigned long size = 255;
	GetComputerName(q->PCName, &size);//GetComputerName()函数的第一个参数的类型是LPWSTR，所以直接使用wchar定义前面的数组
	GetUserName(q->UserName, &size);//GetUserName()函数同上
	//printf("The computer's name is :%S\n", PCName);//打印要用%S，对应wchar		
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
		cout << "\"" << fileName << "文件创建成功" << endl;
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
					cout << "错误，\"" << fileName << "\"文件已存在" << endl;
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
			cout << "\"" << fileName << "文件创建成功" << endl;
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
		cout << "错误，\"" << fileName << "\"文件不存在" << endl;
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
				cout << "错误\"" << fileName << "\"已装入内存" << endl;
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
				cout << "\"" << fileName << "文件已删除" << endl;
			}
		}
		else
			cout << "错误，\"" << fileName << "\"文件不存在" << endl;

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
	cout << str << "下子目录及文件：" << endl;
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
	cout << "显示所有目录结构" << endl << "---------------------------------------------------------------------" << endl;
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
		cout << "\"" << dirName << "子目录创建成功" << endl;
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
					cout << "错误，\"" << dirName << "\"子目录已存在" << endl;
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
			cout << "\"" << dirName << "子目录创建成功" << endl;
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
		cout << "错误，\"" << dirName << "\"子目录已存在" << endl;
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
				cout << "错误，\"" << dirName << "\"子目录下存在子目录或文件" << endl;
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
				cout << "\"" << dirName << "子目录已删除" << endl;
			}
		}
		else
			cout << "错误，\"" << dirName << "\"子目录不存在" << endl;
	}
}

void BACK()
{
	if (workDir->father)
	{
		int len = strlen(path), Len = strlen(workDir->name);
		path[len - Len - 1] = '\0';
		workDir = workDir->father;
		cout << "已返回" << workDir->name << "目录" << endl;
	}
	else
	{
		cout << "错误，上一级目录不存在" << endl;
	}
}

void version()
{
	cout << endl << endl;
	cout << "---------------------------------------------------------" << endl;
	cout << "|                  模拟文件模拟管理系统                 |" << endl;
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
		cout << "错误，\"" << fileName << "\"文件不存在" << endl;
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
				cout << "错误\"" << fileName << "\"已装入内存" << endl;
			else
			{
				Read_File(p);
				Transfer_In_File(p);
			}
		}
		else
			cout << "错误，\"" << fileName << "\"文件不存在" << endl;
	}
}

void CLOSE(char fileName[])
{
	dirNode* p, * q;
	int flag = 0;
	p = workDir->sub;
	if (p == NULL)
		cout << "错误，\"" << fileName << "\"文件不存在" << endl;
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
				cout << "错误\"" << fileName << "\"已移除内存" << endl;
			else
			{
				Transfer_Out_File(p);
				Write_File(p);
			}
		}
		else
			cout << "错误，\"" << fileName << "\"文件不存在" << endl;
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
		cout << endl << "模拟文件管理模拟系统" << endl;
		cout << endl << "CD 改变目录      CREATE 创建文件   DEL 删除文件   OPEN 打开文件   CLOSE 关闭文件" << endl;
		cout << endl << "LSALL 显示目录   MD 创建目录       RD 删除目录    BACK 返回上一级目录" << endl;
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
				cout << "命令错误" << endl;
				break;
			}
		}
		dir(workDir->sub);
	}
	return 0;
}