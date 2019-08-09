#define _CRT_SECURE_NO_WARNINGS 1
#include "snake.h"
//按任意键时按空格游戏会自动暂停
//按与蛇身相反的键时不会有反应，但是在按一个键会出现这个键的反应
void HideCursor()//隐藏光标显示，调用一次
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
void SerPos(int x, int y) //定位光标，将光标调整到(x,y)的位置 列，行
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//获取标准输出的句柄
	COORD pos = { 0 };
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos); //设置标准输出上光标的位置为pos
}
void WecomeToGame()//打印欢迎界面
{
	//设置窗口大小
	system("mode con cols=100 lines=30");//设置DOS窗口的尺寸将会变为100列30行的
	/*
	键入mode con cols = 100 lines = 30
	则DOS窗口的尺寸将会变为30行100列的，
	cols(列)最小值为13，lines(行)最小值为1。
	在C语言中也可以通过system函数调用这个dos命令来实现这个功能。
	*/

	//打印文字
	SerPos(37, 12); //定位光标 列，行
	printf("欢迎来到贪吃蛇小游戏");
	SerPos(37, 20);
	system("pause");
	system("cls");
	SerPos(37, 12); //定位光标 列，行
	printf("提示：↑ ↓ ← → 控制贪吃蛇方向");
	SerPos(37, 13); //定位光标 列，行
	printf("提示：F1：加速，F2，减速  加速可获得更高的分数");
	SerPos(37, 20);
	system("pause");
	system("cls");
}
void CreateMap()//创建地图 60列 * 28行
{
	int i = 0;
	//上边界
	for (i = 0; i < 60; i = i + 2)
	{
		SerPos(i, 0); //定位光标 列，行
		printf("%s", "▇");
	}
	//下边界
	for (i = 0; i < 60; i = i + 2)
	{
		SerPos(i, 27); //定位光标 列，行
		printf("%s", "▇");
	}
	//左边界
	for (i = 1; i < 27; i++)
	{
		SerPos(0, i); //定位光标 列，行
		printf("%s", "▇");
	}
	
	//右边界
	for (i = 1; i < 27; i++)
	{
		SerPos(58, i); //定位光标 列，行
		printf("%s", "▇");
	}
	
}
pSnakeNode BuyNode() //创捷新结点
{
	pSnakeNode psnake = (pSnakeNode)malloc(sizeof(SnakeNode));
	if (NULL == psnake)
	{
		perror(NULL);
		exit(EXIT_FAILURE);
	}
	psnake->next = NULL;
	return psnake;
}
void InitSnake(pSnake ps)//初始化蛇
{
	//创建第一个结点
	pSnakeNode first = BuyNode();
	first->x = INIT_X;
	first->y = INIT_Y;
	//创建剩余结点
	pSnakeNode cur;
	for (int i = 0; i < 4; i++)
	{
		//创建结点
		cur = BuyNode();
		cur->x = first->x + 2;
		cur->y = first->y;
		//插入节点（头插）
		cur->next = first;
		first = cur;
	}
	ps->_pSnake = first; //蛇头指针
	//打印蛇
	while (cur != NULL)  //循环cur指向第一个结点
	{
		SerPos(cur->x, cur->y);
		printf("%s", "■");
		cur = cur->next;
	}
	printf("\n");

}
void CreateFood(pSnake ps)//生成食物
{
	pSnakeNode pfood = BuyNode();  //食物结点
again:
	//随机生成食物的位置
	do  //列
	{
		pfood->x = rand()%55 + 2; //2-56 0-54+2
	} while (0 != pfood->x % 2);  //x必须为偶数，否则蛇吃不到
	pfood->y = rand() % 26 + 1;//1-26 0-25+//行

	pSnakeNode cur = ps->_pSnake;  //蛇头
	while (NULL != cur) //遍历蛇身，防止食物出现在蛇身上
	{
		if (cur->x == pfood->x && cur->y == pfood->y)
		{
			//CreateFood(ps);//使用递归在函数返回时会再一次改变pfood的值
			goto again; //跳转至again处
		}
		cur = cur->next;
	}
	ps->_pFood = pfood;
	SerPos(pfood->x, pfood->y);
	printf("%s", "★");
}
void Pause()//时间暂停
{
	while (1)
	{
		Sleep(100);
		if (GetAsyncKeyState(VK_SPACE))
		{
			break;
		}
	}
}
void DirectionOfDdtermination(pSnake ps)//键盘输入操作
{
	if (DOWN != ps->_Dir && GetAsyncKeyState(VK_UP))//向上 ???不能走回去
	{
		ps->_Dir = UP;
	}
	else if (UP != ps->_Dir && GetAsyncKeyState(VK_DOWN))//向下
	{
		ps->_Dir = DOWN;
	}
	else if (RIGHT != ps->_Dir && GetAsyncKeyState(VK_LEFT))//向左 
	{
		ps->_Dir = LEFT;
	}
	else if (LEFT != ps->_Dir && GetAsyncKeyState(VK_RIGHT))//向右 
	{
		ps->_Dir = RIGHT;
	}
	else if (GetAsyncKeyState(VK_SPACE))//暂停
	{
		Pause();//时间暂停 ???如果任意键为空格，则会读取一个空格
	}
	else if (GetAsyncKeyState(VK_ESCAPE))//退出
	{
		ps->_status = NORMAL_END;
	}
	else if (GetAsyncKeyState(VK_F1))//加速
	{
		//300
		if (ps->_AddScore < 15)
		{
			ps->_AddScore = ps->_AddScore + 1;  //增加的分数+1
			ps->_SleepTime = ps->_SleepTime - 30;  //休眠时间-30  min=150
		}
	}
	else if (GetAsyncKeyState(VK_F2))//减速
	{
		if (ps->_AddScore > 5)
		{
			ps->_AddScore = ps->_AddScore - 1;  //增加的分数-1
			ps->_SleepTime = ps->_SleepTime + 30;  //休眠时间-30 max = 450
		}
		
	}
}
void EatFood(pSnake ps, pSnakeNode snewnode)//吃食物
{
	//把新节点插入到蛇中
	snewnode->next = ps->_pSnake;
	ps->_pSnake = snewnode;
	//打印新结点 //可有可无
	SerPos(ps->_pSnake->x, ps->_pSnake->y);
	printf("■");
	//加分
	ps->_TotalScore = ps->_TotalScore + ps->_AddScore;
	//重新生成食物
	CreateFood(ps);
}
void NoFood(pSnake ps, pSnakeNode snewnode)//无食物
{
	//把新节点插入到蛇中
	snewnode->next = ps->_pSnake;
	ps->_pSnake = snewnode;
	//打印新结点
	SerPos(ps->_pSnake->x, ps->_pSnake->y);
	printf("%s", "■");
	//处理尾结点 需要把倒数第二个结点的next变成空
	pSnakeNode cur = ps->_pSnake;
	while (cur->next->next != NULL)  //尾结点
	{
		cur = cur->next;
	}
	SerPos(cur->next->x, cur->next->y);
	printf(" ");
	free(cur->next);
	cur->next = NULL;
}
void SnakeMovement(pSnake ps)//蛇移动
{
	pSnakeNode  snewnode = BuyNode(); //创捷新结点
	switch (ps->_Dir)
	{
	case UP://向上
	{
				//新结点赋值
				snewnode->x = ps->_pSnake->x;
				snewnode->y = ps->_pSnake->y - 1;
				//判断是否为食物
				if (snewnode->x == ps->_pFood->x && snewnode->y == ps->_pFood->y) //是食物
				{
					EatFood(ps, snewnode);
				}
				else//不是食物
				{
					NoFood(ps, snewnode);
				}
	}
		break;
	case DOWN://向下
	{
				  //新结点赋值
				  snewnode->x = ps->_pSnake->x;
				  snewnode->y = ps->_pSnake->y + 1;
				  //判断是否为食物
				  if (snewnode->x == ps->_pFood->x && snewnode->y == ps->_pFood->y) //是食物
				  {
					  EatFood(ps, snewnode);
				  }
				  else//不是食物
				  {
					  NoFood(ps, snewnode);
				  }
	}
		break;
	case LEFT://向左
	{
				  //新结点赋值
				  snewnode->x = ps->_pSnake->x - 2;
				  snewnode->y = ps->_pSnake->y;
				  //判断是否为食物
				  if (snewnode->x == ps->_pFood->x && snewnode->y == ps->_pFood->y) //是食物
				  {
					  EatFood(ps, snewnode);
				  }
				  else//不是食物
				  {
					  NoFood(ps, snewnode);
				  }
	}
		break;
	case RIGHT://向右
	{
				   //新结点赋值
				   snewnode->x = ps->_pSnake->x + 2;
				   snewnode->y = ps->_pSnake->y;
				   //判断是否为食物
				   if (snewnode->x == ps->_pFood->x && snewnode->y == ps->_pFood->y) //是食物
				   {
					   EatFood(ps, snewnode);
				   }
				   else//不是食物
				   {
					   NoFood(ps, snewnode);
				   }
	}
		break;
	}
}
void PrintInformation(pSnake ps)//打印信息
{
	//打印得分
	SerPos(70, 10);
	printf("得分：%d ", ps->_TotalScore);
	SerPos(70, 11);
	printf("当前所加得分：%d ", ps->_AddScore);
	//打印文字
	SerPos(70, 12);
	printf("↑ ↓ ← → 控制贪吃蛇方向");
	SerPos(70, 13);
	printf("提示：");
	SerPos(70, 14);
	printf("F1：加速，F2：减速");
	SerPos(70, 15);
	printf("空格：暂停");
	SerPos(70, 16);
	printf("Esc：退出");
}
void KillByWall(pSnake ps)//被墙撞死
{
	//2-58 1-26
	if (
		ps->_pSnake->x< 2 ||
		ps->_pSnake->x > 56 ||
		ps->_pSnake->y < 1 ||
		ps->_pSnake->y > 26
		)
	{
		ps->_status = KILL_BY_WALL;
	}
}
void KillBySelf(pSnake ps)//被蛇撞死
{
	pSnakeNode cur = ps->_pSnake->next;
	while (NULL != cur)
	{
		if (ps->_pSnake->x == cur->x && ps->_pSnake->y == cur->y)
		{
			ps->_status = KILL_EY_SELF;
			return;
		}
		cur = cur->next;
	}
}
void GameStart(pSnake ps)  //游戏开始
{
	//打印欢迎界面
	WecomeToGame();
	//创建地图
	CreateMap();
	//初始化蛇
	InitSnake(ps);
	//初始化食物
	CreateFood(ps);
	//初始化其他数据
	ps->_TotalScore = 0; //得分
	ps->_AddScore = 10;  //增加的分数
	ps->_SleepTime = 500;  //休眠时间
	ps->_Dir = RIGHT;//方向
	ps->_status = OK;//游戏状态
}
void GameRun(pSnake ps) //游戏过程
{
	do
	{
		DirectionOfDdtermination(ps);//键盘输入操作
		SnakeMovement(ps);//蛇移动
		PrintInformation(ps);//打印信息
		KillByWall(ps);//被墙撞死
		KillBySelf(ps);//被蛇撞死
		Sleep(ps->_SleepTime); //蛇睡眠
	} while (OK == ps->_status);

}
void GameEnd(pSnake ps)//游戏结束
{
	if(NORMAL_END == ps->_status)
	{
		SerPos(22, 13);
		printf("游戏结束！");
	}
	else if(KILL_BY_WALL == ps->_status)
	{
		SerPos(22, 13);
		printf("撞墙，游戏结束！");
	}
	else if (KILL_EY_SELF == ps->_status)
	{
		SerPos(22, 13);
		printf("撞蛇身，游戏结束！");
	}
	//释放蛇
	while (NULL != ps->_pSnake)
	{
		pSnakeNode del = ps->_pSnake;
		ps->_pSnake = ps->_pSnake->next;
		free(del);
		del = NULL;
	}
	//释放食物
	free(ps->_pFood);
	ps->_pFood = NULL;
}
