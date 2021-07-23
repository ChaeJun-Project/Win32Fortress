#include "Win32Fortress.h"

Input::Input()
{
	up.reset();
	down.reset();
}

bool Input::KeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (!down[key])
		{
			down.set(key, true);
			return true;
		}
	}
	else
	{
		down.set(key, false);
	}

	return false;
}

bool Input::KeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		up.set(key, true);
	}
	else
	{
		if (up[key])
		{
			up.set(key, false);
			return true;
		}
	}

	return false;
}

bool Input::KeyPress(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
		return true;

	return false;
}

bool Input::KeyToggle(int key)
{
	if (GetKeyState(key) & 0x0001)
		return true;

	return false;
}



