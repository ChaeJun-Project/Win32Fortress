#pragma once

//Template
template <typename T>
class SingletonBase
{
protected:
	static T* instance;

	SingletonBase() = default;
	~SingletonBase() = default;

	//복사생성자 금지
	SingletonBase(const SingletonBase& obj) = delete;
	//대입연산자 금지
	SingletonBase& operator=(const SingletonBase& obj) = delete;

public:
	static void Create();
	static void Delete();
	static T* GetInstance();
};

template <typename T>
T* SingletonBase<T>::instance = nullptr;

template <typename T>
void SingletonBase<T>::Create()
{
	if (!instance)
		instance = new T;
}

template <typename T>
void SingletonBase<T>::Delete()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

template <typename T>
T* SingletonBase<T>::GetInstance()
{
	if (!instance)
		Create();

	return instance;
}