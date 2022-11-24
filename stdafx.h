// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#define PROGRAM_TITLE L"PUSHBRICK_MADEBY_WOOJIN"

#define WINSIZE_X 1280	//사각형 크기 40 -> 32
#define WINSIZE_Y 720	// 18

#define RECT_SIZE 40
#define BRICK_SIZE 30
#define HORIZEN 19
#define VERTICAL 33
#define MOVINGINTERVAL (WINSIZE_X / (VERTICAL - 1))

#define RECT_MAKE(x,y,s) {x - s / 2, y - s / 2, x + s / 2, y + s / 2}
#define RECT_DRAW(rt) Rectangle(hdc, rt.left, rt.top, rt.right, rt.bottom)


#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include "gameInit.h"
