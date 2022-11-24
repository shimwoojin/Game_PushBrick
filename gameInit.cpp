#include "stdafx.h"
#include "gameInit.h"

void drawMap(HDC& hdc, int horizen, int vertical)
{
	int roomSize = WINSIZE_X / (vertical - 1);

	//수평선
	for (int i = 0; i < horizen; i++)
	{
		MoveToEx(hdc, 0, i * roomSize, NULL);
		LineTo(hdc, WINSIZE_X, i * roomSize);
	}

	//수직선
	for (int i = 0; i < vertical; i++)
	{
		MoveToEx(hdc, i * roomSize, 0, NULL);
		LineTo(hdc, i * roomSize, WINSIZE_Y);
	}

	return;
}

void fillMapRectangle(HDC& hdc, const int map[HORIZEN - 1][VERTICAL - 1])
{
	const int space = 2;
	for (int i = 0; i < HORIZEN - 1; i++)
	{
		for (int j = 0; j < VERTICAL - 1; j++)
		{
			int left = j * MOVINGINTERVAL + space;
			int top = i * MOVINGINTERVAL + space;
			int right = left + MOVINGINTERVAL - 2 * space;
			int bottom = top + MOVINGINTERVAL - 2 * space;
			if (map[i][j] == 1)
			{
				Rectangle(hdc, left, top, right, bottom);
			}
		}
	}
}

void moveCharacter(WPARAM& wParam, POINT& position, MOVE_DIR& dir)
{
	int mapIndexX = (position.x - MOVINGINTERVAL / 2) / MOVINGINTERVAL;
	int mapIndexY = (position.y - MOVINGINTERVAL / 2) / MOVINGINTERVAL;
	switch (wParam)
	{
	case 'A': case 'a':	case VK_LEFT:
	{
		if (position.x > RECT_SIZE / 2 && map[mapIndexY][mapIndexX - 1] == 0)
		{
			position.x -= MOVINGINTERVAL;
			dir = MOVE_DIR::LEFT;
		}
	}
	break;

	case 'D': case 'd':	case VK_RIGHT:
	{
		if (position.x < WINSIZE_X - (RECT_SIZE / 2) && map[mapIndexY][mapIndexX + 1] == 0)
		{
			position.x += MOVINGINTERVAL;
			dir = MOVE_DIR::RIGHT;
		}
	}
	break;

	case 'W': case 'w':	case VK_UP:
	{
		if (position.y > RECT_SIZE / 2 && map[mapIndexY - 1][mapIndexX] == 0)
		{
			position.y -= MOVINGINTERVAL;
			dir = MOVE_DIR::UP;
		}
	}
	break;

	case 'S': case 's':	case VK_DOWN:
	{
		if (position.y < WINSIZE_Y - (RECT_SIZE / 2) && map[mapIndexY +	1][mapIndexX] == 0)
		{
			position.y += MOVINGINTERVAL;
			dir = MOVE_DIR::DOWN;
		}
	}
	break;

	default:
		break;
	}
}

RECT makeBrick(int left, int top)
{
	RECT rt;
	left *= MOVINGINTERVAL;
	left += (MOVINGINTERVAL - BRICK_SIZE) / 2;
	top *= MOVINGINTERVAL;
	top += (MOVINGINTERVAL - BRICK_SIZE) / 2;
	rt.left = left;
	rt.right = rt.left + BRICK_SIZE;
	rt.top = top;
	rt.bottom = top + BRICK_SIZE;
	return rt;
}

RECT makeGoalPoint(int left, int top)
{
	RECT rt;
	const int goalPointInterval = 2;
	left *= MOVINGINTERVAL;
	left += (MOVINGINTERVAL - BRICK_SIZE) / 2 - goalPointInterval;
	top *= MOVINGINTERVAL;
	top += (MOVINGINTERVAL - BRICK_SIZE) / 2 - goalPointInterval;
	rt.left = left;
	rt.right = rt.left + BRICK_SIZE + 2 * goalPointInterval;
	rt.top = top;
	rt.bottom = top + BRICK_SIZE + 2 * goalPointInterval;
	return rt;
}

void pushBrick(RECT& brick, MOVE_DIR dir)
{
	switch (dir)
	{
	case MOVE_DIR::UP:
		if (brick.top - (RECT_SIZE - BRICK_SIZE) / 2 > 0)
		{
			brick.top -= MOVINGINTERVAL;
			brick.bottom -= MOVINGINTERVAL;
		}
		break;
	case MOVE_DIR::DOWN:
		if (brick.bottom + (RECT_SIZE - BRICK_SIZE) / 2 < WINSIZE_Y)
		{
			brick.top += MOVINGINTERVAL;
			brick.bottom += MOVINGINTERVAL;
		}
		break;
	case MOVE_DIR::LEFT:
		if (brick.left - (RECT_SIZE - BRICK_SIZE) / 2 > 0)
		{
			brick.left -= MOVINGINTERVAL;
			brick.right -= MOVINGINTERVAL;
		}
		break;
	case MOVE_DIR::RIGHT:
		if (brick.right + (RECT_SIZE - BRICK_SIZE) / 2 < WINSIZE_X)
		{
			brick.left += MOVINGINTERVAL;
			brick.right += MOVINGINTERVAL;
		}
		break;
	default:
		break;
	}
}
