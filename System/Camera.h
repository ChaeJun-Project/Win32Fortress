#pragma once

enum class CameraType
{
	FREE,
	TARGET,
};

template <typename P, typename R>
class Camera : public SingletonBase<Camera<P, R>>
{
private:
	P*				p_target;
	P*				p_camera_pos;

	R				rc_client;
	R				rc_world;

	CameraType		type;
	
public:
	Camera();
	explicit Camera(const R& rcClient, const R& rcWorld);
	~Camera();

	bool Init(P* pt);
	void Update();

	void SetTarget(P* pt);

	void SetTargetPos(P* pt) { p_target = pt; }
	void SetCameraPos(P* pt) { p_camera_pos = pt; }

	const P* GetTargetPos() const { return p_target; }
	const P* GetCameraPos() const { return p_camera_pos; }

	void SetClient(const R& rc) { rc_client = rc; }
	void SetWorld(const R& rc) { rc_world = rc; }

	const R& GetClient() const { return rc_client; }
	const R& GetWorld() const { return rc_world; }
};

#include "Camera.hpp"