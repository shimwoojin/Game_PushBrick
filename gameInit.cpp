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

void moveCharacter(WPARAM& wParam, POINT& position, MOVE_DIR& dir)
{

	switch (wParam)
	{
	case 'A': case 'a':	case VK_LEFT:
	{
		position.x -= MOVINGINTERVAL;
		dir = MOVE_DIR::LEFT;
	}
	break;

	case 'D': case 'd':	case VK_RIGHT:
	{
		position.x += MOVINGINTERVAL;
		dir = MOVE_DIR::RIGHT;
	}
	break;

	case 'W': case 'w':	case VK_UP:
	{
		position.y -= MOVINGINTERVAL;
		dir = MOVE_DIR::UP;
	}
	break;

	case 'S': case 's':	case VK_DOWN:
	{
		position.y += MOVINGINTERVAL;
		dir = MOVE_DIR::DOWN;
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
	left += (MOVINGINTERVAL - RECT_REALSIZE) / 2;
	top *= MOVINGINTERVAL;
	top += (MOVINGINTERVAL - RECT_REALSIZE) / 2;
	rt.left = left;
	rt.right = rt.left + 30;
	rt.top = top;
	rt.bottom = top + 30;
	return rt;
}

void pushBrick(RECT& brick, MOVE_DIR dir)
{
	switch (dir)
	{
	case MOVE_DIR::UP:
		brick.top -= MOVINGINTERVAL;
		brick.bottom -= MOVINGINTERVAL;
		break;
	case MOVE_DIR::DOWN:
		brick.top += MOVINGINTERVAL;
		brick.bottom += MOVINGINTERVAL;
		break;
	case MOVE_DIR::LEFT:
		brick.left -= MOVINGINTERVAL;
		brick.right -= MOVINGINTERVAL;
		break;
	case MOVE_DIR::RIGHT:
		brick.left += MOVINGINTERVAL;
		brick.right += MOVINGINTERVAL;
		break;
	default:
		break;
	}
}
