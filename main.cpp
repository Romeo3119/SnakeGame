/*******************************
	�ļ����ƣ�main.cpp
	�ļ�������C����+ͼ�ν����ʵ�����ܰ桾̰���ߡ�
	���뻷����VC++6.0/VS2008/VS2010/VS2013/VS2015+ͼ�ν����
	����޸ģ�<2019/12/6> <��������> <Romeo>
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
			//ʳ�ﱻ�Ե���
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
	//cleardevice();//�����úõ���ɫȥˢ����Ļ

	
	//mciSendString(L"play bkmusic repeat", 0, 0, 0);
	//�������壬һ��ֻ��Ҫ���øߣ���Ϊ0������Ĭ�ϵģ�����Ӧ
	//settextstyle(50, 0, L"΢���ź�");
	//settextcolor(RED);
	//outtextxy(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, L"Romeo");
	getchar();
	closegraph();  //�رմ���
	return 0;
}

//��Ϸ�ĳ�ʼ��
void GameInit()
{

	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
	srand((unsigned int)time(NULL)); 
	//����mp3��ʽ�ĺ���
	//mciSendString(L"open ./res/˦�и�.mp3 alias bkmusic", 0, 0, 0);
	//mciSendString(L"play bkmusic repeat", 0, 0, 0);

	PlaySound(LPWSTR(IDR_WAVE1), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC | SND_LOOP);
	//��ʼ��һ��С��
	rectangle(0, 0,SNAKESIZE,SNAKESIZE);
	//�ߵķ���
	snake.ch = down;
	snake.n = 3; //��ǰ����

	snake.sCor[0].x = 0;  //������
	snake.sCor[0].y = 20;

	snake.sCor[1].x = 0;  //�ڶ���
	snake.sCor[1].y = 10;

	snake.sCor[2].x = 0; //��һ��
	snake.sCor[2].y = 0;

	food.isEat = 0; //���Ե��ģ���Ϊ���Ե����ܳ����µģ�


}


//�����ƶ�
void SnakeMove()
{

	//���Ͻ������ڽڵ�����
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


//�ߵĻ���:����n��
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
	//Բ�Ǿ���
	roundrect(food.fCor.x, food.fCor.y,
		food.fCor.x + SNAKESIZE,
 		food.fCor.y + SNAKESIZE, 10, 10);

}

//��ȡ�õ�ʳ�������
void FoodCoor()
{
	//
	food.fCor.x = rand()% (WINDOW_WIDTH/SNAKESIZE)*SNAKESIZE;
	food.fCor.y = rand()% (WINDOW_HEIGHT/SNAKESIZE)*SNAKESIZE;

	food.isEat = 1; //û���Ե�
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

//ײǽ snake.sCor[0].x snake.sCor[0].y
//���п���ײ���Լ�,��forȥ�������飬�ж���ͷ������
//��û�и�������������һ�������غ�
void SnakeBreak()
{
	//ײǽ snake.sCor[0].x snake.sCor[0].y
	if (snake.sCor[0].x < 0 ||
		snake.sCor[0].x > 630 ||
		snake.sCor[0].y < 0 ||
		snake.sCor[0].y > 470)
	{
		Sleep(1000);
		closegraph();  //�رմ���

		exit(0);
	}


	//ײ���Լ�
	for (int i = snake.n - 1; i > 0; i--)
	{
		if (snake.sCor[0].x == snake.sCor[i].x
			&& snake.sCor[0].y == snake.sCor[i].y)
		{
			Sleep(1000);
			closegraph();  //�رմ���
			
			exit(0);
			
		}
	}
}