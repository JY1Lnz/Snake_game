//主要函数设置
#include "class.h"
#include "setting.h"

void Draw(Snake & snake, Wall & wall, Apple & apple, UI & ui)
{
	cleardevice();
	snake.Draw();
	wall.Draw();
	apple.Draw();
	ui.Draw();
}