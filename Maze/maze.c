#include "Maze.h"
//初始化
void StackInit(pStack pstack)
{
	assert(pstack);
	pstack->Top = 0;
}
//压栈
void StackPush(pStack pstack, SDataType d)
{
	assert(pstack);
	if (MAXSIZE == pstack->Top)
	{
		return;
	}
	pstack->array[pstack->Top] = d;
	pstack->Top++;
}
//出栈
void StackPop(pStack pstack)
{
	assert(pstack);
	if (0 == pstack->Top)
	{
		return;
	}
	pstack->Top--;
}
//求有效元素个数
int StackSize(pStack pstack)
{
	assert(pstack);
	return pstack->Top;
}
//栈是否为空
int StackEmpty(pStack pstack)
{
	assert(pstack);
	return pstack->Top == 0;
}
//查看栈顶元素
SDataType StackTop(pStack pstack)
{
	assert(pstack);
	if (0 == pstack->Top)
	{
		assert(0);
	}
	return pstack->array[pstack->Top - 1];


}



//迷宫
//初始化
void MazeInit(pMaze pmaze, int map[X][Y])
{
	//初始化迷宫
	//地图初始化
	for (int i = 0; i < X; i++)
	{
		for (int j = 0; j < Y; j++)
			pmaze->_map[i][j] = map[i][j];
	}
}
//打印地图
void MazePrint(pMaze pmaze)
{
	for (int i = 0; i < X; i++)
	{
		for (int j = 0; j < Y; j++)
			printf("%d ", pmaze->_map[i][j]);
		printf("\n");
	}
	printf("\n");
}
//探测地图
int MazeProbe(pMaze pmaze, Postion post)
{
	if (pmaze->_map[post.x][post.y] == 1)
		return 1;
	return 0;
}
//检测入口点是否合法
int Entrance(pMaze pmaze, Postion post)
{
	if ((post.x == 0 || post.x == X - 1 || post.y == 0 || post.y == Y - 1) && (pmaze->_map[post.x][post.y] == 1)) //在边界,同时入口点为1
	{
		return 1;
	}
	return 0;
}
//检测是否为出口
int Exit(pMaze pmaze, Postion post, Postion cur)
{
	if ((cur.x != post.x || cur.y != post.y) && (cur.x == 0 || cur.x == X - 1 || cur.y == 0 || cur.y == Y - 1))
	{
		return 1;
	}
	return 0;
}
//简单地图
int MazeGo1(pMaze pmaze, Postion post) //入口点
{
	//地图不为空
	assert(pmaze);
	//检测入口点是否合法
	if (!Entrance(pmaze, post))
	{
		return -1;
	}
	//初始化栈
	Stack stack;
	StackInit(&stack);//初始化
	//走迷宫
	Postion cur, next;
	StackPush(&stack, post); //入栈   入栈过程中，cur为一个指针，使用的是ppost的空间，每次压栈时压的是同一个地址
	//需要每一次指向下一个
	//如何处理每次压栈是所使用的空间是同一块空间
	//改变压栈时的元素对象
	while (!(StackEmpty(&stack))) //栈不为空或没找到出口
	{
		//获取栈顶元素
		cur = StackTop(&stack);
		//标记
		pmaze->_map[cur.x][cur.y] = 2;  //要先把当前步标记，之后再判断走向那个方向
		//检测是否为出口，先探测，后压入元素
		if (Exit(pmaze, post, cur))
		{
			return 1;
		}
		
		//上
		next = cur;
		next.x = next.x - 1;
		if (MazeProbe(pmaze, next))
		{
			StackPush(&stack, next);
			continue;
		}
		//左
		next = cur;
		next.y = next.y - 1;
		if (MazeProbe(pmaze, next))
		{
			StackPush(&stack, next);
			continue;
		}
		//右
		next = cur;
		next.y = next.y + 1;
		if (MazeProbe(pmaze, next))
		{
			StackPush(&stack, next);
			continue;
		}
		//下
		next = cur;
		next.x = next.x + 1;
		if (MazeProbe(pmaze, next))
		{
			StackPush(&stack, next);
			continue;
		}
		//四面都走不通，然后退栈
		//循环走到这里，已经是都走不通了
		
		//标记
		pmaze->_map[cur.x][cur.y] = 3;
		//退栈
		StackPop(&stack);
	}
	//栈为空，走不通
	return 0;
}
//把旧栈变为新栈
void StackP(pStack pstackold, pStack pstacknew)  
{
	//直接把旧栈中的数组元素赋给新栈
	for (int i = 0; i < pstackold->Top; i++)
	{
		pstacknew->array[i] = pstackold->array[i];
	}
	pstacknew->Top = pstackold->Top;
}
//多通路地图
void MazeGo2(pMaze pmaze, Postion post, pStack pstackmin)
{
	//地图不为空
	assert(pmaze);
	//检测入口点是否合法
	if (!Entrance(pmaze, post))
	{
		return ;
	}
	//初始化栈
	Stack stack; //路径栈
	StackInit(&stack);
	//走迷宫
	Postion cur, next;
	StackPush(&stack, post); //入栈
	while (!(StackEmpty(&stack))) //栈不为空
	{
		//获取栈顶元素
		cur = StackTop(&stack);
		//标记
		pmaze->_map[cur.x][cur.y] = 2;  //要先把当前步标记，之后再判断走向那个方向
		//检测是否为出口
		if (Exit(pmaze, post, cur))
		{
			//判断是否为最短路径，若是，则更新最小栈
			if (StackEmpty(pstackmin) || StackSize(&stack) < StackSize(pstackmin))  //初始时如何把路径放入最小栈中
			{
				//更新之前需要最小栈为空
				StackP(&stack, pstackmin);  //把旧栈变为新栈
			}
			//stack以为空栈
			//把出口用0堵死
			pmaze->_map[cur.x][cur.y] = 0;
			//让出口入栈，开始回溯，重新开始找路径
			StackPop(&stack);
			//结束循环，继续寻找其他道路
			continue;
		}
		//探测下一步，先探测，后压入元素
		//上
		next = cur;
		next.x = next.x - 1;
		if (MazeProbe(pmaze, next))
		{
			StackPush(&stack, next);
			continue;
		}
		//左
		next = cur;
		next.y = next.y - 1;
		if (MazeProbe(pmaze, next))
		{
			StackPush(&stack, next);
			continue;
		}
		//右
		next = cur;
		next.y = next.y + 1;
		if (MazeProbe(pmaze, next))
		{
			StackPush(&stack, next);
			continue;
		}
		//下
		next = cur;
		next.x = next.x + 1;
		if (MazeProbe(pmaze, next))
		{
			StackPush(&stack, next);
			continue;
		}
		//四面都走不通，然后退栈
		//循环走到这里，已经是都走不通了

		//标记
		pmaze->_map[cur.x][cur.y] = 3;
		//退栈
		StackPop(&stack);
	}
}
//探测
int MazeProbe1(pMaze pmaze, Postion cur,Postion next)  //当前步 <= 下一步
{
	//位置合法next
	if ((0 <= next.x && next.x < X) && (0 <= next.y && Y > next.y))
	{
		if (pmaze->_map[cur.x][cur.y] < pmaze->_map[next.x][next.y] || pmaze->_map[next.x][next.y] == 1)
			return 1;
	}
	return 0;
}


//带环地图
//递归
void MazeGoShort(pMaze pmaze, Postion cur, Postion post, pStack pstack, pStack pstackmin)
{
	//检测是否为出口
	if (Exit(pmaze, post, cur))
	{
		StackPush(pstack, cur);
		//判断是否为最短路径，若是，则更新最小栈
		if (StackEmpty(pstackmin) || StackSize(pstack) < StackSize(pstackmin))  //初始时如何把路径放入最小栈中
		{
			StackP(pstack, pstackmin);  //把旧栈变为新栈
		}
		//让出口出栈，开始回溯，重新开始找路径
		StackPop(pstack);
		//结束循环，继续寻找其他道路
		return;
	}
	//若栈为空，则为第一次走
	if (StackEmpty(pstack))
	{
		pmaze->_map[cur.x][cur.y] = 2;  //赋初值,走入口
	}
	StackPush(pstack, cur); //入栈
	Postion next;

	//探测下一步，先探测，后压入元素
	//上
	next = cur;
	next.x = next.x - 1;
	if (MazeProbe1(pmaze, cur, next))
	{
		//标记
		pmaze->_map[next.x][next.y] = pmaze->_map[cur.x][cur.y] + 1;
		MazeGoShort(pmaze, next, post, pstack, pstackmin);
	}
	//左
	next = cur;
	next.y = next.y - 1;
	if (MazeProbe1(pmaze, cur, next))
	{
		//标记  下一步等于当前步+1
		pmaze->_map[next.x][next.y] = pmaze->_map[cur.x][cur.y] + 1;
		MazeGoShort(pmaze, next, post, pstack, pstackmin);
	}
	//右
	next = cur;
	next.y = next.y + 1;
	if (MazeProbe1(pmaze, cur, next))
	{
		//标记  下一步等于当前步+1
		pmaze->_map[next.x][next.y] = pmaze->_map[cur.x][cur.y] + 1;
		MazeGoShort(pmaze, next, post, pstack, pstackmin);
	}
	//下
	next = cur;
	next.x = next.x + 1;
	if (MazeProbe1(pmaze, cur, next))
	{
		//标记  下一步等于当前步+1
		pmaze->_map[next.x][next.y] = pmaze->_map[cur.x][cur.y] + 1;
		MazeGoShort(pmaze, next, post, pstack, pstackmin);
	}
	//四面都走不通，然后退栈
	//循环走到这里，已经是都走不通了
	//退栈
	StackPop(pstack);
}
void MazeGo3(pMaze pmaze, Postion post, pStack pstackmin)
{
	//地图不为空
	assert(pmaze);
	//初始化栈
	Stack stack; //路径栈
	StackInit(&stack);
	//检测入口点是否合法-函数
	if (!Entrance(pmaze, post))
	{
		return;
	}
	MazeGoShort(pmaze, post, post, &stack, pstackmin);
}
