/*
 * =====================================================================================
 *
 *       Filename:  2.c
 *
 *    Description:  一级菜单功能2，即景点信息查询(首先则是遍历所有的景点并输出)
 *
 *        Version:  1.0
 *        Created:  2013年12月09日 09时55分05秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lgt, lgtcarol@gmail.com
 *        Company:  Class 1203
 *
 * =====================================================================================
 */

void ViewInfo(void)
{
	int 		choice;
	while(1)
	{
		system("clear");
		DisView();
		printf("\t>>>>>>>>请输入您想详细了解的景点的序号:>>>>>>>>\n\t\t");
		scanf("%d", &choice);
		if(choice > 0 && choice <= g_G.vexnum)
		      printf("\t%s\n", g_G.vex[choice].intr);
		else if(choice == g_G.vexnum+1)
		      break;
		else
		      printf("\t ^_^ ,sorry!请检查后重新输入 > > >\n");
		getchar();
		getchar();
	}
}
void DisView(void)
{
	int  	i, j;
	printf("\n\n");
	printf("\t$@$@$@$@ 景点编号 ********* 景点名称 @$@$@$@$\n");
	for(i = 1; i <= g_G.vexnum; i++)
		printf("\t\t  %d  \t\t  %s\n", i, g_G.vex[i].name);
	printf("\t\t  %d  \t\t  %s\n", g_G.vexnum+1, "结束选择");
}
