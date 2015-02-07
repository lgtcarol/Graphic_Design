/*
 * =====================================================================================
 *
 *       Filename:  4.c
 *
 *    Description:  一级菜单功能4，实现任意点的最短和所有路径，包括多景点的游览
 *
 *        Version:  1.0
 *        Created:  2013年12月09日 09时58分19秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lgt, lgtcarol@gmail.com
 *        Company:  Class 1203
 *
 * =====================================================================================
 */

void BeginTrav(void)
{
	int 		choice, rechoice, i;
	while(1)
	{
		system("clear");
		DisView();
		printf("\t******* 亲，您是有很想去的景点？(1.是  2.否  3.放弃)****\n\t\t");
		scanf("%d", &choice);
		if(choice == 1)
		{
			g_viewspnt.more = 1;
			printf("\t\t请输入您的起点：");
			scanf("%d", &g_start);
			printf("\n\t\t>>>>您中意的景点有几个呢？>>>>>>： ");
			scanf("%d", &g_viewspnt.desnum);
			printf("\n\t^_^, 温馨提醒：输入完毕将自动跳转到 \"贴心服务界面\" ～～～～～～");
			printf("\n\t>>>>>>>> 请输入您想游览的景点，最后一个默认为目的地 >>>>>>>>>\n\t\t");
			for(i = 1; i <= g_viewspnt.desnum; i++)
				scanf("%d", &g_viewspnt.des[i]);
//			printf("\t****您是出于怎样的想法选择路线呢？****\n\n");
			MainPart(1);
		}
		else if(choice == 2)
		{
			printf("\n\t\t ——————————————————————————————————————————————————————————\n");
			printf("\t\t|*****贴心为您提供一些涉及所有景点的便捷小道供您参考！*****|\n");
			printf("\t\t ——————————————————————————————————————————————————————————\n");
			printf("\t\t>>>>>> 请输入您当前的位置:>>>>>>\n\t\t");
			scanf("%d", &g_start);
			MiniTree(); 						//最小生成树
		}
		else
		      break ;
		getchar();
		printf("\t\t按任意键继续...");
		getchar();
	}
	g_viewspnt.more = 0;
	g_viewspnt.all = 0; 							//全局变量恢复
}

void MiniTree(void)
{
	int 		lowcost[VEXMAX];
//	char 		adjvex[MAXVEX]; 
	int 		adjvex[VEXMAX]; 				
	int 		i, min, j;

	lowcost[g_start] = 0; 					        //lowcost = 0代表在目标集合内
	for(i = 1; i <= g_G.vexnum; i++) 				//默认就先从第一个节点遍历吧
	{
		if(i == g_start)
		      continue;
		lowcost[i] = g_G.arc[g_start][i].dist;
		adjvex[i] = g_start; 				      //初始化辅助数组
	}
	printf("\t\t######遍游所有景点的代价最小：#######\n");
	for(i = 1; i < g_G.vexnum; i++) 			//尽管说第一个没有比较的意义但便于将来不从第一个开始找
	{
		min = FindMinCost(lowcost);
//		printf("(%c %c) : %d\n", adjvex[min], G->vex[min], lowcost[min]);
		printf("\t\t%s ---> %s   %d米\n", g_G.vex[adjvex[min]].name, g_G.vex[min].name, g_G.arc[adjvex[min]][min].dist);
		lowcost[min] = 0; 				//将该点加入目标集合中
		for(j = 1; j <= g_G.vexnum; j++)
		      if(g_G.arc[min][j].dist < lowcost[j])
		      {
		      	lowcost[j] = g_G.arc[min][j].dist; 		
			adjvex[j] = min;
		      }
	}
#if 0
	printf("最小生成树：\n");
	for(i = 1; i <= G->vexnum; i++) 			//第一个结点略过
		printf("(%c, %c): %d\n", adjvex[i], G->vex[i], lowcost[i]);
#endif
}
int FindMinCost(int lowcost[])
{
	int 		min = INT_MAX;
	int 		i, index;

	for(i = 1; i <= g_G.vexnum; i++)
	      if(lowcost[i] != 0 && lowcost[i] < min)
	      {
		    min = lowcost[i]; 					//权最小的那个下标
		    index = i;
	      }
	return index;
}

