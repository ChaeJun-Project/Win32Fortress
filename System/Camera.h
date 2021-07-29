#pragma once

//ī�޶� ������ Ÿ��
enum class CameraType
{
	FREE,    //Ÿ���� ���� �������� ���� ���
	TARGET,  //Ÿ���� ���� ������ ����ٴϴ� ���
};

//ī�޶� Ŭ����(�̱��� ���, ���ø� Ŭ����)
template <typename P, typename R>
class Camera : public SingletonBase<Camera<P, R>>
{
private:
	P*				p_target; //Ÿ���� ��ǥ
	P*				p_camera_pos; //ī�޶��� ��ǥ

	R				rc_client; //������ â�� ũ��
	R				rc_world;  //���� ���� ���� ���� ũ��

	CameraType		type; //ī�޶� Ÿ��

public:
	Camera();
	explicit Camera(const R& rcClient, const R& rcWorld); //������ �����ε�
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

//ī�޶� Ŭ������ ���ø� �Լ��� ����ο� ���Ǻθ� ������ ���� hpp ���
#include "Camera.hpp"