#pragma once

//게임 최대 플레이어 가능 수
#define MAX_PLAYER_COUNT 2

//Key Macro
#define KEYDOWN(key)	 Input::GetInstance()->KeyDown(key)
#define KEYUP(key)		 Input::GetInstance()->KeyUp(key)
#define KEYPRESS(key)	 Input::GetInstance()->KeyPress(key)
#define KEYTOGGLE(key)	 Input::GetInstance()->KeyToggle(key)

#define SAFE_DELETE(p) {if(p) {delete (p); (p) = nullptr; }}

// 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
#define WIN32_LEAN_AND_MEAN       

// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <assert.h>
#include <tchar.h>
#include <time.h>

// C++ 표준 라이브러리
#include <string>
#include <vector>
#include <list>
#include <map>

//Utility
#include "Utility/CommonFunction.h"
#include "Utility/SingletonBase.h"

//System
#include "System/BackBuffer.h"
#include "System/Collision.h"
#include "System/Input.h"
#include "System/Timer.h"
#include "System/Camera.h"

//Scene
#include "Scene/BackGround.h"
#include "Scene/Bullet.h"
#include "Scene/HpBar.h"
#include "Scene/ObjectBase.h"
#include "Scene/Player.h"

//Resource
#include "Resource/Animation.h"
#include "Resource/Image.h"

//Manager
#include "Manager/AnimationManager.h"
#include "Manager/ImageManager.h"
#include "Manager/ObjectManager.h"
#include "Manager/TimeManager.h"

//Core
#include "Core/GameBase.h"
#include "Core/GameMain.h"


//Extern Object
extern HWND			g_hWnd;
extern HINSTANCE	g_hInstance;
extern POINT		g_ptMouse;

//Constants
const  float		EP = 0.00001f;
const  float        PI = 3.141592f;

//카메라 클라이언트 크기(윈도우 창의 크기)
const  int			GAME_START_X = 50;
const  int			GAME_START_Y = 50;
const  int			GAME_WIDTH = 1300;
const  int			GAME_HEIGHT = 700;

//실제 게임 월드의 크기
const  int          WORLD_WIDTH = 1920;
const  int          WORLD_HEIGHT = 1080;

