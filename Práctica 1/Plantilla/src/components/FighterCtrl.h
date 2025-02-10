#pragma once

#include "../ecs/Component.h"

class Transform;
class FighterCtrl : public ecs::Component
{
public:
	FighterCtrl(): Component(), _rotationDegrees(5.0f), _thrust(0.2), _speedLimit(3.0f) {}
	void update() override;
	void initComponent() override;

protected:
	float _rotationDegrees;
	float _thrust;
	float _speedLimit;

	Transform* _transform;
};

