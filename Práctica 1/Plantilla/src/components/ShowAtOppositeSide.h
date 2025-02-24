#pragma once
#include "../ecs/Component.h"

class Transform;

class ShowAtOppositeSide : public ecs::Component {
	Transform* _transform;
public:
	__CMPID_DECL__(ecs::cmp::SHOWATOPPSTSIDE)

	ShowAtOppositeSide() : Component() {}
	void update() override;
	void initComponent() override;
};