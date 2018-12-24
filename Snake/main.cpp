#include <graphics.h>
#include <Windows.h>

#include "class.h"

//全局变量beign
bool isGameRunning = true;
//全局变量end


//全局范围添加4个对象定义
Snake snake;
Wall wall;
Apple apple;
UI ui;


bool IsKeyDown(int key)
{//判断键盘是否按下
	return (GetAsyncKeyState(key) & 0x8000 ? 1 : 0);
}

void Draw()
{
	cleardevice();
	snake.Draw();
	wall.Draw();
	apple.Draw();
	ui.Draw();
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
	initgraph(640,480);
	setbkcolor(WHITE);
	setlinecolor(BLACK);
	settextcolor(BLACK);
	cleardevice();

	while (isGameRunning)
	{
		KeyboardControl();
		HandleLogic();
		Draw();
		Sleep(30);
	}

	closegraph();
	return 0;
}