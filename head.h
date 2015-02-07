/*
 * =====================================================================================
 *
 *       Filename:  head.h
 *
 *    Description:  包含所有的头文件，全局变量，函数声明 
 *
 *        Version:  1.0
 *        Created:  2013年12月09日 08时39分47秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lgt, lgtcarol@gmail.com
 *        Company:  Class 1203
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
//#include <io.h>
#define NAMSIZ  200
#define DESCRIBE 800
#define VEXMAX  20

typedef struct
{
	int 		num;
	char 		name[NAMSIZ];
	char 		intr[DESCRIBE];
}VexType;
typedef struct
{
	int 		dist;
	char    	intr[DESCRIBE];
}ArcType;
typedef struct
{
	VexType 	vex[VEXMAX];
	ArcType 	arc[VEXMAX][VEXMAX];
	int 		vexnum;
	int 		arcnum;
}AdjMatrix;

AdjMatrix       g_G; 				//定义全局的图结构

int 		g_id; 					//用于区分登录者的身份
int 		g_start;
int 		g_end;
int 		g_reend;
struct
{
	int 	minpath[VEXMAX];
	int 	len;
	int 	totaldis;
}g_viewsmin;
struct
{
	int 	des[VEXMAX];
	int 	desnum;
	int 	more;			//用来标记是否当前有多个目的地要游览
	int 	all;
}g_viewspnt; 		  			//用于多景点游览


void Welcome(void);
void DocutId(int choice);
void MainMenu(void);
void FirstShow(void);
void PrintView(void);
void DisView(void);
void ViewInfo(void);
void QuickVisit(void);
void BeginTrav(void);
void CreatAdjMatrix(void);
void ReadFile(AdjMatrix *G); 			//加载系统信息

int  DisFunc(void);
void MainPart(int type) ;
void show(void);
void ShortPath(void);
int FindMinDist(int dist[], int visited[]);
void AllPath(int start, int h0);
int Satisfy(int path[], int n);
void MinPath(int path[], int n);
void ViewsMin(void);
void MiniTree(void);
int FindMinCost(int lowcost[]);

void InsertView(void);
void PrintWarn(void);
void InitNew(int nvex);
void SaveFile(void);

void KeyPnt(void);
