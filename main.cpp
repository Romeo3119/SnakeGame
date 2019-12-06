/*******************************
	文件名称：main.cpp
	文件描述：C语言+图形界面库实现智能版【贪吃蛇】
	编译环境：VC++6.0/VS2008/VS2010/VS2013/VS2015+图形界面库
	最后修改：<2019/12/6> <创建工程> <Romeo>
********************************/


#include "game.h"
#include "resource1.h"
int main()
{
	GameInit();

	while (1)
	{
		while (!_kbhit())
		{

			cleardevice();
			//食物被吃掉后
			if (food.isEat == 0)
			{
				FoodCoor();
			}
			FoodDraw();
			SnakeMove();
			FoodEat(); 
			SnakeBreak(); 
			Sleep(100);
		}
		SnakeChange();
	}
	//cleardevice();//用设置好的颜色去刷新屏幕

	
	//mciSendString(L"play bkmusic repeat", 0, 0, 0);
	//设置字体，一般只需要设置高，宽为0，代表默认的，自适应
	//settextstyle(50, 0, L"微软雅黑");
	//settextcolor(RED);
	//outtextxy(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, L"Romeo");
	getchar();
	closegraph();  //关闭窗口
	return 0;
}

//游戏的初始化
void GameInit()
{

	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
	srand((unsigned int)time(NULL)); 
	//播放mp3格式的函数
	//mciSendString(L"open ./res/甩葱歌.mp3 alias bkmusic", 0, 0, 0);
	//mciSendString(L"play bkmusic repeat", 0, 0, 0);

	PlaySound(LPWSTR(IDR_WAVE1), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC | SND_LOOP);
	//初始化一条小蛇
	rectangle(0, 0,SNAKESIZE,SNAKESIZE);
	//蛇的方向
	snake.ch = down;
	snake.n = 3; //当前节数

	snake.sCor[0].x = 0;  //第三节
	snake.sCor[0].y = 20;

	snake.sCor[1].x = 0;  //第二节
	snake.sCor[1].y = 10;

	snake.sCor[2].x = 0; //第一节
	snake.sCor[2].y = 0;

	food.isEat = 0; //被吃掉的（因为被吃掉才能出现新的）


}


//让蛇移动
void SnakeMove()
{

	//不断交换相邻节的坐标
	for (int i = snake.n -1; i > 0; --i)
	{
		snake.sCor[i].x = snake.sCor[i - 1].x;
		snake.sCor[i].y = snake.sCor[i - 1].y;
	}
	switch (snake.ch)
	{
	case up:
		snake.sCor[0].y -= SNAKESIZE;
		break;
	case down:
		snake.sCor[0].y += SNAKESIZE;
		break;
	case left:
		snake.sCor[0].x -= SNAKESIZE;
		break;
	case right:
		snake.sCor[0].x += SNAKESIZE;
		break;
	}

	SnakeDraw();
}


//蛇的绘制:蛇有n节
void SnakeDraw()
{
	for (int i = 0; i < snake.n; ++i)
	{
		rectangle(snake.sCor[i].x,
			snake.sCor[i].y,
			snake.sCor[i].x + SNAKESIZE,
			snake.sCor[i].y + SNAKESIZE);
	}
}

void SnakeChange()
{
	char move; 

	move = getch(); // getchar()/getch();

	switch (move)
	{
	case up:
		if (snake.ch != down)
			snake.ch = up;
		break;

	case down:
		if (snake.ch != up)
			snake.ch = down;
		break;

	case left:
		if (snake.ch != right)
			snake.ch = left;
		break;

	case right:
		if (snake.ch != left)
			snake.ch = right;
		break;
	}
}

void FoodDraw()
{
	//圆角矩形
	roundrect(food.fCor.x, food.fCor.y,
		food.fCor.x + SNAKESIZE,
 		food.fCor.y + SNAKESIZE, 10, 10);

}

//获取得到食物的坐标
void FoodCoor()
{
	//
	food.fCor.x = rand()% (WINDOW_WIDTH/SNAKESIZE)*SNAKESIZE;
	food.fCor.y = rand()% (WINDOW_HEIGHT/SNAKESIZE)*SNAKESIZE;

	food.isEat = 1; //没被吃掉
}


void FoodEat()
{
	if (snake.sCor[0].x == food.fCor.x
		&& snake.sCor[0].y == food.fCor.y)
	{
		snake.n++;
		food.isEat = 0;
	}
}

//撞墙 snake.sCor[0].x snake.sCor[0].y
//还有可能撞到自己,用for去遍历数组，判定蛇头的坐标
//有没有跟蛇身体上任意一节坐标重合
void SnakeBreak()
{
	//撞墙 snake.sCor[0].x snake.sCor[0].y
	if (snake.sCor[0].x < 0 ||
		snake.sCor[0].x > 630 ||
		snake.sCor[0].y < 0 ||
		snake.sCor[0].y > 470)
	{
		Sleep(1000);
		closegraph();  //关闭窗口

		exit(0);
	}


	//撞到自己
	for (int i = snake.n - 1; i > 0; i--)
	{
		if (snake.sCor[0].x == snake.sCor[i].x
			&& snake.sCor[0].y == snake.sCor[i].y)
		{
			Sleep(1000);
			closegraph();  //关闭窗口
			
			exit(0);
			
		}
	}
}