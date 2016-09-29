#pragma once
#include "GameObject.h"

PTR( Camera )

class Camera : public GameObject {
friend class GameEngine;
public:
	virtual ~Camera();

	static CameraPtr GetMainCamera();

private:
	Camera();
};

#define sCamera Camera::GetMainCamera()