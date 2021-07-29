#pragma once

//WinMain ���ο��� Object�� �����ϴ� Game Class
//GameBase �ʿ��� ��� Ŭ������ ���� ����, GameMain �ʿ����� ���� ���� ó�� 
//GameBase�� �������̽� Ŭ����

//Ŭ���� ���漱��
class BackBuffer;

class GameBase
{
private:
	BackBuffer*		backBuffer;

	void SetBackBuffer();

public:
	GameBase();
	virtual ~GameBase() = 0;

	virtual bool Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc) = 0;

	BackBuffer* GetBackBuffer() { return backBuffer; }

	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);
};

