#pragma once
#include "Behavior.h"

PTR( CameraControl )

class CameraControl : public Behavior
{
public:
	CameraControl();
	virtual ~CameraControl();

	virtual void Update();
};

