//主要函数设置
#include "class.h"
#include "setting.h"

void Draw(Snake & snake, Wall & wall, Apple & apple, UI & ui)
{
	cleardevice();
	snake.Draw();
	wall.Draw();
	apple.Draw();
	ui.Draw_GameRunning(snake);
}

bool IsKeyDown(int key)
{//判断键盘是否按下
	return (GetAsyncKeyState(key) & 0x8000 ? 1 : 0);
}

void KeyboardControl(bool &isGameRunning,bool &isGameStarting,Snake & snake)
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
	if (IsKeyDown(VK_RETURN))
	{
		isGameStarting = false;
		isGameRunning = true;
	}
}

void Draw_start(UI & ui)
{
	ui.Draw_preparing();
}