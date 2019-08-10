#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <windows.h>
#include <assert.h>
#include <malloc.h>
#define X 10
#define Y 10
typedef struct Maze  //迷宫地图
{
	int _map[X][Y];
}Maze, *pMaze;
typedef struct Postion  //位置
{
	int x;
	int y;
}Postion, *pPostion;

//顺序栈
#define MAXSIZE 20
typedef Postion SDataType;
typedef struct Stack
{
	SDataType array[MAXSIZE];
	int Top;
}Stack, *pStack;
void StackInit(pStack pstack);//初始化
void StackPush(pStack pstack, SDataType d);//压栈
void StackPop(pStack pstack);//出栈
int StackSize(pStack pstack);//求有效元素个数
int StackEmpty(pStack pstack);//栈是否为空  //栈为空，返回1
SDataType StackTop(pStack pstack);//查看栈顶元素


void MazeInit(pMaze pmaze, int map[X][Y]);//初始化
void MazePrint(pMaze pmaze);//打印地图
//简单地图
int MazeGo1(pMaze pmaze, Postion post);
//多通路地图
void MazeGo2(pMaze pmaze, Postion post, pStack pstackmin);
//递归
void MazeGo3(pMaze pmaze, Postion post, pStack pstackmin);
