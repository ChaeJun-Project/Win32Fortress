#pragma once

/*Template
  함수나 클래스를 개별적으로 다시 작성하지 않아도, 여러 자료 형으로 사용할 수 있도록 하게 만들어 놓은 틀
*/

//해당 템플릿 클래스를 상속받아 싱글톤 클래스로 사용 가능
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

//템플릿 함수
template <typename T>
T* SingletonBase<T>::instance = nullptr;

//생성
template <typename T>
void SingletonBase<T>::Create()
{
	if (!instance)
		instance = new T;
}

//삭제
template <typename T>
void SingletonBase<T>::Delete()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

//싱글톤 클래스 객체 반환
template <typename T>
T* SingletonBase<T>::GetInstance()
{
	if (!instance)
		Create();

	return instance;
}