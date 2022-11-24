#pragma once
enum class MOVE_DIR { UP, DOWN, LEFT, RIGHT };

void drawMap(HDC& hdc, int vertical, int horizen);

void moveCharacter(WPARAM& wParam, POINT& position, MOVE_DIR& dir);

RECT makeBrick(int left, int top);

void pushBrick(RECT& brick, MOVE_DIR dir);