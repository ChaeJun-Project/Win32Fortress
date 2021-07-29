#pragma once

//카메라 렌더링 타입
enum class CameraType
{
	FREE,    //타겟이 따로 정해지지 않은 경우
	TARGET,  //타겟이 따로 정해져 따라다니는 경우
};

//카메라 클래스(싱글톤 사용, 템플릿 클래스)
template <typename P, typename R>
class Camera : public SingletonBase<Camera<P, R>>
{
private:
	P*				p_target; //타겟의 좌표
	P*				p_camera_pos; //카메라의 좌표

	R				rc_client; //윈도우 창의 크기
	R				rc_world;  //실제 게임 내의 월드 크기

	CameraType		type; //카메라 타입

public:
	Camera();
	explicit Camera(const R& rcClient, const R& rcWorld); //생성자 오버로딩
	~Camera();

	void Update();

	void SetTargetPos(P* pt);
	void SetCameraPos(P* pt);

	const P* GetTargetPos() const { if (p_target) return p_target; else return nullptr; }
	const P* GetCameraPos() const { if (p_camera_pos) return p_camera_pos; else return nullptr; }

	void SetClient(const R& rc) { rc_client = rc; }
	void SetWorld(const R& rc) { rc_world = rc; }

	const R& GetClient() const { return rc_client; }
	const R& GetWorld() const { return rc_world; }
};

//카메라 클래스의 템플릿 함수를 선언부와 정의부를 나누기 위해 hpp 사용
#include "Camera.hpp"