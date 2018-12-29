#include <graphics.h>
#include <Windows.h>
#include "setting.h"
#include "class.h"



//全局变量beign
bool isGameRunning = false;
bool isGameStarting = true;
bool isGameChoosing = false;
//全局变量end

//全局范围添加4个对象定义
Snake snake;
Wall wall;
Apple apple;
UI ui;
Parameter parameter;




void HandleLogic()
{
	snake.Update();
	snake.TryEat(apple);
}

int main()
{
	
	initgraph(parameter.window_width,parameter.window_high);
	setbkcolor(WHITE);
	setlinecolor(BLACK);
	settextcolor(BLACK);
	cleardevice();

	while (isGameStarting)
	{
		KeyboardControl(isGameRunning, isGameStarting, isGameChoosing, snake);
		Draw_start(ui);
		Sleep(30);
	}

	while (isGameChoosing)
	{
		KeyboardControl(isGameRunning, isGameStarting, isGameChoosing, snake);
		Draw_choice(ui);
		Sleep(30);
	}

	while (isGameRunning)
	{
		KeyboardControl(isGameRunning,isGameStarting, isGameChoosing, snake);
		HandleLogic();
		Draw(snake,wall,apple,ui);
		Sleep(30);
	}

	closegraph();
	return 0;
}