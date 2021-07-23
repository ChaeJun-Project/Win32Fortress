#pragma once
//WinMain 내부에서 Object로 동작하는 Game Class
//GameBase 쪽에서 기반 클래스를 생성 해제, GameMain 쪽에서는 게임 로직 처리 
//GameBase는 인터페이스 클래스

//클래스 전방선언
class BackBuffer;

class GameBase
{
private:
	BackBuffer*		backBuffer;

	void SetBackBuffer();

public:
	GameBase() ;
	virtual ~GameBase();

	virtual bool Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	BackBuffer* GetBackBuffer() { return backBuffer; }

	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);
};

