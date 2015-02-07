/*
 * =====================================================================================
 *
 *       Filename:  3.c
 *
 *    Description:  一级菜单功能3，快捷服务区
 *
 *        Version:  1.0
 *        Created:  2013年12月09日 09时56分33秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lgt, lgtcarol@gmail.com
 *        Company:  Class 1203
 *
 * =====================================================================================
 */

void QuickVisit(void)
{
	int 		choice;
	while(1)
	{
		system("clear");
		choice = DisFunc();
		switch(choice)
		{
			printf("\n\t********************** 查询结果如下 ***************\n");
			case 1: printf("\t\t11)美食广场\t12)旭日院餐厅\n"); MainPart(0); break;
			case 2: printf("\t\t13)1-6#公寓楼\t14）10-16#公寓楼\n"); MainPart(0); break;
			case 3: printf("\t\t8)洗浴中心附近的医疗室\n"); MainPart(0); break;
			case 4: printf("\t\t7)图书馆二楼超市\t12)旭日院超市\n"); MainPart(0); break;
			case 5: printf("\t\t4)教学楼一楼\t11)美食广场\t12)旭日院一楼\n"); MainPart(0); break;
			case 6: break;
		}
		if(choice == 6)
		      break;
		getchar();
		getchar();
	}
}
int  DisFunc(void)
{
	int 		choice;
	printf("\n\n\n\t^^^^^^^^^^^^^^^快————>捷^^^^^^\n");
	printf("\t               &&&&&&&&&&   \\  &&&&&&&&\n");
	printf("\t                      ^^^^^^ 查————>询  ^^^^^^^^^^^^^^^^\n\n\n");
	printf("\t\t1.美食区\t2.住宿区  \t3.医务室\n");
	printf("\t\t4.超市  \t5.自动取款\t6.退出选择\n");
	printf("\t>>>>>>>> 请选择您需要的服务类型:>>>>>>>>>\n\t");
	do
	{
		scanf("%d", &choice);
		if(choice > 0 && choice < 7)
		      break;
		else
		      printf("\t------请确认后重新选择----\n\t");
	}while(1);
	return choice;
}

void MainPart(int type) 					//功能3和4用到一个菜单，0表前者
{
	int 		i, h0 = 1;
	int 		choice ;
	if(type == 0)
	{
		printf("\t>>>>>>>> 请做出您的选择(序号为相应景点的编码)：>>>>>>>>>\n\t\t");
	        scanf("%d", &g_end);
	        printf("\t\t"); DisView(); 			//给出用户可有的选择
	        printf("\t>>>>>>>> 请输入您的当前位置:>>>>>>>>>\n\t\t");
	        scanf("%d", &g_start);
	}
	while(1)
	{
		system("clear");
		show();
		scanf("%d", &choice);
		switch(choice)
		{
			case 1: if(type == 0)
				      ShortPath();  		
				else{
					g_viewsmin.totaldis = INT_MAX;
					AllPath(g_start, h0);
					ViewsMin();
				}
				break; 			//满足多个点的所有路径,通过标记进行路径值最小的选择
			case 2: if(type == 1)
				      g_viewspnt.all = 1; 				//如若没有给该成员赋值则默认要的最佳路径 
				else
				      g_viewspnt.more = 0; 				//保证不受功能4影响
				AllPath(g_start, h0); 
				g_viewspnt.all = 0; 
			default: break;
		}	
		if(choice == 3)
		      return ;
		if(choice > 3)
		      printf("\t\t~~~sorry!请确认后重新输入~~~\n\t\t");
		getchar();
		getchar();
	}

}
void show(void)
{
	printf("\n\n\t               *      *   						\n");
	printf("\t            *   *  ¡ï   *    						\n");
	printf("\t            *           *     						\n");
	printf("\t>>> >> >>  -贴心助手向您问好！-H--E--L--L--O-->>> >> >>>> 			\n");
	printf("\t              *        *       						\n");
	printf("\t                *   *       						\n");
	printf(" \t                 *                                  ");
	printf("\n\n");	

	printf("\t\t1.  ^_*  为 您 寻 找 最 省 时 省 力 的 路 径 \n");
	printf("\t\t2.  ^_*  为 您 提 供 满 足 需 求 的 所 有 路  径  \n");
	printf("\t\t3.  -_-  不 再 需 要 服 务 \n");
	printf("\t\t>>>>>>>> 请选择：>>>>>>>>>\n\t\t");
}
void ShortPath(void)
{
	int 		dist[VEXMAX], visited[VEXMAX] = {0};
	struct
	{
		int 	*path;
		int 	len;
	}short_path[VEXMAX];  						//记录最短路径的线性表		
	int 		i, min, j, k;

	for(i = 1; i <= g_G.vexnum; i++) 				//默认就先从第一个节点遍历吧
	{
		if(i == g_start)
		      continue;
		dist[i] = g_G.arc[g_start][i].dist;
		short_path[i].path = (int *)malloc(sizeof(int)*(g_G.vexnum+1));
		short_path[i].path[1] = g_G.vex[g_start].num;
		short_path[i].path[2] = g_G.vex[i].num; 
		short_path[i].len = 2;  					//申请路径空间（指针数组）并初始化
	}
	visited[g_start] = 1; 					//源点直接就在已处理好的集合中
	for(i = 1; i < g_G.vexnum; i++) 			//寻找n-1次即可
	{
		min = FindMinDist(dist, visited);      //获取最小权的路径
		visited[min] = 1; 				//将该点加入目标集合中，即已经找过源点到其的最小的路径		
		for(j = 1; j <= g_G.vexnum; j++)
		{
		      if(!visited[j] && g_G.arc[min][j].dist < INT_MAX && g_G.arc[min][j].dist+dist[min] < dist[j]) //借助刚找到的点有更短的路径到达j点
		      { 
		      	dist[j] = g_G.arc[min][j].dist + dist[min];	       //修改路径权值
			for(k = 1; k <= short_path[min].len; k++)
			      short_path[j].path[k] = short_path[min].path[k];
			short_path[j].len = short_path[min].len + 1; 		//直接在此加一
			short_path[j].path[(short_path[min].len) + 1] = g_G.vex[j].num;
 		      }
		}
	}
	printf("\t\t%s--->%s的最短路径: ", g_G.vex[g_start].name, g_G.vex[g_end].name );
	for(i = 1; i <= short_path[g_end].len; i++)
	{
		printf("%s", g_G.vex[short_path[g_end].path[i]].name);
		if(i < short_path[g_end].len)
			printf("--->");
	}
	int 	sum = 0;
	for(i = 1; i < short_path[g_end].len; i++)
	      sum += g_G.arc[short_path[g_end].path[i]][short_path[g_end].path[i+1]].dist;
	printf("  总路程：%d米", sum);
	printf("\n");
}
int FindMinDist(int dist[], int visited[])
{
	int 		min = INT_MAX;
	int 		i, index;

	for(i = 1; i <= g_G.vexnum; i++)
	{
	      if(visited[i] == 0 && dist[i] < min)
	      {
		    min = dist[i]; 					//权最小的那个下标
		    index = i;
	      }
	}
	return index;
}


void AllPath(int start, int h) 		//h0=1;
{
	int 		i, j;
	static int 	path[VEXMAX]; 				//记录路径便于回溯
	static int 	g_visited[VEXMAX] = {0};
	int 		tag = 0; 			//有时该限制条件下可能一条路径都没有，那么需提醒用户
	if(g_viewspnt.more == 1)
		g_end = g_viewspnt.des[g_viewspnt.desnum];
        path[h] = start;
	g_visited[start] = 1;
	if(g_viewspnt.more == 0)
	{
	      tag = 1; 						//如若是单目的地，则不再考虑多个景点
	      g_viewspnt.all = 1;
	}
	for(i = 1; i <= g_G.vexnum; i++) 			//只需遍历该起点的连通图即可
	{
	      if(g_G.arc[start][i].dist != INT_MAX && i == g_end )
	      {
	      	      path[h+1] = i;
		      if(tag != 1 && g_viewspnt.more == 1)
		      {
			    if(Satisfy(path, h+1) == 1)
				  tag = 1;
		      }
		      if(tag == 1) 				//反正无论如何必须得有tag=1，而它成立跟目的地有关
		      {
			      if(g_viewspnt.all == 1)
			      {
				        printf("\t");
	      	      			for(j = 1; j <= h+1; j++)
					{
	      	      	   			printf("%s", g_G.vex[path[j]].name);
						if(j < h+1)
						      printf("--->");
					}
	      	      			printf("\n");
			      }
			      else
				    MinPath(path, h+1); 			//将权值最小的路径保存在minpath中
		      } 								//在此分支处理不是所有路径
	      }
	      else if(g_G.arc[start][i].dist != INT_MAX && !g_visited[i])
	      {
	      	      path[h+1] = i;
		      AllPath(i, h+1);
              }
	}
	g_visited[start] = 0;
}

int Satisfy(int path[], int n)
{
	int 		i, j,flag, sum = 0;
	for(i = 1; i <= g_viewspnt.desnum; i++)
	{
		flag = 1;
		for(j = 1; j <= n; j++)
			if(path[j] == g_viewspnt.des[i])
			{
				flag = 0; break;
			}
		sum += flag;
	}
	if(sum == 0)
		return 1; 					//包含所有目标节点
	else{
		return 0;
	}
}

void MinPath(int path[], int n)
{
	int 	i, j, sum = 0;

	for(i = 1; i < n; i++)
		sum += g_G.arc[path[i]][path[i+1]].dist;
	if(sum < g_viewsmin.totaldis)
	      for(i = 1; i <= n; i++)
		    g_viewsmin.minpath[i] = path[i]; 		//将目前最小路径复制保存
	g_viewsmin.len = n;
}

void ViewsMin(void)
{
	int 		i, sum = 0;
	printf("\t\t********符合多景点的最短路径是：*******\n\t\t");
	for(i = 1; i <= g_viewsmin.len; i++)
	{
	      printf("%s", g_G.vex[g_viewsmin.minpath[i]].name);
	      if(i < g_viewsmin.len)
		    printf("--->");
	}
	for(i = 1; i < g_viewsmin.len; i++)
	      sum += g_G.arc[g_viewsmin.minpath[i]][g_viewsmin.minpath[i+1]].dist;
	printf(" 总路程：%d米", sum);
	printf("\n");
}
