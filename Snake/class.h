#pragma once
#include <graphics.h>
#include <list>
#include <sstream>
#include <iostream>
#include <time.h>
#include <math.h>
#include "stdlib.h"



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
	Apple()
	{
		NewApple();
	}
	void Draw()
	{
		circle(_x * 48 + 160 + 24, _y * 48 + 24, 15);
	}
	void NewApple()
	{
		srand((unsigned)time(NULL));
		_x = rand() % 10;
		_y = rand() % 10;
	}
	int GetX()
	{
		return _x;
	}
	int GetY()
	{
		return _y;
	}
private:
	int _x;
	int _y;
};

enum Direction
{
	Up,
	Down,
	Left,
	Right,
};


class Snake
{
public:

	Snake()
	{
		POINT head = { 1,1 };
		_bodyList.push_back(head);
		_dir = Direction::Right;

		POINT p1 = { 1,2 };
		POINT p2 = { 1,3 };
		POINT p3 = { 2,3 };
		_bodyList.push_back(p1);
		_bodyList.push_back(p2);
		_bodyList.push_back(p3);
		_length = 4;
	}

	std::string getLength()
	{
		std::ostringstream os;
		os << _length;
		return os.str();
	}

	void ChangeDirection(Direction dir)
	{
		if (_dir == Direction::Up && dir == Direction::Down
			|| _dir == Direction::Down && dir == Direction::Up
			|| _dir == Direction::Right && dir == Direction::Left
			|| _dir == Direction::Left && dir == Direction::Right)
		{
			return;
		}

		_dir = dir;
	}
	void Update()
	{
		int x0ffset[4] = { 0,0,-1,1 };
		int y0ffset[4] = { -1,1,0,0 };

		static int lastMoveTick = 0;
		int curTick = GetTickCount();//记录当前时间

		if (curTick - lastMoveTick < _difficulty)//控制蛇的移动速度
		{
			return;
		}

		lastMoveTick = curTick;

		std::list<POINT>::iterator it = _bodyList.begin();

		int prevX = it->x;
		int prevY = it->y;
		it->x += x0ffset[_dir];
		it->y += y0ffset[_dir];

		it++;

		for (; it != _bodyList.end(); it++)
		{
			int curX = it->x;
			int curY = it->y;

			it->x = prevX;
			it->y = prevY;

			prevX = curX;
			prevY = curY;
		}
	}

	void TryEat(Apple & apple)
	{
		POINT headPos = *_bodyList.begin();

		if (headPos.x != apple.GetX() || headPos.y != apple.GetY())
		{
			return;
		}
		apple.NewApple();
		_length++;

		POINT end = _bodyList.back();
		_bodyList.push_back(end);
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

	void GetDifficulty(int difficulty)
	{
		_difficulty = difficulty;
	}

private:
	std::list<POINT> _bodyList;
	int _dir;
	int _length;
	int _difficulty = 500;
};

class UI
{
public:
	void Draw_GameRunning(Snake & snake)
	{

		RECT scoreRect = { 10,10,140,50 };
		drawtext("长度", &scoreRect, DT_CENTER);

		RECT levelRect = { 10,240,140,290 };
		drawtext("难度", &levelRect, DT_CENTER);

		char sLength[10];
		std::string s = snake.getLength();
		int sLen = s.length();
		for (int i = 0; i < sLen; i++)
			sLength[i] = s[i];
		sLength[sLen] = 0;
		RECT snakeLength = { 10,40,140,100 };
		drawtext(sLength, &snakeLength, DT_CENTER);

	}
	void Draw_preparing()
	{
		RECT helloRect = { 0,0,640,480 };
		drawtext("欢迎游玩贪吃蛇", &helloRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		RECT startRect = { 480,320,640,480 };
		drawtext("按下任意键继续......", &startRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	
	void Drwa_Choosing()
	{
		RECT choiceRect = { 0,0,640,240 };
		drawtext("请选择难度", &choiceRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
};


void Draw(Snake & snake, Wall & wall, Apple & apple, UI & ui);
void Draw_start(UI & ui);
void Draw_choice(UI & ui);

bool IsKeyDown(int key);

void KeyboardControl(bool &isGameRunning,bool &isGameStarting,bool &isGameChoosing,Snake & snake);