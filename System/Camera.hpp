#include "Win32Fortress.h"

template <typename P, typename R>
Camera<P, R>::Camera()
	: p_target(nullptr)
{
	p_camera_pos = new P;
	*p_camera_pos = { 0, 0 };

	type = CameraType::FREE;
}

template <typename P, typename R>
Camera<P, R>::Camera(const R& rcClient, const R& rcWorld)
	: rc_client(rcClient), rc_world(rcWorld), p_target(nullptr)
{
	p_camera_pos = new P;
	*p_camera_pos = { 0, 0 };

	type = CameraType::FREE;
}

template <typename P, typename R>
Camera<P, R>::~Camera()
{
	SAFE_DELETE(p_target);
	SAFE_DELETE(p_camera_pos);
}

template <typename P, typename R>
bool Camera<P, R>::Init(P* pt)
{
	if (pt != nullptr)
	{
		p_target = pt;
		type = CameraType::TARGET;
	}

	return true;
}

template <typename P, typename R>
void Camera<P, R>::Update()
{
	if (type == CameraType::TARGET)
	{
		p_camera_pos->x = (*p_target).x - rc_client.right / 2;
		p_camera_pos->y = (*p_target).y - rc_client.bottom / 2;
	}

	if (p_camera_pos->x < 0)
		p_camera_pos->x = 0;
	if (p_camera_pos->y < 0)
		p_camera_pos->y = 0;
	if (p_camera_pos->x > (rc_world.right - rc_client.right))
		p_camera_pos->x = (rc_world.right - rc_client.right);
	if (p_camera_pos->y > (rc_world.bottom - rc_client.bottom))
		p_camera_pos->y = (rc_world.bottom - rc_client.bottom);
		
}

template <typename P, typename R>
void Camera<P, R>::SetTarget(P* pt)
{ 
	assert(pt != nullptr);

	p_target = pt;
	type = CameraType::TARGET;
}
