#include "Win32Fortress.h"

template <typename P, typename R>
Camera<P, R>::Camera()
	: p_target(nullptr)
{
	p_camera_pos = new P; //카메라 위치 동적 할당
	*p_camera_pos = { 0, 0 }; // (0, 0)으로 초기화

	type = CameraType::FREE;
}

template <typename P, typename R>
Camera<P, R>::Camera(const R& rcClient, const R& rcWorld)
	: rc_client(rcClient), rc_world(rcWorld), p_target(nullptr)
{
	p_camera_pos = new P; //카메라 위치 동적 할당
	*p_camera_pos = { 0, 0 }; // (0, 0)으로 초기화

	type = CameraType::FREE;
}

template <typename P, typename R>
Camera<P, R>::~Camera()
{
	SAFE_DELETE(p_target);
	SAFE_DELETE(p_camera_pos);
}

//카메라 타겟의 좌표 설정
template <typename P, typename R>
void Camera<P, R>::SetTargetPos(P* pt)
{
	if (pt != nullptr)
	{
		p_target = pt;
		type = CameraType::TARGET; //타겟의 좌표가 정해졌으므로 타켓모드로 변경
	}

	else
		type = CameraType::FREE; //타겟의 좌표가 없으므로 자유모드로 변경
}

//카메라 좌표 설정
template <typename P, typename R>
void Camera<P, R>::SetCameraPos(P* pt)
{
	if (pt != nullptr)
		p_camera_pos = pt;

}

template <typename P, typename R>
void Camera<P, R>::Update()
{
	//현재 카메라 상태가 타겟을 따라다니는 타겟모드일 경우
	if (type == CameraType::TARGET)
	{
		//카메라의 중심에 타겟이 나오도록 카메라의 좌표값 변경
		p_camera_pos->x = (*p_target).x - rc_client.right / 2;
		p_camera_pos->y = (*p_target).y - rc_client.bottom / 2;
	}

	//카메라의 x좌표가 음수가 되는 경우
	if (p_camera_pos->x < 0)
		p_camera_pos->x = 0; //x좌표값 0으로 초기화

	//카메라의 y좌표가 음수가 되는 경우
	if (p_camera_pos->y < 0)
		p_camera_pos->y = 0; //y좌표값 0으로 초기화

	//카메라가 월드 밖을 나가지 않도록 x범위를 제한
	if (p_camera_pos->x > (rc_world.right - rc_client.right))
		p_camera_pos->x = (rc_world.right - rc_client.right);

	//카메라가 월드 밖을 나가지 않도록 y범위를 제한
	if (p_camera_pos->y > (rc_world.bottom - rc_client.bottom))
		p_camera_pos->y = (rc_world.bottom - rc_client.bottom);
}
