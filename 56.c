/*
 * =====================================================================================
 *
 *       Filename:  56.c
 *
 *    Description:  一级菜单的功能5，6. 即添加景点道路信息 和 关节点的寻找
 *
 *        Version:  1.0
 *        Created:  2013年12月11日 16时42分01秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lgt, lgtcarol@gmail.com
 *        Company:  Class 1203
 *
 * =====================================================================================
 */

void InsertView(void)
{
	int 		nvex, narc;
	int 		head, tail, weight;
	int 		i, j;
	system("clear");
	PrintWarn();
	printf("\t\t>>>>>>>> 请输入新增的景点个数: >>>>>>>>>> ");
	scanf("%d", &nvex);
	printf("\t>>>>>>>>> 请输入%d个景点名字 >>>>>>>>>\n", nvex);
	for(i = 1; i <= nvex; i++)
	{      
		g_G.vex[g_G.vexnum+i].num = g_G.vexnum + i;
		printf("\t\tNO.%d(编号：%d): ", i, g_G.vexnum + i);
		scanf("%s", g_G.vex[g_G.vexnum+i].name);
		printf("\t\t简介：");
		scanf("%s", g_G.vex[g_G.vexnum+i].intr);
	}
	InitNew(nvex); 								//新的方阵的初始化
	printf("\t\t>>>>>>>> 请输入新增的道路的条数: >>>>>>>>>> ");
	scanf("%d", &narc);
	printf("\t\t>>>>>>>> 请输入%d条道路的信息(请使用上示的编号代替景点名称) >>>>>>>>>\n", narc);
	printf("\n\t<<<<<<<< 为您提供原有景点编号供您参考 <<<<<<<<<<");
	for(i = 1; i <= narc; i++)
	{
		printf("\t\tNO.%d: ", i);
		scanf("%d %d %d", &head, &tail, &weight);
	        g_G.arc[head][tail].dist = weight;              //无向网
		printf("\t\t     道路信息（例如：名称，沿途风景等）：");
		scanf("%s", g_G.arc[head][tail].intr);		
		memcpy(&g_G.arc[tail][head], &g_G.arc[head][tail], sizeof(ArcType));
  	}
	g_G.vexnum += nvex; 							//改变矩阵大小
	g_G.arcnum += narc;
	SaveFile();
}

void PrintWarn(void)
{
	printf("\n\n\n");
	printf("\t          ——————————————————————————\n");
	printf("\t******** 【您正在进行系统信息的更改】 ********\n");
	printf("\t          ——————————————————————————\n\n");
}

void InitNew(int nvex)
{
	int 		i, j;
	//考虑列的变化
	for(i = 1; i <= g_G.vexnum+nvex; i++)
		for(j = g_G.vexnum+1; j <= g_G.vexnum+nvex; j++)
		{
			g_G.arc[i][j].dist = INT_MAX;
			strcpy(g_G.arc[i][j].intr, "");
		}
	//考虑行的变化
	for(i = g_G.vexnum+1; i <= g_G.vexnum+nvex; i++)
		for(j = 1; j <= g_G.vexnum+nvex; j++)
		{
			g_G.arc[i][j].dist = INT_MAX;
			strcpy(g_G.arc[i][j].intr, "");
		}

}

void SaveFile(void)
{

	int 		i, j;
	FILE 	        *fp;
	
	if((fp = fopen("viewinfo", "wt+")) == NULL)
	{
		printf("\t\t*****写入文件出错！*****\n");
		exit(1);
	}

	fprintf(fp, "%d %d", g_G.vexnum, g_G.arcnum); 		//读取矩阵大小
	for(i = 1; i <= g_G.vexnum; i++) 				//节点信息
	{
	  	  fwrite(&g_G.vex[i], sizeof(VexType), 1, fp);
	}
	for(i = 1; i <= g_G.vexnum; i++)  				//边信息				
	      for(j = 1; j <= g_G.vexnum; j++)
		    	 fread(&g_G.arc[i][j], sizeof(ArcType), 1, fp);					      
	fclose(fp);
}
void KeyPnt(void)
{
	printf("key\n");
}
