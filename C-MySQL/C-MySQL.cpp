#include <iostream>
#include <stdio.h>
#include <mysql.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable:4996)
#include <WinSock.h>
#pragma comment(lib,"libmysql.lib")
#define bzero(a,b) memset(a,0,b)
MYSQL* conn_prt;
MYSQL_RES* res;
MYSQL_ROW row;
char v;
void self_init()
{
	conn_prt = mysql_init(NULL);
}


char select_head[100] = "select Snum,Sname from ";
char select_head_book[200] = "select Bname from student, SToB, book where SToB.Snum = student.Snum and SToB.Bnum = book.Bnum and ";
char desc_head[50] = "desc ";
char insert_head[200] = "insert into ";
char drop_msg_head[50] = "delete from ";
char change_base_head[50] = "use ";
char update_head[50] = "update ";
char count_head[200] = "select COUNT(student.Snum) from student, SToB, book where SToB.Snum = student.Snum and SToB.Bnum = book.Bnum and ";



MYSQL* mysql_connect()
{
	MYSQL * conn_prt = mysql_init(0);
	if (!mysql_real_connect(conn_prt, "localhost", "root", "zc000910", "book", 0, 0, 0))
	{
		printf("无法连接到数据库！");
		return NULL;
	}
	else
	{
		printf("连接成功！");
		return conn_prt;
	}

}

int count_book(char Snum[10])
{
	int count;
	int t = 0;
	char temp;
	char query[200];
	bzero(query, 50);
	strcpy(query, count_head);
	strcat(query, " student.Snum =\"");
	strcat(query, Snum);
	strcat(query, "\"");
	t = mysql_query(conn_prt, query);
	if (t)
	{
		printf("失败:%s\n", mysql_error(conn_prt));
	}
	res = mysql_store_result(conn_prt);
	row = mysql_fetch_row(res);
	count = *row[0] - '0';
	return count;
}
int menu()
{
	int n = 10;
	system("cls");
	printf("========================================================================\n");
	printf("=                      students managing system                        =\n");
	printf("========================================================================\n");
	printf("=          1:添加学生                      2:删除学生                  =\n");
	printf("=                                                                      =\n");
	printf("=          3:图书出借                      4:图书归还                  =\n");
	printf("=                                                                      =\n");
	printf("=          5:查询信息                      0:退出系统                  =\n");
	printf("========================================================================\n");
	while (n < 0 || n>5)
	{
		scanf("%d", &n);
	}
	return n;
}
void select_by_name()
{
	int t = 0;
	char sele_name[20];
	char query[200];
	bzero(query, 50);
	strcpy(query, select_head);
	strcat(query, "student where Sname like ");
	printf("请输入需查询的学生的姓名（支持模糊）\n");
	strcat(query, "'%");
	scanf("%s", sele_name);
	strcat(query,sele_name);
	strcat(query, "%'");
	t = mysql_query(conn_prt, query);
	if (t)
	{
		printf("失败:%s\n", mysql_error(conn_prt));
	}
	printf("成功!\n");
	printf("学号\t姓名\n");
	res = mysql_store_result(conn_prt);
	while (row = mysql_fetch_row(res))
	{
		for (t = 0; t < (int)mysql_num_fields(res); t++)
		{
			printf("%s\t", row[t]);
		}
		printf("\n");
	}

	bzero(query, 50);
	strcpy(query, select_head_book);
	strcat(query, "student.Sname like ");
	strcat(query, "'%");
	strcat(query,sele_name);
	strcat(query, "%'");
	t = mysql_query(conn_prt, query);
	if (t)
	{
		printf("失败:%s\n", mysql_error(conn_prt));
	}
	printf("已借书目:\n");
	res = mysql_store_result(conn_prt);
	while (row = mysql_fetch_row(res))
	{
		for (t = 0; t < (int)mysql_num_fields(res); t++)
		{
			printf("%s\t", row[t]);
		}
		printf("\n");
	}


}

void select_by_num()
{
	int t = 0;
	char sele_num[20];
	char query[200];
	bzero(query, 50);
	strcpy(query, select_head);
	strcat(query, "student where Snum like ");
	printf("请输入需查询的学生的学号（支持模糊）\n");
	strcat(query, "'%");
	scanf("%s", sele_num);
	strcat(query, sele_num);
	strcat(query, "%'");
	t = mysql_query(conn_prt, query);
	if (t)
	{
		printf("失败:%s\n", mysql_error(conn_prt));
	}
	printf("成功!\n");
	printf("学号\t姓名\n");
	res = mysql_store_result(conn_prt);
	while (row = mysql_fetch_row(res))
	{
		for (t = 0; t < (int)mysql_num_fields(res); t++)
		{
			printf("%s\t", row[t]);
		}
		printf("\n");
	}

	bzero(query, 50);
	strcpy(query, select_head_book);
	strcat(query, "student.Snum like ");
	strcat(query, "'%");
	strcat(query, sele_num);
	strcat(query, "%'");
	t = mysql_query(conn_prt, query);
	if (t)
	{
		printf("失败:%s\n", mysql_error(conn_prt));
	}
	printf("已借书目:\n");
	res = mysql_store_result(conn_prt);
	while (row = mysql_fetch_row(res))
	{
		for (t = 0; t < (int)mysql_num_fields(res); t++)
		{
			printf("%s\t", row[t]);
		}
		printf("\n");
	}

}


void select_stu()
{
	int n=-1;
	system("cls");
	printf("========================================================================\n");
	printf("=                      students managing system                        =\n");
	printf("========================================================================\n");
	printf("=            1:按学号查询                    2：按姓名查询             =\n");
	printf("========================================================================\n");
	while (n < 0 || n>2)
	{
		scanf("%d", &n);
	}
	switch (n)
	{
	case 1:
	{
		select_by_num();
		break;
	}
	case 2:
	{
		select_by_name();
		break;
	}
	{
	default:
		break;
	}
	}
}
void drop_stu()
{
	int t;
	char drop_query[200] = { 0 };
	char table_name[20] = { 0 };
	char del_num[20] = { 0 };

	strcpy(drop_query, drop_msg_head);

	puts("请输入需删除学生的学号:");
	scanf("%s", del_num);

	strcat(drop_query, "student");
	strcat(drop_query, " where Snum =\"");
	strcat(drop_query, del_num);
	strcat(drop_query, "\"");
	printf("%s\n", drop_query);

	t = mysql_real_query(conn_prt, drop_query, strlen(drop_query));
	if (t)
	{
		printf("failed to query:%s\n", mysql_error(conn_prt));
		return;
	}

	drop_query[200] = { 0 };
	strcpy(drop_query, drop_msg_head);
	strcat(drop_query, "SToB");
	strcat(drop_query, " where Snum =\"");
	strcat(drop_query, del_num);
	strcat(drop_query, "\"");
	printf("%s\n", drop_query);

	t = mysql_real_query(conn_prt, drop_query, strlen(drop_query));
	if (t)
	{
		printf("failed to query:%s\n", mysql_error(conn_prt));
		return;
	}

	printf("删除学生成功！\n");
	return;
}

void return_book()
{
	int t;
	char drop_query[200] = { 0 };
	char table_name[20] = { 0 };
	char del_Bnum[20] = { 0 };
	char del_Snum[20] = { 0 };


	strcpy(drop_query, drop_msg_head);

	puts("请输入学生学号:");
	scanf("%s", del_Snum);
	puts("请输入需还书目编号:");
	scanf("%s", del_Bnum);

	strcat(drop_query, "SToB");
	strcat(drop_query, " where Snum =\"");
	strcat(drop_query, del_Snum);
	strcat(drop_query, "\" and");
	strcat(drop_query, " Bnum =\"");
	strcat(drop_query, del_Bnum);
	strcat(drop_query, "\"");
	printf("%s\n", drop_query);

	t = mysql_real_query(conn_prt, drop_query, strlen(drop_query));
	if (t)
	{
		printf("failed to query:%s\n", mysql_error(conn_prt));
		return;
	}

	printf("归还成功！\n");
	return;
}

void insert_stu()
{
	int t;
	char insert_query[200];
	char table_name[50];
	char field[100]= "Snum,Sname";
	char left[5] = "(";
	char right[5] = ") ";
	char values[50] = "values";
	char message[200] = { 0 };

	bzero(field, 100);
	bzero(table_name, 50);
	bzero(message, 200);
	strcpy(insert_query, insert_head); 

	puts("请输入学号、姓名(以逗号分隔)");
	scanf("%s", message);


	strcat(insert_query, "student");
	strcat(insert_query, left);
	strcat(insert_query, field);
	strcat(insert_query, right);
	strcat(insert_query, values);
	strcat(insert_query, left);
	strcat(insert_query, message);
	strcat(insert_query, right);
	printf("%s\n", insert_query);

	t = mysql_real_query(conn_prt, insert_query, strlen(insert_query));
	if (t)
	{
		printf("failed to query:%s\n", mysql_error(conn_prt));
		return;
	}

	printf("成功添加学生！\n");
}

void borrow()
{
	int t;
	char insert_query[200];
	char table_name[50];
	char field[100] = "Snum,Bnum";
	char left[5] = "(";
	char right[5] = ") ";
	char values[50] = "values";
	char message[200] = { 0 };
	char Snum[20] = { 0 };
	char Bnum[20] = { 0 };
	bzero(field, 100);
	bzero(table_name, 50);
	bzero(message, 200);
	strcpy(insert_query, insert_head);

	puts("请输入学生学号:\n");
	scanf("%s", Snum);
	if (count_book(Snum) >= 5)
	{
		printf("所借书目已达上限！\n");
		return;
	}
	puts("请输入书本编号:\n");
	scanf("%s", Bnum);
	strcpy(message, Snum);
	strcat(message, ",");
	strcat(message, Bnum);

	strcat(insert_query, "SToB");
	strcat(insert_query, left);
	strcat(insert_query, field);
	strcat(insert_query, right);
	strcat(insert_query, values);
	strcat(insert_query, left);
	strcat(insert_query, message);
	strcat(insert_query, right);
	printf("%s\n", insert_query);

	t = mysql_real_query(conn_prt, insert_query, strlen(insert_query));
	if (t)
	{
		printf("failed to query:%s\n", mysql_error(conn_prt));
		return;
	}

	printf("书本出借成功！\n");
}


int main()
{
	int sele=-1;
	conn_prt = mysql_connect();
	while (1)
	{
		sele = menu();
		switch (sele)
		{
		case 1:
		{
			insert_stu();
			printf("按任意键回到主菜单\n");
			v = getch();
			break;
		}
		case 2:
		{
			drop_stu();
			printf("按任意键回到主菜单\n");
			v = getch();
			break;
		}
		case 3:
		{
			borrow();
			printf("按任意键回到主菜单\n");
			v = getch();
			break;
		}
		case 4:
		{
			return_book();
			printf("按任意键回到主菜单\n");
			v = getch();
			break;
		}
		case 5:
		{
			select_stu();
			printf("按任意键回到主菜单\n");
			v = getch();
			break;
		}
		case 0:
		{
			return 0;
			printf("按任意键回到主菜单\n");
			v = getch();
			break;
		}

		}
	}
	
	

	return 0;
}