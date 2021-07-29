#include "Win32Fortress.h"

template <typename P, typename R>
Camera<P, R>::Camera()
	: p_target(nullptr)
{
	p_camera_pos = new P; //ī�޶� ��ġ ���� �Ҵ�
	*p_camera_pos = { 0, 0 }; // (0, 0)���� �ʱ�ȭ

	type = CameraType::FREE;
}

template <typename P, typename R>
Camera<P, R>::Camera(const R& rcClient, const R& rcWorld)
	: rc_client(rcClient), rc_world(rcWorld), p_target(nullptr)
{
	p_camera_pos = new P; //ī�޶� ��ġ ���� �Ҵ�
	*p_camera_pos = { 0, 0 }; // (0, 0)���� �ʱ�ȭ

	type = CameraType::FREE;
}

template <typename P, typename R>
Camera<P, R>::~Camera()
{
	SAFE_DELETE(p_target);
	SAFE_DELETE(p_camera_pos);
}

//ī�޶� Ÿ���� ��ǥ ����
template <typename P, typename R>
void Camera<P, R>::SetTargetPos(P* pt)
{
	if (pt != nullptr)
	{
		p_target = pt;
		type = CameraType::TARGET; //Ÿ���� ��ǥ�� ���������Ƿ� Ÿ�ϸ��� ����
	}

	else
		type = CameraType::FREE; //Ÿ���� ��ǥ�� �����Ƿ� �������� ����
}

//ī�޶� ��ǥ ����
template <typename P, typename R>
void Camera<P, R>::SetCameraPos(P* pt)
{
	if (pt != nullptr)
		p_camera_pos = pt;

}

template <typename P, typename R>
void Camera<P, R>::Update()
{
	//���� ī�޶� ���°� Ÿ���� ����ٴϴ� Ÿ�ٸ���� ���
	if (type == CameraType::TARGET)
	{
		//ī�޶��� �߽ɿ� Ÿ���� �������� ī�޶��� ��ǥ�� ����
		p_camera_pos->x = (*p_target).x - rc_client.right / 2;
		p_camera_pos->y = (*p_target).y - rc_client.bottom / 2;
	}

	//ī�޶��� x��ǥ�� ������ �Ǵ� ���
	if (p_camera_pos->x < 0)
		p_camera_pos->x = 0; //x��ǥ�� 0���� �ʱ�ȭ

	//ī�޶��� y��ǥ�� ������ �Ǵ� ���
	if (p_camera_pos->y < 0)
		p_camera_pos->y = 0; //y��ǥ�� 0���� �ʱ�ȭ

	//ī�޶� ���� ���� ������ �ʵ��� x������ ����
	if (p_camera_pos->x > (rc_world.right - rc_client.right))
		p_camera_pos->x = (rc_world.right - rc_client.right);

	//ī�޶� ���� ���� ������ �ʵ��� y������ ����
	if (p_camera_pos->y > (rc_world.bottom - rc_client.bottom))
		p_camera_pos->y = (rc_world.bottom - rc_client.bottom);
}
