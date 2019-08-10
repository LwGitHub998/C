#include "Maze.h"
void test1()
{
	Maze maze;
	int map[X][Y] = {
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 1, 1, 1, 1, 1, 0, 0, 0 },
		{ 0, 0, 1, 0, 0, 0, 1, 0, 0, 0 },
		{ 0, 0, 1, 0, 0, 0, 1, 0, 0, 0 },
		{ 0, 0, 1, 0, 0, 0, 1, 0, 0, 0 },
		{ 0, 0, 1, 0, 0, 0, 1, 0, 0, 0 }
	};
	MazeInit(&maze, map);//初始化
	MazePrint(&maze);//打印地图
	Postion ppost;
	ppost.x = 9;
	ppost.y = 2;
	int ret = MazeGo1(&maze, ppost);
	MazePrint(&maze);//打印地图
}
void test2()
{
	Maze maze;
	int map[X][Y] = {
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 1, 1, 1, 1, 1, 0, 0, 0 },
		{ 0, 0, 1, 0, 0, 0, 1, 0, 0, 0 },
		{ 0, 0, 1, 0, 0, 0, 1, 0, 0, 0 },
		{ 0, 0, 1, 0, 0, 0, 1, 0, 0, 0 },
		{ 0, 0, 1, 0, 0, 0, 1, 0, 0, 0 },
		{ 0, 0, 1, 1, 1, 0, 1, 0, 0, 0 },
		{ 0, 0, 1, 0, 1, 0, 1, 0, 0, 0 },
		{ 0, 0, 1, 0, 1, 0, 1, 0, 0, 0 }
	};
	MazeInit(&maze, map);//初始化
	MazePrint(&maze);//打印地图
	Postion ppost;
	ppost.x = 9;
	ppost.y = 2;
	Stack stackmin;
	StackInit(&stackmin);
	MazeGo2(&maze, ppost, &stackmin);
	MazePrint(&maze);//打印地图
}
void test3()
{
	Maze maze;
	int map[X][Y] = {
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 1, 1, 1, 1, 0, 0, 0, 0 },
		{ 0, 0, 1, 0, 0, 1, 0, 0, 0, 0 },
		{ 0, 0, 1, 0, 0, 1, 0, 0, 0, 0 },
		{ 0, 0, 1, 1, 1, 1, 0, 0, 0, 0 },
		{ 0, 0, 1, 0, 0, 1, 0, 0, 0, 0 },
		{ 0, 0, 1, 0, 0, 1, 0, 0, 0, 0 }
	};
	MazeInit(&maze, map);//初始化
	MazePrint(&maze);//打印地图
	Postion ppost;
	ppost.x = 9;
	ppost.y = 2;
	Stack stackmin;
	StackInit(&stackmin);
	MazeGo3(&maze, ppost, &stackmin);
	MazePrint(&maze);//打印地图
}
int main()
{
	test1(); //简单
	test2(); //多通路
	test3(); //带环
	system("pause");
	return 0;
}
