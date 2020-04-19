//教务管理系统demo
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


//学生信息结构体
typedef struct Student{   
	int no;               //学号
	char name[8];         //姓名
	int cl;               //班级
	int grade1;           
	int grade2;
	int grade3;
	int sum;              //总成绩
	int avg;              //平均成绩
	struct Student *next;
}stu;
int size = sizeof(stu); //结构体空间大小


void Menu();				/*项目菜单*/
stu *load(FILE *fp);        /*读取文件信息*/
void save(stu *p);          /*储存文件信息*/
stu *append(stu* h);        /*追加学生信息*/
void edit();                /*修改学生信息*/
void demand();              /*查询学生信息*/
void del();                 /*删除学生信息*/
void display();             /*显示学生信息*/
stu *sort(stu *p, int);     /*排序*/
int check(int no);          /*判断学生信息是否已经存在*/
stu *create();              /*创建链表*/

//主函数
int main()
{
	Menu();
	return 0;
}

void Menu()
{
	int flag = 0;
	stu *h = NULL;
	FILE *fp;
	do
	{
		int num = 0;
		printf("\n");
		printf("      欢迎来到学生成绩管理系统    \n");
		printf("==================================\n");
		printf("*       1.录入学生信息           *\n");
		printf("*       2.修改学生信息           *\n");
		printf("*       3.查询学生信息           *\n");
		printf("*       4.显示学生信息           *\n");
		printf("*       5.删除学生信息           *\n");
		printf("*       0.退出                   *\n");
		printf("==================================\n");
		printf("\n请输入选择:");
		scanf("%d", &num);
		switch (num)
		{
		case 0:
			flag = -1;
			break;
		case 1:
			//文件存在则打开,不存在则创建
			if ((fp = fopen("stu.list", "rb")) == NULL)
				h = create();
			else
				h = append(load(fp));
			break;
		case 2:
			getchar();
			edit();
			break;	
		case 3:
			demand();
			break;
		case 4:
			display();
			break;
		case 5:
			del();
			break;
		default:
			break;
		}
	} while (flag != -1);
}

int check(int no)
{
	stu *p = NULL;
	FILE *fp;
	//文件打开失败
	if ((fp = fopen("stu.list", "rb")) == NULL)
	{
		return -1;
	}
	//加载文件内容
	rewind(fp);
	p = load(fp);
	
	//比较是否有重复学号
	for (p ; p != NULL; p = p->next)
	{
		if (p->no == no)
			return 1;
	}
	
	return 0;
}


void save(stu *p)
{
	FILE *fp;
	//文件打开,写入头插进来的信息块,关闭
	fp = fopen("stu.list", "wb");
	for (; p != NULL; p = p->next)
		fwrite(p, size, 1, fp);
	
	fclose(fp);
	printf("\n 保存成功!\n");
}

stu* create()
{
	stu *head = NULL, *node = NULL; //head为新头节点,node为tmp
	while (1)
	{
		node = (stu *)malloc(size);
		printf("\n请输入学号： ");
		scanf("%d", &node->no);
		//检测添加的学号是否存在
		while (check(node->no) == 1)
		{
			printf("\n已经存在该学号\n请输入学号： ");
			scanf("%d", &node->no);
		}
		printf("\n请输入班级: ");
		scanf("%d", &node->cl);
		printf("\n请输入名字: ");
		scanf("%s", &node->name);
		printf("\n请输入第一门成绩: ");
		scanf("%d", &node->grade1);
		printf("\n请输入第二门成绩: ");
		scanf("%d", &node->grade2);
		printf("\n请输入第三门成绩: ");
		scanf("%d", &node->grade3);
		node->sum = node->grade1 + node->grade2 + node->grade3;
		node->avg = (node->sum) / 3;
		//node头插,更新头
		node->next = head;
		head = node;
		getchar();

		int temp = 0;
		printf("是否继续录入?1.是 2.否 :");
		scanf("%d", &temp);
		//保存
		if (temp != 1)
		{
			save(head);
			return head;
		}
	}
}

stu *load(FILE *fp)
{
	stu *p, *q, *h = NULL;
	p = (stu *)malloc(size);
	q = (stu *)malloc(size);
	h = p;

	for (; fread(p, size, 1, fp) != NULL; q = p, p = p->next)
		p->next = (stu *)malloc(size);

	q->next = NULL;
	fclose(fp);
	return h;
}

stu *append(stu *q)
{
	stu *node;
	while (1)
	{
		node = (stu *)malloc(size);
		printf("\n请输入学号： ");
		scanf("%d", &node->no);
		while(check(node->no) == 1)
		{
			printf("\n已经存在该学号\n请输入学号： ");
			scanf("%d", &node->no);
		}
		printf("\n请输入班级: ");
		scanf("%d", &node->cl);
		printf("\n请输入名字: ");
		scanf("%s", &node->name);
		printf("\n请输入第一门成绩: ");
		scanf("%d", &node->grade1);
		printf("\n请输入第二门成绩: ");
		scanf("%d", &node->grade2);
		printf("\n请输入第三门成绩: ");
		scanf("%d", &node->grade3);
		node->sum = node->grade1 + node->grade2 + node->grade3;
		node->avg = (node->sum) / 3;

		node->next = q;
		q = node;

		int temp = 0;
		printf("是否继续录入?1.是 2.否 :");
		scanf("%d", &temp);
		//保存
		if (temp != 1)
		{
			save(q);
			return q;
		}
		
	}
}



void edit()
{
	int no=0, flag=0;
	stu *head, *p;
	//没有文件则退出
	FILE *fp;
	if ((fp = fopen("stu.list", "rb")) == NULL)
	{
		printf("没有记录");
		return;
	}
	//head载入链表
	head = load(fp);	
	system("cls");
	
	printf("请输入学号：");
	scanf("%d", &no);
	p = head;
	//修改指定学号的学生信息
	for (p ; p != NULL; p = p->next)
	{
	//找到并修改
		if (p->no == no)
		{
			flag = 1;
			printf("┃    学号    ┃  姓名  ┃  班级┃ 成绩1┃ 成绩2┃ 成绩3┃ 总分 ┃平均分┃\n");
			printf("┃%12d┃", p->no);
			printf("%8s┃", p->name);
			printf("%6d┃", p->cl);
			printf("%6d┃", p->grade1);
			printf("%6d┃", p->grade2);
			printf("%6d┃", p->grade3);
			printf("%6d┃", p->sum);
			printf("%6d┃\n", p->avg);
			
			printf("\n请输入名字: ");
			scanf("%s", &p->name);
			printf("\n请输入第一门成绩: ");
			scanf("%d", &p->grade1);
			printf("\n请输入第二门成绩: ");
			scanf("%d", &p->grade2);
			printf("\n请输入第三门成绩: ");
			scanf("%d", &p->grade3);
					
			p->sum = p->grade1 + p->grade2 + p->grade3;
			p->avg = (p->sum) / 3;
			save(head); 
			break;
		}
			}
	//没找到
	if (flag == 0)
		printf("没有找到\n");
		
	//关闭文件
	fclose(fp);
}


void demand()
{
	stu *h, *cur;
	FILE *fp;
	if ((fp = fopen("stu.list", "rb")) == NULL)
	{
		printf("没有记录\n");
		return;
	}
	h = load(fp);
	int choice = 0;
	printf("=======================\n");
	printf("* 1.查询最高分        *\n");
	printf("* 2.查询最低分        *\n");
	printf("* 3.查询成绩不合格学生*\n");
	printf("=======================\n");
	printf("请选择查询方式:");
	scanf("%d", &choice);
	
	switch (choice){
	case 1:
		cur = h;
		int max = 0;
		//找出最高分
		for (cur; cur != NULL; cur = cur->next)
		{
			if (cur->sum > max)
				max = cur->sum;
		}
		cur = h;
		//将最高分的人输出
		printf("┃    学号    ┃  姓名  ┃  班级┃ 成绩1┃ 成绩2┃ 成绩3┃ 总分 ┃平均分┃\n");
		for (cur; cur != NULL; cur = cur->next)
		{
			if (cur->sum == max)
			{
				printf("┃%12d┃", cur->no);
				printf("%8s┃", cur->name);
				printf("%6d┃", cur->cl);
				printf("%6d┃", cur->grade1);
				printf("%6d┃", cur->grade2);
				printf("%6d┃", cur->grade3);
				printf("%6d┃", cur->sum);
				printf("%6d┃\n", cur->avg);
			}
		}
		
		break;
	case 2:
		cur = h;
		int min = 100; //满分100
		//找出最低分
		for (cur; cur != NULL; cur = cur->next)
		{
			if (cur->sum < min)
				min = cur->sum;
		}
		cur = h;
		//将最低分的人输出
		printf("┃    学号    ┃  姓名  ┃  班级┃ 成绩1┃ 成绩2┃ 成绩3┃ 总分 ┃平均分┃\n");
		for (cur; cur != NULL; cur = cur->next)
		{
			if (cur->sum == min)
			{
				printf("┃%12d┃", cur->no);
				printf("%8s┃", cur->name);
				printf("%6d┃", cur->cl);
				printf("%6d┃", cur->grade1);
				printf("%6d┃", cur->grade2);
				printf("%6d┃", cur->grade3);
				printf("%6d┃", cur->sum);
				printf("%6d┃\n", cur->avg);
			}
		}
		break;

	case 3:
		cur = h;
		//将不及格人员输出出来
		printf("┃    学号    ┃  姓名  ┃  班级┃ 成绩1┃ 成绩2┃ 成绩3┃ 总分 ┃平均分┃\n");
		for (cur; cur != NULL; cur = cur->next)
		{
			if (cur->grade1<60 || cur->grade2<60 || cur->grade3<60)
			{
				printf("┃%12d┃", cur->no);
				printf("%8s┃", cur->name);
				printf("%6d┃", cur->cl);
				printf("%6d┃", cur->grade1);
				printf("%6d┃", cur->grade2);
				printf("%6d┃", cur->grade3);
				printf("%6d┃", cur->sum);
				printf("%6d┃\n", cur->avg);
			}
		}
		break;
	}//end of switch
			
	fclose(fp);	
}

void del()
{
	int flag=0, choice=0;
	stu *h, *p, *q;
	FILE *fp;
	if ((fp = fopen("stu.list", "rb")) == NULL)
	{
		printf("没有记录\n");
		return;
	}
	
	h = load(fp);
	printf("请输入要删除的学号:");
	scanf("%d", &choice);
	p = h;
	q = p;
	for (p ; p != NULL; q = p, p = p->next)
	{
		if (p->no == choice)
		{
			flag = 1;
			printf("┃    学号    ┃  姓名  ┃  班级┃ 成绩1┃ 成绩2┃ 成绩3┃ 总分 ┃平均分┃\n");
			printf("┃%12d┃", p->no);
			printf("%8s┃", p->name);
			printf("%6d┃", p->cl);
			printf("%6d┃", p->grade1);
			printf("%6d┃", p->grade2);
			printf("%6d┃", p->grade3);
			printf("%6d┃", p->sum);
			printf("%6d┃\n", p->avg);
			
			//头结点
			if (p == h)
				h = p->next;
			//非头结点
			else
			{
				q->next = p->next;
				free(p);
			}
			save(h);
			printf("\t删除成功!\n");
			break;
	    }
	}
	if (flag == 0)
		printf("没有找到\n");
			
	fclose(fp);
}

stu *sort(stu *p, int choice)
{
	stu *h, *q, *temp, *cmp, *before;
	h = p;
	q = p;
	before = p;
	switch (choice)
	{
	//学号排序
	case 1:
		for (p; p != NULL; q = p, p = p->next)
		{
			if (h->no > p->no)
			{
				q->next = h;
				temp = h->next;
				h->next = p->next;
				p->next = temp;
				h = p;
			}
		}
		for (p = h; p != NULL; before = p, p = p->next){
			for (cmp = p; cmp != NULL; q = cmp, cmp = cmp->next){
				if (p->no > cmp->no)
				{
					q->next = p;
					temp = p->next;
					p->next = cmp->next;
					cmp->next = temp;
					p = cmp;
					before->next = cmp;
				}
			}
		}
		break;
	//总成绩排序
	case 2:
		for (; p != NULL; q = p, p = p->next){
			if (h->sum < p->sum)
			{
				q->next = h;
				temp = h->next;
				h->next = p->next;
				p->next = temp;
				h = p;
			}
		}
		for (p = h; p != NULL; before = p, p = p->next){
			for (cmp = p; cmp != NULL; q = cmp, cmp = cmp->next){
				if (p->sum < cmp->sum)
				{
					q->next = p;
					temp = p->next;
					p->next = cmp->next;
					cmp->next = temp;
					p = cmp;
					before->next = cmp;
				}
			}
		}
		break;
	}
	return h;
}


void display()
{
	int choice = 0;
	stu *p;
	FILE *fp;
	if ((fp = fopen("stu.list", "rb")) == NULL)
	{
		printf("没有记录\n");
		return;
	}
	p = load(fp);

	printf("请选择排序方式:\n");
	printf("1.按学号排序\n");
	printf("2.按总分排序\n");
	printf("请输入选项:");
	scanf("%d", &choice);

	if (choice == 1)
		p = sort(p, 1);
	else if (choice == 2)
		p = sort(p, 2);
	else
		return;
	
	printf("┃    学号    ┃  姓名  ┃  班级┃ 成绩1┃ 成绩2┃ 成绩3┃ 总分 ┃平均分┃\n");
	for (; p != NULL; p = p->next)
	{
		printf("┃%12d┃", p->no);
		printf("%8s┃", p->name);
		printf("%6d┃", p->cl);
		printf("%6d┃", p->grade1);
		printf("%6d┃", p->grade2);
		printf("%6d┃", p->grade3);
		printf("%6d┃", p->sum);
		printf("%6d┃\n", p->avg);
	}
	
}
