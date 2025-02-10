#pragma once

#include "../ecs/Component.h"
class Transform;
class DeAcceleration : public ecs::Component {
	Transform* _transform;
public:
	DeAcceleration() : Component() {}
	void update() override;
	void initComponent() override;
};