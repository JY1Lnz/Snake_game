#include <graphics.h>
#include <Windows.h>

#include "class.h"

//ȫ�ֱ���beign
bool isGameRunning = true;
//ȫ�ֱ���end


//ȫ�ַ�Χ���4��������
Snake snake;
Wall wall;
Apple apple;
UI ui;


bool IsKeyDown(int key)
{//�жϼ����Ƿ���
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