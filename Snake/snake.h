#ifndef __SNAKE_H__
#define __SNAKE_H__
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//#define WALL '▇'  //2字节  墙 蛇
//#define FOOD '■'  //2字节  食物

#define INIT_X 26  //初始位置列
#define INIT_Y 12  //初始位置行

enum Direction //蛇的运动方向
{
	UP, //上
	DOWN, //下
	LEFT,  //左
	RIGHT  //右
};
enum Gamestatus  //游戏状态  
{
	OK,  //正常状态
	NORMAL_END,  //正常退出
	KILL_BY_WALL,  //撞墙死亡
	KILL_EY_SELF  //撞蛇死亡
};

typedef struct SnakeNode  //结点位置
{
	int x;
	int y;
	struct SnakeNode* next;
}SnakeNode, *pSnakeNode;
typedef struct Snake //游戏框架
{
	pSnakeNode _pSnake;  //蛇头指针
	pSnakeNode _pFood;  //食物位置指针
	int _TotalScore; //得分
	int _AddScore;  //增加的分数
	int _SleepTime;  //休眠时间
	enum Direction _Dir;//方向
	enum Gamestatus _status;//游戏状态
}Snake, *pSnake;

void HideCursor();//隐藏光标显示，调用一次
void SerPos(int x, int y);//定位光标
void WecomeToGame();//打印欢迎界面
void CreateMap();//创建地图
pSnakeNode BuyNode(); //创捷新结点
void InitSnake(pSnake ps);//初始化蛇
void CreateFood(pSnake ps);//生成食物
void Pause();//时间暂停
void DirectionOfDdtermination(pSnake ps);//键盘输入操作
void EatFood(pSnake ps, pSnakeNode snewnode);//吃食物
void NoFood(pSnake ps, pSnakeNode snewnode);//无食物
void SnakeMovement(pSnake ps);//蛇移动
void PrintInformation(pSnake ps);//打印信息
void KillByWall(pSnake ps);//被墙撞死
void KillBySelf(pSnake ps);//被蛇撞死
void GameStart(pSnake ps);//游戏开始
void GameRun(pSnake ps); //游戏过程
void GameEnd(pSnake ps);//游戏结束


#endif __SNAKE_H__
