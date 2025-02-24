#pragma once

#include "../ecs/Component.h"

class Transform;
class SoundEffect;
class FighterCtrl : public ecs::Component
{
public:
	FighterCtrl();
	~FighterCtrl();

	void update() override;
	void initComponent() override;

	__CMPID_DECL__(ecs::cmp::FIGHTRCTRL)
protected:

	float _rotationDegrees;
	float _thrust;
	float _speedLimit;

	Transform* _transform;
	SoundEffect* _thrustSound;
};

