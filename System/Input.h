#pragma once

#include <bitset>
#include "Utility/SingletonBase.h"

using std::bitset;

const int KEYMAX = 256;

class Input : public SingletonBase<Input>
{
private:
	//Ű�ڵ忡 �ش��ϴ� ���� �ε����� �ϴ� bit ���� �迭�� ����
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
//std namespace, bit size ��������� �����ϴ� array
//��������� array�� ��� 
//���� : std::bitset<�Ҵ��� ������> ��ü��;
//std::bitset<8> bitChar('a');
//���⼭�� T/F �� �����ϴ� �迭�� �뵵
//�ش� ��ġ ���� ���� �Լ��� 
//set() -> ��ü 1, set(index, value) ->�ش� index ���� value��
//reset() -> ��ü 0, reset(index) ->�ش� index ���� 0��
//flip() ->��ü �� ����, flip(index) -> �ش� ��ġ �� ����


