#pragma once
#include "../ecs/Component.h"

class Transform;

class ShowAtOppositeSide : public ecs::Component {
	Transform* _transform;
public:
	ShowAtOppositeSide() : Component() {}
	void update() override;
	void initComponent() override;
};