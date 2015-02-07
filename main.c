/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  函数大致框架的调用关系及一些菜单的显示
 *
 *        Version:  1.0
 *        Created:  2013年12月09日 08时50分53秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lgt, lgtcarol@gmail.com
 *        Company:  Class 1203
 *
 * =====================================================================================
 */
#ifndef HEAD_H
#define HEAD_H
       #include "head.h"
#endif
#include "0.c"
#include "1.c"
#include "2.c"
#include "3.c"
#include "4.c"
#include "56.c"

int main(int argc, char *argv[])
{
	int 			choice;
	while(1)
	{
		system("clear");	
		Welcome(); 						//系统主界面
		scanf("%d", &choice);
		if(choice == 3)
		      return 0;
		else if(choice < 1 || choice > 3)
		{
			printf("\t\tsorry!请检查您的输入>>>\n");
			continue;
		}
		else
		{
		      DocutId(choice);     				//记录用户的登录身份
		      MainMenu(); 					//一级主菜单
		      break;
		}
		getchar();
		getchar();
	}

	return 0;
}

void Welcome(void)
{
	printf("\n\n\n");
	printf("\t           *     * *     *     						\n");
	printf("\t          *  ¡ï   *  ¡ï   *    						\n");
	printf("\t           *      ¡ï     *     						\n");
	printf("\t>>>------ --欢迎使用西邮校园导游系统-----  ----> 			\n");
	printf("\t             *         *       						\n");
	printf("\t               *  ¡ï *       						\n");
	printf("\t                *   *          						\n");
	printf("\t                 * *          						\n");
	printf("\t                  *   							\n");
	printf("\n\n");	

	printf("\t			***************	 普通游客登录          ************* 1 **************\n");
	printf("\t			***************	 管理员登录            ************* 2 **************\n");
	printf("\t			***************	 退出系统              ************* 3 **************\n\t");
	printf("\n\n");
	printf("\t>>>>>>>	>>>亲,请选择您的身份...>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\t");
}
void DocutId(int choice)
{
	char 		passwd[NAMSIZ]; 
	int 		i = 0;
	if(choice == 1)
	      printf("～～～亲，祝您游览开心！～～～\n");
	else if (choice == 2)
	{
		printf("\t---------您将至多有三次输入机会，否则将视您为普通游客！---------\n");
		while(i < 3)
		{
			printf("\t请输入您的登录口令:");
			memset(passwd,'\0', sizeof(passwd));
			system("stty -echo");
			scanf("%s", passwd);
			system("stty echo");
			if(strcmp(passwd, "lgtcarol") != 0)
				printf("~ ~ ~sorry!您的口令有误～～～\n");
			else{
		      		g_id = 1;  				//此人为管理员
				break;
			}
			i++;
		}
	}
	else
	      exit(0);
}
void MainMenu(void)
{
	int 		choice;
	int 		once = 0; 					//一次只进行一次系统信息的读入
	while(1)
	{
		system("clear");	
		FirstShow();
		scanf("%d", &choice);
		if(once == 0 &&choice != 0 && choice != 5)
		{
		      ReadFile(&g_G);
		      once = 1; 					//在退出前将永久不在读取系统信息，除非有管理员的操作
		}
		switch(choice)
		{
			case 0: if(g_id == 1)  CreatAdjMatrix();
				else 	       printf("\tsorry!您不是管理员，此操作关系重大呦～～～\n");	 break;
			case 1: PrintView(); break;
			case 2: ViewInfo(); break;
			case 3: QuickVisit(); break;
			case 4: BeginTrav(); break;
			case 5: InsertView(); break;
			case 6: KeyPnt(); break;
			case 7: break;
			default : printf("\t\t^_^!功能有限,请检查后重新输入~~~\n"); break;
		}
		if(choice == 7)
		      return ;
		getchar();
		getchar();
	}
	
}
void FirstShow(void)
{
	printf("\n\n\n");
	printf("\t><><><><><><><><><><><<><><><><><><><><><><><><<><><><><><><><><><><><><><><><>\n");
	printf("\t||      ****************	 系统首页     ***************                  || \n");
	printf("\t><><><><><><><><><>><><><><><><><><><><><><><><<><><><><><><><><><><><><><><><>\n");
	printf("\t\t0.初始化系统\n");
	printf("\t\t1.查看景点分布图\n");
	printf("\t\t2.景点详介\n");
	printf("\t\t3.快捷服务区\n");
	printf("\t\t4.开始游览\n");
	printf("\t\t5.扩充景点及道路信息\n");
	printf("\t\t6.搜索校园图的关节点\n");
	printf("\t\t7.退出系统\n");	
	printf("\t\t>>>>请选择:>>>>>>\n\t\t");
}


