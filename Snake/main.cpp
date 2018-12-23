#include <graphics.h>
#include <Windows.h>
#include <list>

//全局变量beign
bool isGameRunning = true;
//全局变量end

class Wall
{
public:
	void Draw()
	{
		line(160, 0, 160, 480);
	}
};

class Apple
{
public:
	void Draw()
	{

	}
private:
	int _x;
	int _y;
};

class Snake
{
public:
	Snake()
	{
		POINT head = { 1,1 };
		_bodyList.push_back(head);

		POINT p1 = { 1,2 };
		POINT p2 = { 1,3 };
		POINT p3 = { 2,3 };
		_bodyList.push_back(p1);
		_bodyList.push_back(p2);
		_bodyList.push_back(p3);
	}
	void Draw()
	{
		for (std::list<POINT>::iterator it = _bodyList.begin(); it != _bodyList.end(); it++)
		{
			POINT pos = *it;
			//蛇的每个结点都画一个正方形,长宽 48
			rectangle(pos.x * 48 + 160, pos.y * 48, (pos.x + 1) * 48 + 160, (pos.y + 1) * 48);
			if (it == _bodyList.begin())
			{
				rectangle(pos.x * 48 + 160 + 6, pos.y * 48, (pos.x + 0.25) * 48 + 160 + 6, (pos.y + 0.25) * 48);
				rectangle(pos.x * 48 + 160 + 30, pos.y * 48, (pos.x + 0.25) * 48 + 160 + 30, (pos.y + 0.25) * 48);
			}
		}
	}
private:
	std::list<POINT> _bodyList;
};

class UI
{
public:
	void Draw()
	{
		RECT scoreRect = { 10,10,140,50 };
		drawtext("分数", &scoreRect, DT_CENTER);

		RECT levelRect = { 10,240,140,290 };
		drawtext("难度", &levelRect, DT_CENTER);
	}
};

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
}

void HandleLogic()
{

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