#pragma once
#include <stdio.h>
#include <time.h>  //随机函数
#include <stdlib.h> //结合 time.h
#include <graphics.h>
#include <mmsystem.h>
#include <conio.h>
#pragma comment(lib, "winmm.lib")

#define WINDOW_WIDTH  640
#define WINDOW_HEIGHT 480
#define MAXNUM        100  //蛇的最大节数
#define SNAKESIZE     10   //蛇大小


//用一个什么样的数据去表示一个"🐍"
//用自定义结构体类型：当前有多少节，蛇的方向，蛇的坐标

//方向
typedef enum Ch
{
	up = 72,
	down = 80,
	left = 75,
	right = 77
} CH;

//坐标
typedef struct Coor
{
	int x;
	int y;
} COOR;

typedef struct Snake
{
	COOR sCor[MAXNUM]; //蛇的坐标(包含100节）
	int n; //当前节数
	CH ch; //蛇的方向
}SNAKE;

//蛇的食物
typedef struct Food
{
	Coor fCor;
	int isEat;
}FOOD;

SNAKE snake; //蛇的定义
FOOD food;





//游戏的初始化
void GameInit();

//让蛇移动
void SnakeMove();

//蛇的绘制
void SnakeDraw();

void SnakeChange();

void FoodDraw();

void FoodCoor();

void FoodEat();

void SnakeBreak();