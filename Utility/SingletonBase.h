#pragma once

/*Template
  �Լ��� Ŭ������ ���������� �ٽ� �ۼ����� �ʾƵ�, ���� �ڷ� ������ ����� �� �ֵ��� �ϰ� ����� ���� Ʋ
*/

//�ش� ���ø� Ŭ������ ��ӹ޾� �̱��� Ŭ������ ��� ����
template <typename T>
class SingletonBase
{
protected:
	static T* instance;

	SingletonBase() = default;
	~SingletonBase() = default;

	//��������� ����
	SingletonBase(const SingletonBase& obj) = delete;
	//���Կ����� ����
	SingletonBase& operator=(const SingletonBase& obj) = delete;

public:
	static void Create();
	static void Delete();
	static T* GetInstance();
};

//���ø� �Լ�
template <typename T>
T* SingletonBase<T>::instance = nullptr;

//����
template <typename T>
void SingletonBase<T>::Create()
{
	if (!instance)
		instance = new T;
}

//����
template <typename T>
void SingletonBase<T>::Delete()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

//�̱��� Ŭ���� ��ü ��ȯ
template <typename T>
T* SingletonBase<T>::GetInstance()
{
	if (!instance)
		Create();

	return instance;
}