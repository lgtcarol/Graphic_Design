/*
 * =====================================================================================
 *
 *       Filename:  init.c
 *
 *    Description:  通过键盘输入的方式创建信息文件，然后在系统中可以直接读取（如若此，那么就要在管理员权限中写回文件）
 *
 *        Version:  1.0
 *        Created:  2013年12月09日 10时28分02秒
 *       Revision:  none
 *       Compiler:  g_Gcc
 *
 *         Author:  lg_Gt, lg_Gtcarol@g_Gmail.com
 *        Company:  Class 1203
 *
 * =====================================================================================
 */


void CreatAdjMatrix(void)
{
	int 	i, j; 				
	int 	head, tail, weight; 						//保存边的序号
	AdjMatrix G; 	  				//在创建系统信息时用到
	FILE 	*fp;
	
	if((fp = fopen("viewinfo", "at+")) == NULL)
	{
		printf("viewinfo打开出错！\n");
		exit(0);
	}
						
	printf("\t>>>>>>>> 请分别输入景点个数（不超过%d个）和道路数: >>>>>>>>>>>\n\t\t", VEXMAX-1);
	scanf("%d %d", &G.vexnum, &G.arcnum);
	fprintf(fp, "%d %d", G.vexnum, G.arcnum); 			//将矩阵大小写入文件
	for(i = 1; i <= G.vexnum; i++) 				
	      for(j = 1; j <= G.vexnum; j++)
	      {
			      G.arc[i][j].dist = INT_MAX;
			      strcpy(G.arc[i][j].intr, "");
	      }
	printf("\t>>>>>>>>> 请输入%d个景点名字 >>>>>>>>>\n", G.vexnum);
//	g_vexnum = G.vexnum;
	for(i = 1; i <= G.vexnum; i++)
	{      
		G.vex[i].num = i;
		printf("\t\tNO.%d: ", i);
		scanf("%s", G.vex[i].name);
		printf("\t\t简介：");
		scanf("%s", G.vex[i].intr);
		fwrite(&G.vex[i], sizeof(VexType), 1, fp); 		//所有节点写入文件
	}
	printf("\t>>>>>>>> 请输入%d条道路的信息 >>>>>>>>>\n", G.arcnum);
//	g_arcnum = G.arcnum;
	for(i = 1; i <= G.arcnum; i++)
	{
		printf("\t\tNO.%d: ", i);
		scanf("%d %d %d", &head, &tail, &weight);
//		fprintf(fp, "%d %d", head, tail); 			//将边相关的节点标号存入文件
	        G.arc[head][tail].dist = weight;              //无向网
		printf("\t\t     道路信息（例如：名称，沿途风景等）：");
		scanf("%s", G.arc[head][tail].intr);		
		memcpy(&G.arc[tail][head], &G.arc[head][tail], sizeof(ArcType));
  // 	        fwrite(&G.arc[head][tail], sizeof(ArcType), 1, fp); 		//注意：在次只读入了一条边，还原时注意将对称位置恢复
	}
	//将完整的矩阵写入文件
	for(i = 1; i <= G.vexnum; i++)
	      for(j = 1; j <= G.vexnum; j++)
		    fwrite(&G.arc[i][j], sizeof(ArcType), 1, fp);
	ReadFile(&g_G);
	fclose(fp);
}
#if 0
int LocateArc(int vex)
{
	int 	i;
	for(i = 1; i <= G.vexnum; i++)
	      if(G.vex[i].num == vex)
		    return i;
	printf("关系不存在!\n");
	exit(1);
}
#endif
void ReadFile(AdjMatrix *g_G)  					//**注意：避免无向图的输出对视觉的不爽
{ 				
	int 		i, j;
	FILE 	*fp;
	if((fp = fopen("viewinfo", "r")) == NULL)
		return ;

	fscanf(fp, "%d %d", &g_G->vexnum, &g_G->arcnum); 		//读取矩阵大小
	for(i = 1; i <= g_G->vexnum; i++) 				//节点信息
	{
	  	  fread(&g_G->vex[i], sizeof(VexType), 1, fp);
	}
	for(i = 1; i <= g_G->vexnum; i++)  				//边信息				
	      for(j = 1; j <= g_G->vexnum; j++)
		    	 fread(&g_G->arc[i][j], sizeof(ArcType), 1, fp);					      
	fclose(fp);
}
