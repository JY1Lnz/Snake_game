#include <graphics.h>
#include <Windows.h>
#include "setting.h"
#include "class.h"
//#include "function.cpp"

//全局变量beign
bool isGameRunning = true;
//全局变量end






//全局范围添加4个对象定义
Snake snake;
Wall wall;
Apple apple;
UI ui;
Parameter parameter;

bool IsKeyDown(int key)
{//判断键盘是否按下
	return (GetAsyncKeyState(key) & 0x8000 ? 1 : 0);
}

void KeyboardControl()
{
	if (IsKeyDown(VK_ESCAPE))
	{
		isGameRunning = false;
		return;
	}
	if (IsKeyDown(VK_LEFT))
	{
		snake.ChangeDirection(Direction::Left);
	}
	if (IsKeyDown(VK_RIGHT))
	{
		snake.ChangeDirection(Direction::Right);
	}
	if (IsKeyDown(VK_UP))
	{
		snake.ChangeDirection(Direction::Up);
	}
	if (IsKeyDown(VK_DOWN))
	{
		snake.ChangeDirection(Direction::Down);
	}
}

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

	while (isGameRunning)
	{
		KeyboardControl();
		HandleLogic();
		Draw(snake,wall,apple,ui);
		Sleep(30);
	}

	closegraph();
	return 0;
}