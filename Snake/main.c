#include "snake.h"

void test()
{
	HideCursor();//隐藏光标显示，调用一次
	srand((unsigned)time(NULL));
	Snake snake;  //创建游戏框架
	GameStart(&snake);  //游戏开始
	GameRun(&snake);  //游戏过程
	GameEnd(&snake);  //游戏结束
	SerPos(0, 29);
}
int main()
{
	test();
	system("pause");
	return 0;
}
