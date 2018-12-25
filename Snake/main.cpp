#include <graphics.h>
#include <Windows.h>
#include "setting.h"
#include "class.h"
//#include "function.cpp"

//ȫ�ֱ���beign
bool isGameRunning = true;
//ȫ�ֱ���end






//ȫ�ַ�Χ���4��������
Snake snake;
Wall wall;
Apple apple;
UI ui;
Parameter parameter;

bool IsKeyDown(int key)
{//�жϼ����Ƿ���
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