#pragma once

#include <bitset>
#include "Utility/SingletonBase.h"

using std::bitset;

const int KEYMAX = 256;

class Input : public SingletonBase<Input>
{
private:
	//키코드에 해당하는 값을 인덱스로 하는 bit 단위 배열로 선언
	bitset<KEYMAX>	up;
	bitset<KEYMAX>	down;

public:
	Input();
	~Input() = default;

	bool KeyDown(int key);
	bool KeyUp(int key);
	bool KeyPress(int key);

	bool KeyToggle(int key);
};

//bitset
//std namespace, bit size 저장공간을 제공하는 array
//생성방법이 array랑 비슷 
//선언 : std::bitset<할당할 사이즈> 객체명;
//std::bitset<8> bitChar('a');
//여기서는 T/F 를 저장하는 배열의 용도
//해당 위치 값을 쓰는 함수는 
//set() -> 전체 1, set(index, value) ->해당 index 값을 value로
//reset() -> 전체 0, reset(index) ->해당 index 값을 0로
//flip() ->전체 값 반전, flip(index) -> 해당 위치 값 반전


